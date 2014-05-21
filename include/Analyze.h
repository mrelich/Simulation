#ifndef Analyze_h
#define Analyze_h

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
// This class will carry out the analysis by generating the mixed //
// shower profiles and calculating the electric field at the      //
// positions designated by the user in the Detector class. Right  //
// now the electric field calculation is done using Jaime's       //
// near-field parameterization from arxiv:1106.6283. This class   //
// could later be used on a track analysis.                       //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//

// My goodies
#include "Mixer.h"
#include "Dim3.h"
#include "Detectors.h"

// Standard
#include <string>
#include <iostream>
#include <vector>

class Analyze
{

 public:
  
  // Constructor
  Analyze();

  // Destructor
  virtual ~Analyze();


 private:

  //
  // Methods
  //

  // Generate the next event and record
  // the result at the detector positions.


  //
  // Objects
  //

  Dim3* m_dim3;           // Time-domain 3D parameterization
  Mixer* m_mixer;         // Event mixer class
  Detectors* m_detectors; // Detector objects

};

#endif
