#ifndef Detectors_h
#define Detectors_h

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
// The user will place the detectors relative to the beam. These //
// points will be where the measurements are calculated and      //
// stored for the analysis.                                      //
//                                                               //
// NOTE: All coordinates currently are relative to (0,0,0) which //
// is where the particle beam begins in my toy simulation. When  //
// I finally move to the full simulation, I will have to fix a   //
// coordinate system and update here accordingly.                //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//

// My goodies
#include "Detector.h"

// Standard
#include <vector>
#include <iostream>

class Detectors
{
  
 public:
  
  // Default Constructor
  Detectors(){};

  // Destructor
  virtual ~Detectors(){
    for(unsigned int i=0; i<m_detectors; ++i)
      delete m_detectors.at(i);
    m_detectors.clear();
  };

  // Initialize.  This is where the
  // user will place all of their 
  // detectors used in the analysis.
  // TODO: The user will hardcode these...
  // consider making this configurable from
  // some input text file.
  void initialize();


  // Need a method to retrieve the detectors in 
  // order to access the physics info
  std::vector<Detector*> getDetectors(){ return m_detectors; };
  
  // Now access a given detector
  Detector* getDetector(int i){ return m_detectors.at(i); };

  // Need a method to figure out how many
  // detectors have been initialzed for looping
  unsigned int getN(){ return m_detectors.size(); };   

 private:

  // Add a detector
  void addDetector(Detector* d){ m_detectors.push_back(d); };

  std::vector<Detector*> m_detectors;     // Vector to hold the detector locations

  
};


#endif
