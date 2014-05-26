
#include "Detectors.h"

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
  
};
