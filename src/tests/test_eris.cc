/*
 * Copyright 2009-2018 The VOTCA Development Team (http://www.votca.org)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#define BOOST_TEST_MAIN

#define BOOST_TEST_MODULE eris_test
#include <boost/test/unit_test.hpp>
#include <votca/xtp/ERIs.h>
#include <votca/xtp/convergenceacc.h>

using namespace votca::xtp;

BOOST_AUTO_TEST_SUITE(eris_test)

BOOST_AUTO_TEST_CASE(fourcenter_cache){
  
  ofstream xyzfile("molecule.xyz");
  xyzfile << " 5" << endl;
  xyzfile << " methane" << endl;
  xyzfile << " C            .000000     .000000     .000000" << endl;
  xyzfile << " H            .629118     .629118     .629118" << endl;
  xyzfile << " H           -.629118    -.629118     .629118" << endl;
  xyzfile << " H            .629118    -.629118    -.629118" << endl;
  xyzfile << " H           -.629118     .629118    -.629118" << endl;
  xyzfile.close();

 ofstream basisfile("3-21G.xml");
  basisfile <<"<basis name=\"3-21G\">" << endl;
  basisfile << "  <element name=\"H\">" << endl;
  basisfile << "    <shell scale=\"1.0\" type=\"S\">" << endl;
  basisfile << "      <constant decay=\"5.447178e+00\">" << endl;
  basisfile << "        <contractions factor=\"1.562850e-01\" type=\"S\"/>" << endl;
  basisfile << "      </constant>" << endl;
  basisfile << "      <constant decay=\"8.245470e-01\">" << endl;
  basisfile << "        <contractions factor=\"9.046910e-01\" type=\"S\"/>" << endl;
  basisfile << "      </constant>" << endl;
  basisfile << "    </shell>" << endl;
  basisfile << "    <shell scale=\"1.0\" type=\"S\">" << endl;
  basisfile << "      <constant decay=\"1.831920e-01\">" << endl;
  basisfile << "        <contractions factor=\"1.000000e+00\" type=\"S\"/>" << endl;
  basisfile << "      </constant>" << endl;
  basisfile << "    </shell>" << endl;
  basisfile << "  </element>" << endl;
  basisfile << "  <element name=\"C\">" << endl;
  basisfile << "    <shell scale=\"1.0\" type=\"S\">" << endl;
  basisfile << "      <constant decay=\"1.722560e+02\">" << endl;
  basisfile << "        <contractions factor=\"6.176690e-02\" type=\"S\"/>" << endl;
  basisfile << "      </constant>" << endl;
  basisfile << "      <constant decay=\"2.591090e+01\">" << endl;
  basisfile << "        <contractions factor=\"3.587940e-01\" type=\"S\"/>" << endl;
  basisfile << "      </constant>" << endl;
  basisfile << "      <constant decay=\"5.533350e+00\">" << endl;
  basisfile << "        <contractions factor=\"7.007130e-01\" type=\"S\"/>" << endl;
  basisfile << "      </constant>" << endl;
  basisfile << "    </shell>" << endl;
  basisfile << "    <shell scale=\"1.0\" type=\"SP\">" << endl;
  basisfile << "      <constant decay=\"3.664980e+00\">" << endl;
  basisfile << "        <contractions factor=\"-3.958970e-01\" type=\"S\"/>" << endl;
  basisfile << "        <contractions factor=\"2.364600e-01\" type=\"P\"/>" << endl;
  basisfile << "      </constant>" << endl;
  basisfile << "      <constant decay=\"7.705450e-01\">" << endl;
  basisfile << "        <contractions factor=\"1.215840e+00\" type=\"S\"/>" << endl;
  basisfile << "        <contractions factor=\"8.606190e-01\" type=\"P\"/>" << endl;
  basisfile << "      </constant>" << endl;
  basisfile << "    </shell>" << endl;
  basisfile << "    <shell scale=\"1.0\" type=\"SP\">" << endl;
  basisfile << "      <constant decay=\"1.958570e-01\">" << endl;
  basisfile << "        <contractions factor=\"1.000000e+00\" type=\"S\"/>" << endl;
  basisfile << "        <contractions factor=\"1.000000e+00\" type=\"P\"/>" << endl;
  basisfile << "      </constant>" << endl;
  basisfile << "    </shell>" << endl;
  basisfile << "  </element>" << endl;
  basisfile << "</basis>" << endl;
  basisfile.close();
  
  Orbitals orbitals;
  orbitals.LoadFromXYZ("molecule.xyz");
  BasisSet basis;
  basis.LoadBasisSet("3-21G.xml");
 
  AOBasis aobasis;
  aobasis.AOBasisFill(&basis,orbitals.QMAtoms());
 
 Eigen::MatrixXd dmat=Eigen::MatrixXd::Zero(17,17);       
 dmat<<0.00157507,0.0337454,4.48905e-16,-5.93152e-16,7.87133e-17,0.030876,2.51254e-16,-1.49094e-16,5.77899e-17,0.00415998,-0.00445632,0.00415998,-0.00445632,0.00415998,-0.00445632,0.00415998,-0.00445632,
0.0337454,0.722983,2.66427e-15,-4.44783e-15,3.45846e-16,0.661507,4.39854e-15,-2.02475e-15,1.04832e-15,0.0891262,-0.095475,0.0891262,-0.095475,0.0891262,-0.095475,0.0891262,-0.095475,
4.48905e-16,2.66427e-15,1.52199,2.88658e-15,2.09034e-15,-7.94212e-15,0.215492,2.8727e-15,-1.40513e-15,0.141933,-0.0402359,0.141933,-0.0402359,-0.141933,0.0402359,-0.141933,0.0402359,
-5.93152e-16,-4.44783e-15,2.88658e-15,1.52199,-2.31759e-15,9.21105e-15,-2.22045e-15,0.215492,1.6263e-15,0.141933,-0.0402359,-0.141933,0.0402359,-0.141933,0.0402359,0.141933,-0.0402359,
7.87133e-17,3.45846e-16,2.09034e-15,-2.31759e-15,1.52199,2.98902e-15,-2.04958e-15,4.79738e-15,0.215492,0.141933,-0.0402359,-0.141933,0.0402359,0.141933,-0.0402359,-0.141933,0.0402359,
0.030876,0.661507,-7.94212e-15,9.21105e-15,2.98902e-15,0.605259,2.55488e-15,2.7779e-17,1.33759e-15,0.0815477,-0.0873567,0.0815477,-0.0873567,0.0815477,-0.0873567,0.0815477,-0.0873567,
2.51254e-16,4.39854e-15,0.215492,-2.22045e-15,-2.04958e-15,2.55488e-15,0.0305108,3.29597e-17,-5.29036e-16,0.0200958,-0.00569686,0.0200958,-0.00569686,-0.0200958,0.00569686,-0.0200958,0.00569686,
-1.49094e-16,-2.02475e-15,2.8727e-15,0.215492,4.79738e-15,2.7779e-17,3.29597e-17,0.0305108,9.55941e-16,0.0200958,-0.00569686,-0.0200958,0.00569686,-0.0200958,0.00569686,0.0200958,-0.00569686,
5.77899e-17,1.04832e-15,-1.40513e-15,1.6263e-15,0.215492,1.33759e-15,-5.29036e-16,9.55941e-16,0.0305108,0.0200958,-0.00569686,-0.0200958,0.00569686,0.0200958,-0.00569686,-0.0200958,0.00569686,
0.00415998,0.0891262,0.141933,0.141933,0.141933,0.0815477,0.0200958,0.0200958,0.0200958,0.0506951,-0.0230264,-0.00224894,-0.00801753,-0.00224894,-0.00801753,-0.00224894,-0.00801753,
-0.00445632,-0.095475,-0.0402359,-0.0402359,-0.0402359,-0.0873567,-0.00569686,-0.00569686,-0.00569686,-0.0230264,0.0157992,-0.00801753,0.0115445,-0.00801753,0.0115445,-0.00801753,0.0115445,
0.00415998,0.0891262,0.141933,-0.141933,-0.141933,0.0815477,0.0200958,-0.0200958,-0.0200958,-0.00224894,-0.00801753,0.0506951,-0.0230264,-0.00224894,-0.00801753,-0.00224894,-0.00801753,
-0.00445632,-0.095475,-0.0402359,0.0402359,0.0402359,-0.0873567,-0.00569686,0.00569686,0.00569686,-0.00801753,0.0115445,-0.0230264,0.0157992,-0.00801753,0.0115445,-0.00801753,0.0115445,
0.00415998,0.0891262,-0.141933,-0.141933,0.141933,0.0815477,-0.0200958,-0.0200958,0.0200958,-0.00224894,-0.00801753,-0.00224894,-0.00801753,0.0506951,-0.0230264,-0.00224894,-0.00801753,
-0.00445632,-0.095475,0.0402359,0.0402359,-0.0402359,-0.0873567,0.00569686,0.00569686,-0.00569686,-0.00801753,0.0115445,-0.00801753,0.0115445,-0.0230264,0.0157992,-0.00801753,0.0115445,
0.00415998,0.0891262,-0.141933,0.141933,-0.141933,0.0815477,-0.0200958,0.0200958,-0.0200958,-0.00224894,-0.00801753,-0.00224894,-0.00801753,-0.00224894,-0.00801753,0.0506951,-0.0230264,
-0.00445632,-0.095475,0.0402359,-0.0402359,0.0402359,-0.0873567,0.00569686,-0.00569686,0.00569686,-0.00801753,0.0115445,-0.00801753,0.0115445,-0.00801753,0.0115445,-0.0230264,0.0157992;


ERIs eris;
eris.Initialize_4c_small_molecule(aobasis);
eris.CalculateERIs_4c_small_molecule(dmat);

Eigen::MatrixXd eris_ref=Eigen::MatrixXd::Zero(17,17);     
eris_ref<<7.97316 ,1.45564 ,-3.0651e-17 ,8.17169e-17 ,3.42098e-16 ,1.39992 ,-3.24766e-18 ,1.13521e-17 ,4.75743e-17 ,0.145934 ,0.627171 ,0.145934 ,0.627171 ,0.145934 ,0.627171 ,0.145934 ,0.627171,
1.45564 ,6.28995 ,4.29881e-17 ,4.47071e-16 ,1.36225e-15 ,4.46207 ,4.45165e-17 ,2.4258e-16 ,6.14373e-16 ,1.0517 ,2.29374 ,1.0517 ,2.29374 ,1.0517 ,2.29374 ,1.0517 ,2.29374,
-3.0651e-17 ,4.29881e-17 ,6.26692 ,3.16473e-16 ,4.80361e-17 ,5.64633e-17 ,2.77119 ,1.33411e-16 ,-2.0052e-18 ,0.861649 ,0.693449 ,0.861649 ,0.693449 ,-0.861649 ,-0.693449 ,-0.861649 ,-0.693449,
8.17169e-17 ,4.47071e-16 ,3.16473e-16 ,6.26692 ,6.55882e-17 ,3.86325e-16 ,1.33411e-16 ,2.77119 ,6.69489e-17 ,0.861649 ,0.693449 ,-0.861649 ,-0.693449 ,-0.861649 ,-0.693449 ,0.861649 ,0.693449,
3.42098e-16 ,1.36225e-15 ,4.80361e-17 ,6.55882e-17 ,6.26692 ,1.04265e-15 ,-2.0052e-18 ,6.69489e-17 ,2.77119 ,0.861649 ,0.693449 ,-0.861649 ,-0.693449 ,0.861649 ,0.693449 ,-0.861649 ,-0.693449,
1.39992 ,4.46207 ,5.64633e-17 ,3.86325e-16 ,1.04265e-15 ,4.6748 ,1.26956e-16 ,3.96496e-16 ,8.46433e-16 ,1.45414 ,2.8438 ,1.45414 ,2.8438 ,1.45414 ,2.8438 ,1.45414 ,2.8438,
-3.24766e-18 ,4.45165e-17 ,2.77119 ,1.33411e-16 ,-2.0052e-18 ,1.26956e-16 ,3.60471 ,1.19577e-16 ,-4.02136e-17 ,1.12112 ,1.13632 ,1.12112 ,1.13632 ,-1.12112 ,-1.13632 ,-1.12112 ,-1.13632,
1.13521e-17 ,2.4258e-16 ,1.33411e-16 ,2.77119 ,6.69489e-17 ,3.96496e-16 ,1.19577e-16 ,3.60471 ,1.28251e-16 ,1.12112 ,1.13632 ,-1.12112 ,-1.13632 ,-1.12112 ,-1.13632 ,1.12112 ,1.13632,
4.75743e-17 ,6.14373e-16 ,-2.0052e-18 ,6.69489e-17 ,2.77119 ,8.46433e-16 ,-4.02136e-17 ,1.28251e-16 ,3.60471 ,1.12112 ,1.13632 ,-1.12112 ,-1.13632 ,1.12112 ,1.13632 ,-1.12112 ,-1.13632,
0.145934 ,1.0517 ,0.861649 ,0.861649 ,0.861649 ,1.45414 ,1.12112 ,1.12112 ,1.12112 ,3.82992 ,2.41107 ,0.0414422 ,0.512709 ,0.0414422 ,0.512709 ,0.0414422 ,0.512709,
0.627171 ,2.29374 ,0.693449 ,0.693449 ,0.693449 ,2.8438 ,1.13632 ,1.13632 ,1.13632 ,2.41107 ,3.3433 ,0.512709 ,1.4449 ,0.512709 ,1.4449 ,0.512709 ,1.4449,
0.145934 ,1.0517 ,0.861649 ,-0.861649 ,-0.861649 ,1.45414 ,1.12112 ,-1.12112 ,-1.12112 ,0.0414422 ,0.512709 ,3.82992 ,2.41107 ,0.0414422 ,0.512709 ,0.0414422 ,0.512709,
0.627171 ,2.29374 ,0.693449 ,-0.693449 ,-0.693449 ,2.8438 ,1.13632 ,-1.13632 ,-1.13632 ,0.512709 ,1.4449 ,2.41107 ,3.3433 ,0.512709 ,1.4449 ,0.512709 ,1.4449,
0.145934 ,1.0517 ,-0.861649 ,-0.861649 ,0.861649 ,1.45414 ,-1.12112 ,-1.12112 ,1.12112 ,0.0414422 ,0.512709 ,0.0414422 ,0.512709 ,3.82992 ,2.41107 ,0.0414422 ,0.512709,
0.627171 ,2.29374 ,-0.693449 ,-0.693449 ,0.693449 ,2.8438 ,-1.13632 ,-1.13632 ,1.13632 ,0.512709 ,1.4449 ,0.512709 ,1.4449 ,2.41107 ,3.3433 ,0.512709 ,1.4449,
0.145934 ,1.0517 ,-0.861649 ,0.861649 ,-0.861649 ,1.45414 ,-1.12112 ,1.12112 ,-1.12112 ,0.0414422 ,0.512709 ,0.0414422 ,0.512709 ,0.0414422 ,0.512709 ,3.82992 ,2.41107,
0.627171 ,2.29374 ,-0.693449 ,0.693449 ,-0.693449 ,2.8438 ,-1.13632 ,1.13632 ,-1.13632 ,0.512709 ,1.4449 ,0.512709 ,1.4449 ,0.512709 ,1.4449 ,2.41107 ,3.3433;
bool eris_check=eris.getERIs().isApprox(eris_ref,0.00001);
BOOST_CHECK_EQUAL(eris_check, 1);


eris.CalculateEXX_4c_small_molecule(dmat);


Eigen::MatrixXd exx_ref=Eigen::MatrixXd::Zero(17,17);   
exx_ref<<0.389974 ,0.688493 ,3.79471e-17 ,7.81168e-17 ,1.08518e-15 ,0.517741 ,4.72468e-16 ,-9.48677e-17 ,5.73814e-16 ,0.127329 ,0.269914 ,0.127329 ,0.269914 ,0.127329 ,0.269914 ,0.127329 ,0.269914,
0.688493 ,2.50146 ,-1.02362e-16 ,1.06661e-15 ,3.44768e-15 ,1.9867 ,1.61085e-15 ,2.45057e-16 ,2.26081e-15 ,0.565584 ,1.07459 ,0.565584 ,1.07459 ,0.565584 ,1.07459 ,0.565584 ,1.07459,
4.46971e-17 ,-1.27916e-16 ,2.183 ,2.72192e-15 ,4.18152e-16 ,-1.07828e-15 ,1.09857 ,1.98561e-15 ,-3.66135e-16 ,0.398514 ,0.296396 ,0.398514 ,0.296396 ,-0.398514 ,-0.296396 ,-0.398514 ,-0.296396,
7.76458e-17 ,1.06603e-15 ,2.72067e-15 ,2.183 ,5.41643e-16 ,2.43269e-15 ,5.75359e-16 ,1.09857 ,9.80009e-16 ,0.398514 ,0.296396 ,-0.398514 ,-0.296396 ,-0.398514 ,-0.296396 ,0.398514 ,0.296396,
1.08939e-15 ,3.43893e-15 ,4.20912e-16 ,5.42781e-16 ,2.183 ,3.25489e-15 ,-5.41257e-16 ,1.86621e-15 ,1.09857 ,0.398514 ,0.296396 ,-0.398514 ,-0.296396 ,0.398514 ,0.296396 ,-0.398514 ,-0.296396,
0.517741 ,1.9867 ,-1.09083e-15 ,2.45266e-15 ,3.22787e-15 ,1.65289 ,1.02023e-15 ,1.07747e-15 ,2.28546e-15 ,0.499817 ,0.909896 ,0.499817 ,0.909896 ,0.499817 ,0.909896 ,0.499817 ,0.909896,
4.7234e-16 ,1.60133e-15 ,1.09857 ,5.68733e-16 ,-5.4011e-16 ,1.0231e-15 ,0.646708 ,6.65839e-16 ,-6.59225e-16 ,0.250323 ,0.180503 ,0.250323 ,0.180503 ,-0.250323 ,-0.180503 ,-0.250323 ,-0.180503,
-9.44025e-17 ,2.32187e-16 ,1.9847e-15 ,1.09857 ,1.8418e-15 ,1.07759e-15 ,6.64172e-16 ,0.646708 ,1.47368e-15 ,0.250323 ,0.180503 ,-0.250323 ,-0.180503 ,-0.250323 ,-0.180503 ,0.250323 ,0.180503,
5.74192e-16 ,2.26622e-15 ,-3.64074e-16 ,9.70211e-16 ,1.09857 ,2.28268e-15 ,-6.57724e-16 ,1.47071e-15 ,0.646708 ,0.250323 ,0.180503 ,-0.250323 ,-0.180503 ,0.250323 ,0.180503 ,-0.250323 ,-0.180503,
0.127329 ,0.565584 ,0.398514 ,0.398514 ,0.398514 ,0.499817 ,0.250323 ,0.250323 ,0.250323 ,0.562844 ,0.51555 ,0.0484527 ,0.204984 ,0.0484527 ,0.204984 ,0.0484527 ,0.204984,
0.269914 ,1.07459 ,0.296396 ,0.296396 ,0.296396 ,0.909896 ,0.180503 ,0.180503 ,0.180503 ,0.51555 ,0.66257 ,0.204984 ,0.451934 ,0.204984 ,0.451934 ,0.204984 ,0.451934,
0.127329 ,0.565584 ,0.398514 ,-0.398514 ,-0.398514 ,0.499817 ,0.250323 ,-0.250323 ,-0.250323 ,0.0484527 ,0.204984 ,0.562844 ,0.51555 ,0.0484527 ,0.204984 ,0.0484527 ,0.204984,
0.269914 ,1.07459 ,0.296396 ,-0.296396 ,-0.296396 ,0.909896 ,0.180503 ,-0.180503 ,-0.180503 ,0.204984 ,0.451934 ,0.51555 ,0.66257 ,0.204984 ,0.451934 ,0.204984 ,0.451934,
0.127329 ,0.565584 ,-0.398514 ,-0.398514 ,0.398514 ,0.499817 ,-0.250323 ,-0.250323 ,0.250323 ,0.0484527 ,0.204984 ,0.0484527 ,0.204984 ,0.562844 ,0.51555 ,0.0484527 ,0.204984,
0.269914 ,1.07459 ,-0.296396 ,-0.296396 ,0.296396 ,0.909896 ,-0.180503 ,-0.180503 ,0.180503 ,0.204984 ,0.451934 ,0.204984 ,0.451934 ,0.51555 ,0.66257 ,0.204984 ,0.451934,
0.127329 ,0.565584 ,-0.398514 ,0.398514 ,-0.398514 ,0.499817 ,-0.250323 ,0.250323 ,-0.250323 ,0.0484527 ,0.204984 ,0.0484527 ,0.204984 ,0.0484527 ,0.204984 ,0.562844 ,0.51555,
0.269914 ,1.07459 ,-0.296396 ,0.296396 ,-0.296396 ,0.909896 ,-0.180503 ,0.180503 ,-0.180503 ,0.204984 ,0.451934 ,0.204984 ,0.451934 ,0.204984 ,0.451934 ,0.51555 ,0.66257;
 bool exxs_check=eris.getEXX().isApprox(exx_ref,0.00001); 
BOOST_CHECK_EQUAL(exxs_check, 1);
}

BOOST_AUTO_TEST_CASE(threecenter){
  
  ofstream xyzfile("molecule.xyz");
  xyzfile << " 5" << endl;
  xyzfile << " methane" << endl;
  xyzfile << " C            .000000     .000000     .000000" << endl;
  xyzfile << " H            .629118     .629118     .629118" << endl;
  xyzfile << " H           -.629118    -.629118     .629118" << endl;
  xyzfile << " H            .629118    -.629118    -.629118" << endl;
  xyzfile << " H           -.629118     .629118    -.629118" << endl;
  xyzfile.close();

 ofstream basisfile("3-21G.xml");
  basisfile <<"<basis name=\"3-21G\">" << endl;
  basisfile << "  <element name=\"H\">" << endl;
  basisfile << "    <shell scale=\"1.0\" type=\"S\">" << endl;
  basisfile << "      <constant decay=\"5.447178e+00\">" << endl;
  basisfile << "        <contractions factor=\"1.562850e-01\" type=\"S\"/>" << endl;
  basisfile << "      </constant>" << endl;
  basisfile << "      <constant decay=\"8.245470e-01\">" << endl;
  basisfile << "        <contractions factor=\"9.046910e-01\" type=\"S\"/>" << endl;
  basisfile << "      </constant>" << endl;
  basisfile << "    </shell>" << endl;
  basisfile << "    <shell scale=\"1.0\" type=\"S\">" << endl;
  basisfile << "      <constant decay=\"1.831920e-01\">" << endl;
  basisfile << "        <contractions factor=\"1.000000e+00\" type=\"S\"/>" << endl;
  basisfile << "      </constant>" << endl;
  basisfile << "    </shell>" << endl;
  basisfile << "  </element>" << endl;
  basisfile << "  <element name=\"C\">" << endl;
  basisfile << "    <shell scale=\"1.0\" type=\"S\">" << endl;
  basisfile << "      <constant decay=\"1.722560e+02\">" << endl;
  basisfile << "        <contractions factor=\"6.176690e-02\" type=\"S\"/>" << endl;
  basisfile << "      </constant>" << endl;
  basisfile << "      <constant decay=\"2.591090e+01\">" << endl;
  basisfile << "        <contractions factor=\"3.587940e-01\" type=\"S\"/>" << endl;
  basisfile << "      </constant>" << endl;
  basisfile << "      <constant decay=\"5.533350e+00\">" << endl;
  basisfile << "        <contractions factor=\"7.007130e-01\" type=\"S\"/>" << endl;
  basisfile << "      </constant>" << endl;
  basisfile << "    </shell>" << endl;
  basisfile << "    <shell scale=\"1.0\" type=\"SP\">" << endl;
  basisfile << "      <constant decay=\"3.664980e+00\">" << endl;
  basisfile << "        <contractions factor=\"-3.958970e-01\" type=\"S\"/>" << endl;
  basisfile << "        <contractions factor=\"2.364600e-01\" type=\"P\"/>" << endl;
  basisfile << "      </constant>" << endl;
  basisfile << "      <constant decay=\"7.705450e-01\">" << endl;
  basisfile << "        <contractions factor=\"1.215840e+00\" type=\"S\"/>" << endl;
  basisfile << "        <contractions factor=\"8.606190e-01\" type=\"P\"/>" << endl;
  basisfile << "      </constant>" << endl;
  basisfile << "    </shell>" << endl;
  basisfile << "    <shell scale=\"1.0\" type=\"SP\">" << endl;
  basisfile << "      <constant decay=\"1.958570e-01\">" << endl;
  basisfile << "        <contractions factor=\"1.000000e+00\" type=\"S\"/>" << endl;
  basisfile << "        <contractions factor=\"1.000000e+00\" type=\"P\"/>" << endl;
  basisfile << "      </constant>" << endl;
  basisfile << "    </shell>" << endl;
  basisfile << "  </element>" << endl;
  basisfile << "</basis>" << endl;
  basisfile.close();
  
  Orbitals orbitals;
  orbitals.LoadFromXYZ("molecule.xyz");
  BasisSet basis;
  basis.LoadBasisSet("3-21G.xml");
 
  AOBasis aobasis;
  aobasis.AOBasisFill(&basis,orbitals.QMAtoms());
 
   Orbitals orb;
  orb.setBasisSetSize(17);
  orb.setNumberOfLevels(4,13);
  
  Eigen::MatrixXd H=Eigen::MatrixXd::Zero(17,17);
  //generated from 3-21G with ecp on methane independent electron guess
  H<<13.2967782,-1.99797328,0,0,0,-0.26575698,0,0,0,-0.0909339466,-0.147466802,-0.0909339466,-0.147466802,-0.0909339466,-0.147466802,-0.0909339466,-0.147466802,
-1.99797328,-4.04412972,0,0,0,-3.49418055,0,0,0,-0.994581408,-1.89398582,-0.994581408,-1.89398582,-0.994581408,-1.89398582,-0.994581408,-1.89398582,
0,0,-3.93848515,0,0,0,-2.25634153,0,0,-0.780335933,-0.599314142,-0.780335933,-0.599314142,0.780335933,0.599314142,0.780335933,0.599314142,
0,0,0,-3.93848515,0,0,0,-2.25634153,0,-0.780335933,-0.599314142,0.780335933,0.599314142,0.780335933,0.599314142,-0.780335933,-0.599314142,
0,0,0,0,-3.93848515,0,0,0,-2.25634153,-0.780335933,-0.599314142,0.780335933,0.599314142,-0.780335933,-0.599314142,0.780335933,0.599314142,
-0.26575698,-3.49418055,0,0,0,-3.88216043,0,0,0,-1.38139383,-2.47288528,-1.38139383,-2.47288528,-1.38139383,-2.47288528,-1.38139383,-2.47288528,
0,0,-2.25634153,0,0,0,-3.02562938,0,0,-1.03641022,-0.99951947,-1.03641022,-0.99951947,1.03641022,0.99951947,1.03641022,0.99951947,
0,0,0,-2.25634153,0,0,0,-3.02562938,0,-1.03641022,-0.99951947,1.03641022,0.99951947,1.03641022,0.99951947,-1.03641022,-0.99951947,
0,0,0,0,-2.25634153,0,0,0,-3.02562938,-1.03641022,-0.99951947,1.03641022,0.99951947,-1.03641022,-0.99951947,1.03641022,0.99951947,
-0.0909339466,-0.994581408,-0.780335933,-0.780335933,-0.780335933,-1.38139383,-1.03641022,-1.03641022,-1.03641022,-3.00123345,-2.29509192,-0.0552940511,-0.512094198,-0.0552940511,-0.512094198,-0.0552940511,-0.512094198,
-0.147466802,-1.89398582,-0.599314142,-0.599314142,-0.599314142,-2.47288528,-0.99951947,-0.99951947,-0.99951947,-2.29509192,-2.99604761,-0.512094198,-1.30279378,-0.512094198,-1.30279378,-0.512094198,-1.30279378,
-0.0909339466,-0.994581408,-0.780335933,0.780335933,0.780335933,-1.38139383,-1.03641022,1.03641022,1.03641022,-0.0552940511,-0.512094198,-3.00123345,-2.29509192,-0.0552940511,-0.512094198,-0.0552940511,-0.512094198,
-0.147466802,-1.89398582,-0.599314142,0.599314142,0.599314142,-2.47288528,-0.99951947,0.99951947,0.99951947,-0.512094198,-1.30279378,-2.29509192,-2.99604761,-0.512094198,-1.30279378,-0.512094198,-1.30279378,
-0.0909339466,-0.994581408,0.780335933,0.780335933,-0.780335933,-1.38139383,1.03641022,1.03641022,-1.03641022,-0.0552940511,-0.512094198,-0.0552940511,-0.512094198,-3.00123345,-2.29509192,-0.0552940511,-0.512094198,
-0.147466802,-1.89398582,0.599314142,0.599314142,-0.599314142,-2.47288528,0.99951947,0.99951947,-0.99951947,-0.512094198,-1.30279378,-0.512094198,-1.30279378,-2.29509192,-2.99604761,-0.512094198,-1.30279378,
-0.0909339466,-0.994581408,0.780335933,-0.780335933,0.780335933,-1.38139383,1.03641022,-1.03641022,1.03641022,-0.0552940511,-0.512094198,-0.0552940511,-0.512094198,-0.0552940511,-0.512094198,-3.00123345,-2.29509192,
-0.147466802,-1.89398582,0.599314142,-0.599314142,0.599314142,-2.47288528,0.99951947,-0.99951947,0.99951947,-0.512094198,-1.30279378,-0.512094198,-1.30279378,-0.512094198,-1.30279378,-2.29509192,-2.99604761;
Eigen::MatrixXd overlap_ref=Eigen::MatrixXd::Zero(17,17);
 
AOOverlap aoverlap;
aoverlap.Fill(aobasis);
  
  ConvergenceAcc d;
  d.Configure(ConvergenceAcc::closed,false,false,10,false,0,0,0.0,0,4,0);
  d.setOverlap(&aoverlap.Matrix(),1e-8);
  d.SolveFockmatrix(orb.MOEnergies(),orb.MOCoefficients(),H);
 Eigen::MatrixXd dmat=orb.DensityMatrixGroundState();
 ERIs eris;
 eris.Initialize(aobasis,aobasis,Eigen::MatrixXd::Identity(17,17));
 eris.CalculateEXX(dmat);
 Eigen::MatrixXd eri_d=eris.getERIs();
 eris.CalculateEXX(orb.MOCoefficients().block(0,0,17,4),dmat);
 Eigen::MatrixXd eri_mo=eris.getERIs();
 
 bool compare_eris=eri_mo.isApprox(eri_d,1e-4);
 BOOST_CHECK_EQUAL(compare_eris, 1);
 
}




BOOST_AUTO_TEST_SUITE_END()
