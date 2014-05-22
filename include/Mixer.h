#ifndef Mixer_h
#define Mixer_h

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
// This class will read in the text file output from the many shower  //
// simulation and mix them to form the appropriate beam requirements. //
// At first it will simply mix them as if all particles started at    //
// the same time, however we want to be able to put in time (space)   //
// delays between the primaries and the secondaries.  This will just  //
// be a simple offset smeared by some function to be determined.      //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//

// My Stuff
#include "Particle.h"
#include "Event.h"

// Standard
#include <sstream>
#include <stdlib.h>

// Root
#include "TFile.h"
#include "TH1D.h"
#include "TRandom3.h"
#include "TChain.h"

class Mixer
{

 public:

  // Constructor 
  Mixer(float Eprimary,        // Energy of primary [MeV]  
	int nPartPerEvent,     // Specify how to scale the particles
	int nToBeMixed,        // nEvents to mix together
	int totEvents,         // total events in input file
	std::string inname);   // Input file name

  // Destructor
  virtual ~Mixer();


  // Generate a mixed profile
  std::vector<double> generateQz(int nsteps,  // nsteps in the profile
				 float zmin,  // starting point of shower
				 float zmax); // end point of shower

  // Generate single event
  void addSingleQz(int evtNum,                // Random number for event to pick
		   int nsteps,                // nsteps in the profile
		   float zmin,                // starting point of shower
		   float zmax,                 // end point of shower
		   std::vector<double> &Qz);  // Charge excess
  
  // Generate random event number
  int getEventNum();


 private:

  TChain* m_chain;                    // Chain holding events
  Event*  m_event;                    // Event objects
  std::vector<Particle> m_parts;      // Vector to hold particles
  TRandom3* m_rand;                   // Random event number generator
  
  int m_tobemixed;                    // nEvents needed to recreate Edesired
  int m_totEvents;                    // total number of events
  float m_scale;                      // factor to scale each event by

};

#endif
