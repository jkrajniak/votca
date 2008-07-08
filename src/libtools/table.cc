/* 
 * File:   table.cc
 * Author: victorr
 *
 * Created on June 11, 2008, 1:48 PM
 */

#include <fstream>
#include "table.h"

void Table::Load(string filename)
{
    ifstream in;
    in.open(filename.c_str());
    if(!in)
        throw string("error, cannot open file ") + filename;
    
    in >> *this;
    
    in.close();   
}

void Table::Save(string filename) const
{
    ofstream out;
    out.open(filename.c_str());
    if(!out)
        throw string("error, cannot open file ") + filename;
    
    out << (*this);
    
    out.close(); 
}

void Table::ScaleRdf()
{
    for(int i=0; i<_x.size(); ++i)
        if(_x[i]>0)
            _y[i]/=_x[i]*_x[i]*4;
            
}