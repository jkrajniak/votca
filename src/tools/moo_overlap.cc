//
// File:   moo_oeralp.cc
// calculates overlap integrals for molecular orbitals using libmoo
// moo_overlap --pos1 <coordinate file for mol1>
//			--pos2 <coordinate file for mol2>
//			--conjseg <xml file defining conjugated segments>
//			--pdb geometry in which electronic coupling si calculated

#include <boost/program_options.hpp>
#include <string>
#include <votca/moo/jcalc.h>
#include <votca/moo/crgunit.h>
#include <votca/tools/application.h>

using namespace std;

class MOOApplication
	: public Application
{
public:
	    virtual string ProgramName() { return "moo_overlap"; }
	    virtual void HelpText(std::ostream &out) { };
	    void Initialize();
	    bool EvaluateOptions();
	    void Run(void);
protected: 		
	    string _conjseg, _pos1, _pos2, _pdbfile;
};

void MOOApplication::Initialize()
{
	AddProgramOptions("MOO Options")
		("conjseg", boost::program_options::value<string>(), " xml file describing two conjugated segments")
		("pos1", boost::program_options::value<string>(), " position and orientation of molecule 1")
		("pos2", boost::program_options::value<string>(), " position and orientation of molecule 2")		
		("pdb", boost::program_options::value<string>()->default_value("geometry.pdb"), " pdb file of two molecules")		
		;
}

bool MOOApplication::EvaluateOptions()
{
	CheckRequired("conjseg");
	_conjseg = OptionsMap()["conjseg"].as<string>();
	_pos1 = OptionsMap()["pos1"].as<string>();
	_pos2 = OptionsMap()["pos2"].as<string>();
	_pdbfile = OptionsMap()["pdb"].as<string>();
	return true;
}

void MOOApplication::Run(void)
{
        //cout << "Reading Crg unit Types" << endl;
        JCalc jcalc(_conjseg);
        //cout << "Finished reading Crg unit Types" << endl;

        ifstream in1(_pos1.c_str());
        ifstream in2(_pos2.c_str());
        int written=0;
        while (in1 && in2) {
            string name1, name2;
            vec com1;
            vec com2;
            matrix or1;
            matrix or2;
            in1 >> name1 >> com1.x() >> com1.y() >> com1.z() >>
                    or1[0][0] >> or1[0][1] >> or1[0][2] >>
                    or1[1][0] >> or1[1][1] >> or1[1][2] >>
                    or1[2][0] >> or1[2][1] >> or1[2][2];
            in2 >> name2 >> com2.x() >> com2.y() >> com2.z() >>
                    or2[0][0] >> or2[0][1] >> or2[0][2] >>
                    or2[1][0] >> or2[1][1] >> or2[1][2] >>
                    or2[2][0] >> or2[2][1] >> or2[2][2];

            if (!in1 || !in2) break;
            //	cout << "mol1: " << name1 << com1 << or1<<endl;
            //	cout << "mol2: " << name2 << com2 << or2<<endl;


            CrgUnit * A = jcalc.CreateCrgUnit(0, name1);
            CrgUnit * B = jcalc.CreateCrgUnit(1, name2);
            A->SetPos(0, com1);
            B->SetPos(0, com2);
            A->SetNorm(0, or1[2]);
            A->SetPlane(0, or1[1]);
            B->SetNorm(0, or2[2]);
            B->SetPlane(0, or2[1]);


           //write pdb file
           mol_and_orb *molecule = ( A -> rotate_translate_beads() );
           (*molecule).write_pdb(_pdbfile, "m1", written);
           written += (*molecule).getN();
           delete molecule;
           molecule = ( B -> rotate_translate_beads() );
           (*molecule).write_pdb(_pdbfile, "m2", written);
           written += (*molecule).getN();
           delete molecule;
           ofstream fl;
           fl.open(_pdbfile.c_str(), ios::app);
           fl.setf(ios::fixed);
           fl << "END" <<endl;

           
            //	cout << "Compute J" <<endl;
            vector <double> Js = jcalc.CalcJ(*A, *B);
            //	cout << "Finished computing J" <<endl;
            vector <double>::iterator itJ = Js.begin();
            for (; itJ != Js.end(); ++itJ) cout << '\t' << *itJ << endl;
	};
}

int main(int argc, char **argv)
{
	MOOApplication app;
	return app.Exec(argc, argv);
}
