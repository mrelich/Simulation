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
#include "SaveOutput.h"

// Standard
#include <string>
#include <iostream>
#include <vector>

// Root
#include "TFile.h"
#include "TH1F.h"
#include "TGraph.h"

enum OutputOptions
{

  Opt_SaveProfiles   = 1 << 0,
  Opt_SaveVPotential = 1 << 1,
  Opt_SaveEField     = 1 << 2

};

class Analyze
{

 public:
  
  // Constructor
  Analyze();

  // Destructor
  virtual ~Analyze();

  // Start the event loop to save results
  void loop();
  

  // Initialize the mixer
  void initMixer(double EPrimary,
		 int nPartPerEvent,
		 int nToBeMixed,
		 int totEvents,
		 std::string inputFile);

  // Initialize the time-domain param object
  // Note: This should be callled after 
  // initMixer(...)
  void initDim3();

  // Initialize detectors.
  // Note: User should add detectors in
  // Detectors.cxx
  void initDetectors();

  // Set the shower parameters
  void initShowerParams(int nsteps,
			float zmin,
			float zmax);

  // Initialize the timing info
  void initTimeStepInfo(int nsteps,
			double stepsize);

  // Initialize output file and options
  void initOutputInfo(std::string fname, int flag);

  // Method to check everything initialized
  bool isOK(){ 
    return m_initMixer        && 
           m_initDim3         &&
           m_initDetectors    && 
           m_initShowerParams &&
           m_initTimeParams   &&
           m_initOutInfo;
  };

 private:

  //
  // Methods
  //

  // Generate the next event and record
  // the result at the detector positions.
  // Remember that the next event consists of
  // multiple showers superimposed.
  void generateEvent(int evtNum);

  // Generate the results from a given pulse
  // that the user has specified. The user must
  // input some pulse offset.
  void generatePulse(float dt, int evtNum);

  // Get the next shower profile 
  void setNextShower();

  //
  // Objects
  //

  Dim3* m_dim3;           // Time-domain 3D parameterization
  Mixer* m_mixer;         // Event mixer class
  Detectors* m_detectors; // Detector objects
  SaveOutput* m_save;     // Object to save output

  //
  // Variables
  //

  bool m_initMixer;
  bool m_initDim3;
  bool m_initDetectors;
  bool m_initShowerParams;
  bool m_initTimeParams;
  bool m_initOutInfo;

  double m_pulseSeparation;   // The seperation in incoming pulses [ns]
  double m_nEvents;           // The number of events to process
  int    m_nPulses;           // The number of pulses to consider
  
  int m_nsteps;               // Number of steps for the profile
  double m_zmin;              // starting point [m]
  double m_zmax;              // ending point for recording [m]
  std::vector<double> m_Qz;   // Shower profile

  int m_tsteps;               // number of timing steps
  double m_tstepSize;         // timing step size
  
  int m_outFlag;              // Flag to determine how to save output
  TFile* m_outfile;           // The output root file

};

#endif
