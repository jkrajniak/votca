#! /bin/bash
#
# Copyright 2009-2017 The VOTCA Development Team (http://www.votca.org)
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

if [ "$1" = "--help" ]; then
cat <<EOF
${0##*/}, version %version%
This script implemtents calculation of distributions including intramolecular
interactions for the HNC methods using generic csg tools (csg_stat)

Usage: ${0##*/}
EOF
   exit 0
fi

sim_prog="$(csg_get_property cg.inverse.program)"

topol=$(csg_get_property cg.inverse.$sim_prog.topol)
[[ -f $topol ]] || die "${0##*/}: topol file '$topol' not found, possibly you have to add it to cg.inverse.filelist"

traj=$(csg_get_property cg.inverse.$sim_prog.traj)
[[ -f $traj ]] || die "${0##*/}: traj file '$traj' not found"

equi_time="$(csg_get_property cg.inverse.$sim_prog.equi_time)"
if [[ ${CSG_RUNTEST} ]] && csg_calc "$equi_time" ">" "0"; then
  msg --color blue --to-stderr "Automatically setting equi_time to 0, because CSG_RUNTEST was set"
  equi_time=0
fi

first_frame="$(csg_get_property cg.inverse.$sim_prog.first_frame)"
if [[ ${CSG_RUNTEST} ]] && csg_calc "$first_frame" ">" "0"; then
  msg --color blue --to-stderr "Automatically setting first_frame to 0, because CSG_RUNTEST was set"
  first_frame=0
fi

tasks=$(get_number_tasks)

critical csg_stat --options "$CSGXMLFILE" --top "$topol" --trj "$traj" \
    --begin $equi_time --first-frame $first_frame --nt $tasks --include-intra --ext "dist-incl.new"

