
#include "Detectors.h"

using namespace std;

//--------------------------------------------//
// Initialize the detector array
//--------------------------------------------//
void Detectors::initialize()
{

  // Specify some threshold to start recording data
  double AThreshold = 1e-11;
  
  // Add detectors here where you need
  // to specify the x,y,z position in m
  addDetector( new Detector(14.55,0,10, AThreshold) );
  
}

//--------------------------------------------//
// Calculate the electrcic field for the
// stored detectors
//--------------------------------------------//
void Detectors::calculateEField()
{

  // Loop over each detector
  for(unsigned int i=0; i<getN(); ++i){
    Detector* det = getDetector(i);
    
    // Get vector potential info
    unsigned int np = det->getN();
    double t0 = 0, t1 = 0, A0 = 0, A1 = 0;
    for(unsigned int ip=0; ip<np-1; ++ip){
      det->getPoint(ip,   t0, A0);
      det->getPoint(ip+1, t1, A1);
      det->addTE(t0, (A1-A0)/((t1-t0)*1e-9));
    }// end loop over A points

    // Print message if no data stored
    if( np == 0 ){
      cout<<"***** In calculateEField *****"<<endl;
      cout<<"Number of points for A is 0."<<endl;
      cout<<"Calc vector potential before"<<endl;
      cout<<"Trying to calc the E field. "<<endl;
    }

  }// end loop over detectors
    
    

}
