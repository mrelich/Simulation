
#include "Analyze.h"

using namespace std;

//-----------------------------------------------//
// Constructor
//-----------------------------------------------//
Analyze::Analyze() :
  m_dim3(NULL),
  m_mixer(NULL),
  m_detectors(NULL),
  m_save(NULL),
  m_initMixer(false),
  m_initDim3(false),
  m_initDetectors(false),
  m_initShowerParams(false),
  m_initTimeParams(false),
  m_initOutInfo(false),
  m_pulseSeparation(300e-3), // default 300ps
  m_nEvents(10),
  m_nPulses(10),
  m_nsteps(100),
  m_zmin(0),
  m_zmax(1),
  m_outFlag(0),
  m_outfile(NULL)
{

  // Create tool to save output
  m_save = new SaveOutput();

}

//-----------------------------------------------//
// Destructor
//-----------------------------------------------//
Analyze::~Analyze()
{

  // Delete user objects
  delete m_dim3;
  delete m_mixer;
  delete m_detectors;
  
  // Clean out charge excess
  m_Qz.clear();
  
  // Write output and close file
  m_outfile->Write();
  m_outfile->Close();
  delete m_outfile;
}

//-----------------------------------------------//
// Loop over events
//-----------------------------------------------//
void Analyze::loop()
{

  // Check to make sure everything is intitialzed
  // properly. Otherwise alert user and return
  if( !isOK() ){
    cout<<"There seems to be an error. Not all"<<endl;
    cout<<"objects needed for the analysis are"<<endl;
    cout<<"initialzied. Program will not run"<<endl;
    return;
  }

  // For each event we will store the information
  // in m_detectors.  After each event, we will
  // write that information to an output file.
  for(int iEvt=0; iEvt<m_nEvents; ++iEvt){
    
    // Periodic printing
    if( iEvt % 10 == 0 )
      cout<<"Processing Event: "<<iEvt<<endl;
    
    // Reset output for saving
    m_save->reset();

    // Generate the next event
    generateEvent(iEvt);

    // Add code here to save results

  }// end loop over events

  // Let the user know that we are done here
  cout<<"---- Program finished successfully ----"<<endl;

}

//-----------------------------------------------//
// Generate a given event
//-----------------------------------------------//
void Analyze::generateEvent(int evtNum)
{

  // In here we need to loop over the number of
  // pulses in a given bunch, correctly offsetting
  // their start time by dt.
  for(int iP=0; iP<m_nPulses; ++iP)
    generatePulse(iP*m_pulseSeparation,evtNum);
  

}

//-----------------------------------------------//
// Generate a pulse that is a part of the beam
//-----------------------------------------------//
void Analyze::generatePulse(float dt, int evtNum)
{

  // Generate a new profile
  setNextShower();

  // Check if we should record the shower info
  if(m_outFlag & Opt_SaveProfiles)
    m_save->fillQz(m_Qz,m_nsteps,m_zmin,m_zmax,
		   evtNum,m_outfile);		   

  // Calculate the relevant quantities for the 
  // given detector positions 
  unsigned int nDet = m_detectors->getN();
  double t=0, A=0;
  double stepSize = (m_zmax - m_zmin)/m_nsteps;
  for(unsigned int iD=0; iD<nDet; ++iD){
    Detector* det = m_detectors->getDetector(iD);
    
    // Loop over the points to save time
    for(int it=0; it<m_tsteps; ++it){
    
      // record time and vector potential
      t = m_tstepSize * it + dt;       
      A = m_dim3->getANF(t * 1e-9,      // put time in s
			 det->getZ(),   // detector z position
			 det->getR(),   // detector radial position
			 m_Qz,          // Qz distribution
			 stepSize);     // step size in z
			 
      // Save this timing information to a given detector
      det->addTA(t,A);
      
    }// end loop over time steps
    
  }// end loop over detectors

  // Now we have the pulse results. I will
  // save results to TGraphs.  Maybe this 
  // isn't best place. think about it...
  m_save->fillA(m_detectors, evtNum, m_outfile);
  
  // Now clear the detectors since we have
  // filled already for that time.
  m_detectors->clearData();

}

//-----------------------------------------------//
// Set the next shower profile
//-----------------------------------------------//
void Analyze::setNextShower()
{
  m_mixer->generateQz(m_nsteps,m_zmin,m_zmax,m_Qz);
}

//-----------------------------------------------//
// Initialize the mixer
//-----------------------------------------------//
void Analyze::initMixer(double EPrimary,
			int nPartPerEvent,
			int nToBeMixed,
			int totEvents,
			string inputFile)
{

  // Initialize the mixer
  m_mixer = new Mixer(EPrimary,
		      nPartPerEvent,
		      nToBeMixed,
		      totEvents,
		      inputFile);

  m_initMixer = true;

}

//-----------------------------------------------//
// Initialize the Dim3 parameterization
//-----------------------------------------------//
void Analyze::initDim3()
{

  if( m_initMixer ){ 
    m_dim3 = new Dim3(m_mixer->getShowerEMeV() / 1.e6);
    m_initDim3 = true;
  }
  else
    cout<<"Error: Mixer must be initialized before Dim3"<<endl;

}

//-----------------------------------------------//
// Initialize the detectors
//-----------------------------------------------//
void Analyze::initDetectors()
{
  
  // Create detector objects
  m_detectors = new Detectors();
  m_detectors->initialize();

  m_initDetectors = true;

}

//-----------------------------------------------//
// Initialize the holders for charge profile
//-----------------------------------------------//
void Analyze::initShowerParams(int nsteps,
			       float zmin,
			       float zmax)
{

  m_nsteps = nsteps;
  m_zmin   = zmin;
  m_zmax   = zmax;
  
  m_Qz = vector<double> (m_nsteps, 0);
  cout<<"initialized with size: "<<m_Qz.size()<<endl;
  m_initShowerParams = true;
}

//-----------------------------------------------//
// Initialize the time loop information
//-----------------------------------------------//
void Analyze::initTimeStepInfo(int nsteps,
			       double stepsize)
{

  m_tsteps    = nsteps;
  m_tstepSize = stepsize;

  m_initTimeParams = true;

}

//-----------------------------------------------//
// Initialize the ouptut file and flag
//-----------------------------------------------//
void Analyze::initOutputInfo(string fname, int flag)
{

  m_outfile  = new TFile(fname.c_str(),"recreate");
  m_outFlag = flag;

  m_initOutInfo = true;

}
