
#include "Detectors.h"

//--------------------------------------------//
// Initialize the detector array
//--------------------------------------------//
void Detectors::initialize()
{

  // Add detectors here where you need
  // to specify the x,y,z position in m
  addDetector( new Detector(14.55,0,10) );

};
