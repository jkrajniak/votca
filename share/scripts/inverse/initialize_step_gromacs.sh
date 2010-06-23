#! /bin/bash
#
# Copyright 2009 The VOTCA Development Team (http://www.votca.org)
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
This script prepares the input and configuration files for gromacs.

Usage: ${0##*/}

USES: get_main_dir get_last_step_dir run_or_exit grompp mdrun

NEEDS:
EOF
  exit 0
fi

check_deps "$0"

# Get initial configuration
main_dir=$(get_main_dir);
cp ${main_dir}/conf.gro ./conf.gro || die "${0##*/} cp ${main_dir}/conf.gro ./conf.gro failed"

steep_mdp="$(csg_get_property cg.inverse.gromacs.steep_mdp "grompp.steep.mdp")"
[ -f "$steep_mdp" ] || die "${0##*/}: gromacs mdp file '$steep_mdp' not found"
mdp="$(csg_get_property cg.inverse.gromacs.mdp "grompp.mdp")"
[ -f "$mdp" ] || die "${0##*/}: gromacs mdp file '$mdp' not found"

#convert potential in format for sim_prog
for_all non-bonded do_external convert_potential gromacs

for_all "non-bonded" check_cutoff $mdp

index="$(csg_get_property cg.inverse.gromacs.grompp.index "index.ndx")"
[ -f "$index" ] || die "${0##*/}: grompp index file '$index' not found"
top="$(csg_get_property cg.inverse.gromacs.grompp.topol "topol.top")"
[ -f "$top" ] || die "${0##*/}: grompp topol file '$top' not found"
tpr="$(csg_get_property cg.inverse.gromacs.topol "topol.tpr")"
opts="$(csg_get_property --allow-empty cg.inverse.gromacs.grompp.opts)"

# Energy Minimization
run_or_exit grompp -n "${index}" -f "${steep_mdp}" -p "$top" -o "$tpr" ${opts}
[ -f "$tpr" ] || die "${0##*/}: gromacs tpr file '$tpr' not found after running grompp"

if use_mpi; then
  mpicmd=$(csg_get_property cg.inverse.mpi.cmd)
  run_or_exit $mpicmd mdrun -s "${tpr}" "${opts}"
else
  run_or_exit mdrun -s "${tpr}" "${opts}"
fi

mv confout.gro conf.gro

# For full MD
run_or_exit grompp -n "${index}" -f "${mdp}" -p "$top" -o "$tpr" ${opts}
[ -f "$tpr" ] || die "${0##*/}: gromacs tpr file '$tpr' not found after running grompp"
