#ifndef TrackTool_h
#define TrackTool_h

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
// This class will keep methods necessary to calculate the electric  //
// field from tracks using two methods:                              //
//        1.) ZHS formalism -- Middle point method                   //
//        2.) CoREAS formalism -- End points method                  //
// At first I will just go with ZHS in order to get something up and //
// running to compare with ZHS.                                      //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//

#include "Particle.h"
#include "Detectors.h"

class TrackTool
{

 public:

  // Constructor
  TrackTool();
  
  // Destructor
  virtual ~TrackTool();

  // Method to calculate the vector potential
  // from a set of particles using the ZHS 
  // middle point method
  void EfieldZHSStyle(std::vector<Particle*> parts,  // input particles
		      Detectors* dets,               // detectors
		      float tOffset);                // time offset

 private:
  
  // Get the time at the detector
  double getTDetector(TVector3* beta,                // Beta of electron 
		      TVector3* u,                   // unit vector pointing toward detector
		      double t);                     // Particle time
  
  // Get Beta given particle properties
  double getBeta(Particle* part);

  // Get unit vector


};

#endif
