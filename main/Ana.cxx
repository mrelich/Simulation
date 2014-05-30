
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
// This will contain the main program to be executed. Right now  //
// I will just have many arguments that you have to pass, but    //
// consider for the future having it be done by input txt files. //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//

#include "Analyze.h"

using namespace std;

//--------------------------------------------------------//
// Help
//--------------------------------------------------------//
void help()
{

  cout<<endl;
  cout<<"*************************************************"<<endl;
  cout<<"Analyze help menu:                               "<<endl;
  cout<<" Coming soon                                     "<<endl;
  cout<<"*************************************************"<<endl;
  cout<<endl;

}

//--------------------------------------------------------//
// Main
//--------------------------------------------------------//
int main()
{

  // Options
  double EPrimary   = 40;   // MeV
  int nPartPerEvent = 1.754e5;  // Number of times to reuse same shower
  int nToBeMixed    = 1e2;  // Number of showers to use
  int totEvents     = 1e6;  // Total number of events in input file
  string inputfile  = "";   // The input file
  int nzsteps       = 100;  // Number of steps for shower
  double zmin       = 0;    // Minimum z point [m]
  double zmax       = 1;    // maximum z point [m]
  int ntsteps       = 10000;  // Number of time steps
  double tstepsize  = 0.01;  // Time step size [ns]
  string outputname = "";   // The name to save the output
  int flag          = 0;    // Flag to turn on and off saving output
  
  // To do: Add options to run this job
  // for now I will hard code some test
  // values 
  inputfile  = "showers.root";
  outputname = "output_testbeam350ps.root"; 
  flag |= Opt_SaveProfiles;
  flag |= Opt_SaveVPotential;
  flag |= Opt_SaveEField;

  // Create instance of analyze 
  Analyze* ana = new Analyze();
  
  // Initialize event mixer
  ana->initMixer(EPrimary,nPartPerEvent,
		 nToBeMixed,totEvents,
		 inputfile);
  
  // Initialize the 3D parameterization object
  ana->initDim3();

  // Initialize detector positions
  ana->initDetectors();
  
  // Initialize the showering parameters
  ana->initShowerParams(nzsteps,zmin,zmax);

  // Initialize the timing parameters
  ana->initTimeStepInfo(ntsteps,tstepsize);

  // Initialize the ouput info
  ana->initOutputInfo(outputname, flag);

  // Loop 
  ana->loop();

  delete ana;
  
  return 0;

}
