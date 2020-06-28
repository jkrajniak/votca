[![Codacy Badge](https://app.codacy.com/project/badge/Grade/677ff88de55e46ee9411e2eaa6248e0c)](https://www.codacy.com/gh/votca/csg-tutorials?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=votca/csg-tutorials&amp;utm_campaign=Badge_Grade)
[![codecov](https://codecov.io/gh/votca/csg-tutorials/branch/master/graph/badge.svg)](https://codecov.io/gh/votca/csg-tutorials)
[![CI](https://github.com/votca/csg-tutorials/workflows/CI/badge.svg)](https://github.com/votca/csg-tutorials/actions?query=branch%3Agithub_actions+workflow%3ACI)
[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.3902713.svg)](https://doi.org/10.5281/zenodo.3902713)

This is a collection of coarse-graining tutorials using the 
VOTCA package. Further information on VOTCA can be found at
http://www.votca.org

The development of VOTCA is mainly funded by academic research grants.
If you use this package, please cite the VOTCA papers:

* _Relative entropy and optimization-driven coarse-graining methods in VOTCA_,  
  S.Y. Mashayak, M. Jochum, K. Koschke, N.R. Aluru, V. Ruehle, and C.
  Junghans,  
  [PLoS one 10, e131754 (2015)](http://dx.doi.org/10.1371/journal.pone.0131754).

* _Hybrid approaches to coarse-graining using the VOTCA package: liquid
  hexane_,  
  V. Ruehle and C. Junghans,  
  [Macromol. Theory Simul. 20, 472 (2011)](http://dx.doi.org/10.1002/mats.201100011).

* _Versatile Object-oriented Toolkit for Coarse-graining Applications_,  
  V.Ruehle, C. Junghans, A. Lukyanov, K. Kremer, and D. Andrienko,  
  [J. Chem. Theo. Comp. 5 (12), 3211 (2009)](http://dx.doi.org/10.1021/ct900369w).

In case of questions, please post them in the google discussion group
for votca at http://groups.google.com/group/votca

You can contact the VOTCA Development Team at devs@votca.org.


The following tutorials (compare with paper above) are included. They all rely
on Gromacs unless specified otherwise:

-    `spce/atomistic`: atomistic reference simulations for SPC/E water
-    `spce/force_matching`: force matching for SPC/E water
-    `spce/ibi`: iterative boltzmann inversion for SPC/E water
-    `spce/ibi_pressure`: iterative boltzmann inversion for SPC/E water with simple pressure correction
-    `spce/ibi_pressure_wjk`: iterative boltzmann inversion for SPC/E water with wjk pressure correction
-    `spce/ibi_hoomd-blue`: iterative boltzmann inversion for SPC/E water using hoomd-blue
-    `spce/ibi_dlpoly`: iterative boltzmann inversion for SPC/E water using dl_poly
-    `spce/ibi_espresso`: iterative boltzmann inversion for SPC/E water using ESPResSo
-    `spce/ibi_espressopp`: iterative boltzmann inversion for SPC/E water using ESPResSo++
-    `spce/ibi_lammps`: iterative boltzmann inversion for SPC/E water using LAMMPS
-    `spce/ibi_gromacs-multi`: iterative boltzmann inversion for SPC/E water using GROMACS' multidir feature
-    `spce/imc` inverse monte carlo for SPC/E water
-    `spce/re`: relative entropy method for SPC/E water
-    `spce/re_lammps`: relative entropy method for SPC/E water using LAMMPS
-    `spce/realtime`: iterative boltzmann inversion realtime tutorial for SPC/E water
-    `spce/realtime_lammps`: iterative boltzmann inversion realtime tutorial for SPC/E water using LAMMPS
-    `spce/simplex`: simplex optimization for SPC/E water
     -    `spce/simplex/simple`: optimizing the rdf
     -    `spce/simplex/pressure`: optimizing the rdf and pressure
     -    `spce/simplex/density`: optimizing the rdf and density
-    `spce/cma`: cma optimization for SPC/E water
     -    `spce/cma/simple`: optimizing the rdf
     -    `spce/cma/density`: optimizing the rdf and the density

-    `methanol/atomistic`: atomistic simulations for methanol
-    `methanol/force_matching`: force matching for methanol
-    `methanol/ibi`: iterative boltzmann inversion for methanol
-    `methanol/imc`: inverse monte carlo for methanol
-    `methanol/imc_gromacs-remd`: inverse monte carlo for methanol with REMD (only for gromacs) during iterations

-    `propane/atomistic`: atomistic simulations for liquid propane
-    `propane/ibi`: iterative boltzmann inversion for nonbonded interactions of liquid propane
-    `propane/imc`: inverse monte carlo for nonbonded interactions of liquid propane
-    `propane/single_chain`: atomistic simulations, boltzmann inversion and force matching for a single chain of propane

-    `hexane/atomistic`: atomistic simulations for liquid hexane
-    `hexane/force_matching`: force matching (bonded and nonbonded interactions of liquid hexane
-    `hexane/ibi_all`: iterative boltzmann inversion for bonded and nonbonded interactions of liquid hexane
-    `hexane/ibi_nonbonded`: iterative boltzmann inversion for only nonbonded interactions of liquid hexane
-    `hexane/hybrid_force_matching`: hybrid force matching of only nonbonded interactions (with bonded interactions from boltzmann inversion)

-    `methanol-water`: methanol-water mixture for 3 different concentrations
     -    `methanol-water/*/atomistic    atomistic simulations
     -    `methanol-water/*/re`: relative entropy method
     -    `methanol-water/*/simplex`: simplex optimizing

-    `urea-water/atomistic`: atomistic reference simulations urea-water mixture
-    `urea-water/kb-ibi`: Kirkwood-Buff coarse-graining (see Ganguly et al.  J. Chem. Theo. Comp., 8, 1802 (2012) for details)
-    `urea-water/cibi`: Coordination iterative Boltzmann inversion (see T. E. de Oliveira et al., JCP 144, 174106 (2016) for details) - different molarity than kb-ibi
-    `urea-water/cibi/pre`: IBI preparation run for cibi
-    `urea-water/ibi`: boltzmann inversion (to compare to kb-ibi)

-   `LJ1-LJ2/imc`: regularization of inverse Monte-Carlo (see Rosenberger et al. Eur. Phys. J. Special Topics 225, 1323-1345 (2016) for details)

Each of the tutorials contains a `run.sh` which lists all commands needed to execute the tutorial. 
