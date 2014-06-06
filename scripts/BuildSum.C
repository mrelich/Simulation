
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
// I have had to build the sum for the electric field too  //
// many times now. I should really add this to Detectors   //
// class... as a temporary work around, consolidate this   //
// into one function defined here, so it is done uniformly //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//

#include <sstream>

//-------------------------------------//
// Method to build sum E/A
//-------------------------------------//
TH1F* getSum(TFile* file,         // input file
	     TString Vec,         // Specify E or A
	     int det,             // detector number
	     int evtNum,          // event number
	     int npulses,         // number of pulses
	     bool save=false)
{
  
  // Need to get the base pulse graph so that
  // we can add the others to it.
  stringstream pname;
  pname << Vec << "_det" << det
	<< "_evtNum"   << evtNum
	<< "_pulse0";

  TGraph* temp = (TGraph*) file->Get(pname.str().c_str());
  TH1F* SumV = graphToHist(temp,"SumV");
  int np = temp->GetN();

  // Now have the initial graph, so loop over
  // and up all the remaining graphs.
  double V = 0, t = 0;
  double offset = 0;
  for(int i=1; i<npulses; ++i){
    
    // Reset the name
    pname.str("");
    pname << Vec << "_det" << det
	  << "_evtNum"   << evtNum
	  << "_pulse"    << i;

    // Get the new graph
    cout<<"Adding: "<<pname.str()<<endl;
    temp = (TGraph*) file->Get(pname.str().c_str());
    
    // Loop over points and save them
    for(int n=0; n<np; ++n){
      temp->GetPoint(n,t,V);
      SumV->Fill(t,V);      
    }// end loop over points
  }// end loop over pulses
  
  // Clean up
  delete temp;
  
  // Return 
  return SumV;

}

//-------------------------------------//
// Convert graph into hist
//-------------------------------------//
TH1F* graphToHist(TGraph* gr, TString name)
{

  int npoints = gr->GetN();
  double y=0, x=0;
  double xmin=0; gr->GetPoint(0,xmin,y);
  double xmax=0; gr->GetPoint(npoints-1,xmax,y);

  TH1F* h = new TH1F(name.Data(),"",npoints,xmin,xmax);
  
  for(int n=0; n<npoints; ++n){
    gr->GetPoint(n,x,y);
    h->Fill(x,y);
  }
  
  return h;

}
