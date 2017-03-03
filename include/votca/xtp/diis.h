/* 
 *            Copyright 2009-2016 The VOTCA Development Team
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

#ifndef _VOTCA_XTP_DIIS__H
#define _VOTCA_XTP_DIIS__H



   
#include <gsl/gsl_multimin.h>
#include <gsl/gsl_vector.h>


#include <votca/tools/linalg.h>
#include <votca/xtp/aomatrix.h>
#include <votca/xtp/orbitals.h>
#include <votca/xtp/logger.h>


using namespace votca::tools;

namespace votca { namespace xtp {
 namespace ub = boost::numeric::ublas;
  
 
 class Diis{
public:

    Diis() {_maxerrorindex=0;
                _maxerror=0.0; };
   ~Diis() {
     for (std::vector< ub::matrix<double>* >::iterator it = _mathist.begin() ; it !=_mathist.end(); ++it){
         delete *it;
     }
     _mathist.clear();
      for (std::vector< ub::matrix<double>* >::iterator it = _dmathist.begin() ; it !=_dmathist.end(); ++it){
         delete *it;
     }
     _dmathist.clear();
     for (std::vector< ub::matrix<double>* >::iterator it = _errormatrixhist.begin() ; it !=_errormatrixhist.end(); ++it){
         delete *it;
     }
    _errormatrixhist.clear();
    
    for (std::vector< std::vector<double>* >::iterator it = _Diis_Bs.begin() ; it !=_Diis_Bs.end(); ++it){
         delete *it;
     }
    _Diis_Bs.clear(); 
    
   }
   
   void Configure(bool usediis, unsigned histlength, bool maxout, string diismethod, double diis_start,double levelshift,bool unrestricted,unsigned nocclevels){
       _usediis=usediis;
       _histlength=histlength;
       _maxout=maxout;
       _diismethod=diismethod;
       _diis_start=diis_start;
       _levelshift=levelshift;
       _unrestricted=unrestricted;
       _nocclevels=nocclevels;
  
   }
   
   void setOverlap(ub::matrix<double>* _S){
       S=_S;
   }
   void setSqrtOverlap(ub::matrix<double>* _Sminusahalf){
       Sminusahalf=_Sminusahalf;
   }
    void setLogger(Logger *pLog){_pLog=pLog;}
    double Evolve(const ub::matrix<double>& dmat,const ub::matrix<double>& H,ub::vector<double> &MOenergies,ub::matrix<double> &MOs, int this_iter,double totE);
    void SolveFockmatrix(ub::vector<double>& MOenergies,ub::matrix<double>& MOs,const ub::matrix<double>&H);
    void Levelshift(ub::matrix<double>& H,const ub::matrix<double> & dmat,double levelshift,bool unrestricted);
    unsigned gethistlength(){return _mathist.size();}
    
    
    double get_E_adiis(const gsl_vector * x) const;

    void get_dEdx_adiis(const gsl_vector * x, gsl_vector * dEdx) const;
    void get_E_dEdx_adiis(const gsl_vector * x, double * Eval, gsl_vector * dEdx) const;
   
 private:
     
    Logger *_pLog;
    ub::matrix<double>* S;
    ub::matrix<double>* Sminusahalf;
    bool                              _usediis;
    unsigned                          _histlength;
    bool                              _maxout;
    string                            _diismethod;
    ub::matrix<double>                _Sminusonehalf;
    double                              _maxerror;
    double                              _diis_start;                 
    unsigned                            _maxerrorindex;
    std::vector< ub::matrix<double>* >   _mathist;
    std::vector< ub::matrix<double>* >   _dmathist;
    std::vector< ub::matrix<double>* >   _errormatrixhist;
    std::vector< std::vector<double>* >  _Diis_Bs;
   
    std::vector<double>                 _totE;
    ub::vector<double>                  _DiF;
    ub::matrix<double>                  _DiFj;
  
    ub::vector<double> ADIIsCoeff();
    
    
 ub::vector<double> compute_c(const gsl_vector * x);
 /// Compute jacobian
 ub::matrix<double> compute_jac(const gsl_vector * x);
 /// Compute energy
 double min_f(const gsl_vector * x, void * params);
 /// Compute derivative
 void min_df(const gsl_vector * x, void * params, gsl_vector * g);
 /// Compute energy and derivative
void min_fdf(const gsl_vector * x, void * params, double * f, gsl_vector * g);

ub::vector<double> DIIsCoeff();
    
    unsigned _nocclevels;
    double _levelshift;
    bool _unrestricted;
    
  
 };
 
 
 namespace adiis {
  /// Compute weights
  ub::vector<double> compute_c(const gsl_vector * x);
  /// Compute jacobian
  ub::matrix<double> compute_jac(const gsl_vector * x);

  /// Compute energy
  double min_f(const gsl_vector * x, void * params);
  /// Compute derivative
  void min_df(const gsl_vector * x, void * params, gsl_vector * g);
  /// Compute energy and derivative
  void min_fdf(const gsl_vector * x, void * params, double * f, gsl_vector * g);
};
    
}}

#endif	

