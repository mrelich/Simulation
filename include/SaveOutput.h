#ifndef SaveOutput_h
#define SaveOutput_h

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
// Save the output for a given event.  The options for configuring //
// which output to be saved are done in Analyze. The methods here  //
// should be called by Analyze. This is just trying to save things //
// cleanly.                                                        //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//

// My goodies
#include "Detectors.h"

// Standard
#include <string>
#include <vector>
#include <sstream>

// Root
#include "TFile.h"
#include "TH1F.h"
#include "TGraph.h"

class SaveOutput
{

 public:
  
  // Constructor
  SaveOutput(){
    reset();
  };

  // Destructor
  virtual ~SaveOutput(){};

  // Method to reset the pulse counters
  void reset(){
    m_QzCounter = 0;
    m_tACounter = 0;
    m_tECounter = 0;
  };

  // Method to fill charge excess profiles
  void fillQz(std::vector<double> Qz,  // Excess charge
	      int nbins,               // number bins for hist
	      double min,              // Minimum for hist
	      double max,              // Maximum for hist
	      int evtNum,              // Event associated with this Qz
	      TFile* file);            // output file to save in  

  // Method to save vector potential
  void fillA(Detectors* detectors,     // All of the detectors
	     int evtNum,               // Event Number
	     TFile* file);             // output file to save in

  // Method to save E field
  void fillE(Detectors* detectors,     // All of the detectors
	     int evtNum,               // Event Number
	     TFile* file);             // output file to save in


 private:
  
  int m_QzCounter;         // Counter for how many profiles filled
  int m_tACounter;         // Method to plot t vs Vector Potential
  int m_tECounter;         // Method to plot t vs E field

};

#endif
