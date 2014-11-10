/*
 *            Copyright 2009-2012 The VOTCA Development Team
 *                       (http://www.votca.org)
 *
 *      Licensed under the Apache License, Version 2.0 (the "License")
 *
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

// UBLAS stops checking types and array bounds if this flag is defined
#define NDEBUG
#define BOOST_UBLAS_NDEBUG

#ifndef _VOTCA_CTP_DFTENGINE_H
#define	_VOTCA_CTP_DFTENGINE_H

#include <votca/ctp/segment.h>
#include <votca/ctp/orbitals.h>
#include <votca/ctp/aobasis.h>
#include <votca/ctp/aomatrix.h>
#include <votca/ctp/threecenters.h>
#include <votca/ctp/logger.h>
#include <votca/ctp/qmpackagefactory.h>
#include <votca/ctp/parallelxjobcalc.h>
#include <unistd.h>

#include <fstream>
#include <sys/stat.h>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/filesystem.hpp>
#include <votca/tools/linalg.h>
#include <votca/ctp/ERIs.h>
#include <boost/numeric/ublas/operation.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>

#include <votca/ctp/numerical_integrations.h>

namespace votca { namespace ctp {
    namespace ub = boost::numeric::ublas;

        /**
         * \brief Electronic ground-state via Density-Functional Theory
         *
         * Evaluates electronic ground state in molecular systems based on
         * density functional theory with Gaussian Orbitals.
         * 
         */

class DFTENGINE 
{
public:

    DFTENGINE() { };
   ~DFTENGINE() { };

   
   
    void    Initialize( Property *options);
    string  Identify() { return "dftengine"; }
   
    void    CleanUp();

    void setLogger( Logger* pLog ) { _pLog = pLog; }
    
    bool Evaluate(   Orbitals* _orbitals );

    // interfaces for options getting/setting
    //bool get_do_qp_diag(){ return _do_qp_diag ;}
    //void set_do_qp_diag( bool inp ){ _do_qp_diag = inp;}
    
    
    private:

    Logger *_pLog;
    
    void Prepare( Orbitals* _orbitals );
    void SetupInvariantMatrices();
    
    void DensityMatrixGroundState( ub::matrix<double>& _MOs, int occulevels ) ;
    

    void EvolveDensityMatrix(ub::matrix<double>& MOCoeff, int occulevels);
    
    //bool   _maverick;
    
    // program tasks
    //bool                                _do_qp_diag;
    
    // storage tasks
    //bool                                _store_qp_pert;
    
    int                                 _openmp_threads;
    
    
    string _outParent;
    string _outMonDir;
    
    // options
    string _dft_options;
    Property _dftengine_options; 
    
    // atoms
    std::vector<QMAtom*>                _atoms;

    // basis sets
    string                              _auxbasis_name;
    string                              _dftbasis_name;
    BasisSet                            _dftbasisset;
    BasisSet                            _auxbasisset;
    AOBasis                             _dftbasis;
    AOBasis                             _auxbasis;

    // numerical integration 
    string                              _grid_name;
    NumericalIntegration                _gridIntegration;

    // AO Matrices
    AOOverlap                           _dftAOoverlap;
    AOOverlap                           _auxAOoverlap;
    AOCoulomb                           _dftAOcoulomb;
    AOCoulomb                           _auxAOcoulomb;
    AOKinetic                           _dftAOkinetic;
    AOESP                               _dftAOESP;
    
    //
    double                              _mixingparameter;
    int                                 _numofelectrons;
    ub::matrix<double>                  _dftAOdmat;
    std::vector< ub::matrix<double> >   _dftdmathist;
    //Electron repulsion integrals
    ERIs                                _ERIs;
    
    // exchange and correlation
    string                              _x_functional_name;
    string                              _c_functional_name;

};


}}

#endif	/* _VOTCA_CTP_DFTENGINE_H */
