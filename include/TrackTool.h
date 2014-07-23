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
#include "TVector3.h"

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
		      double t0);                    // Start time

 private:

  // EField calculation
  double Efield(TVector3* beta,                      // Beta of electron
		TVector3* u,                         // unit vector pointing towards det
		TVector3* detPol,                    // Detectors polarization vector
		double R);                           // Distance to detector

  // Get the time at the detector
  double getTDetector(TVector3* beta,                // Beta of electron 
		      TVector3* u,                   // unit vector pointing toward detector
		      double R,                      // Distance to detector
		      double t,                      // Particle time
		      double t0);                    // Event start time

  // Get Beta given particle properties
  TVector3 getBeta(Particle* part);

  // Get unit vector which points from
  // the middle of track to detector location.
  TVector3 getUnitVector(Particle* part,               // Particle
			 TVector3* detPos);            // Detector position
  
  
  // Get the distance R from midpoint of
  // the track to the detector position
  double getR(Particle* part,                        // Paticle
	      TVector3* detPos);                     // Detector position
  
  

};

#endif
