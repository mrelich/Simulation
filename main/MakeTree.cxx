
#include "TreeMaker.h"

using namespace std;

//---------------------------------------------------//
//                   HELP MENU                       //
//---------------------------------------------------//
void help()
{
  
  cout<<endl;
  cout<<"***************************************************"<<endl;
  cout<<"Options: "<<endl;
  cout<<"\t-n <int>"<<endl;
  cout<<"\t\tSpecify number of events to put in tree"<<endl;
  cout<<"\t-i <filepath>"<<endl;
  cout<<"\t\tSpecify input file path to G4 data"<<endl;
  cout<<"\t-o <outname>"<<endl;
  cout<<"\t\tSpecify the output file name"<<endl;
  cout<<"***************************************************"<<endl;
  cout<<endl;
}

//---------------------------------------------------//
//                     MAIN                          //
//---------------------------------------------------//
int main(int argc, char** argv)
{


  // TODO: Add options
  int nEvent = 0;
  //int nEvent = 1e6;
  string outname = "eBeam_40MeV_1000000_ice";
  //string inname  = "../../IceBlock/tracks/output_1000000000_40_ice_eBeam_np1.dat";
  string inname  = "../../IceBlock/tracks/output_1000000_40_ice_eBeam_np1.dat";

  //
  // Options
  //
  for(int i=1; i<argc; ++i){
    if(strcmp(argv[i],"-n") == 0)
      nEvent = atoi(argv[++i]);
    else if(strcmp(argv[i],"-o") == 0)
      outname = argv[++i];
    else if(strcmp(argv[i],"-i") == 0)
      inname = argv[++i];
    else{
      help();
      return 0;
    }
  }// end loop over options

  // redirect outname to trees directory
  outname = "../trees/" + outname + ".root";

  // Create TreeMaker Object
  TreeMaker* maker = new TreeMaker(outname,inname);

  // Now loop
  maker->loop(nEvent);

  // Delete object, we're done
  delete maker;

  // return 
  return 0.;
}

