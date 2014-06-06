
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
// Trying to convince group that modulations are expected even    //
// when there are 0s in the pulse.  Try to do this using a square //
// pulse.                                                         //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//

#include "myHist.C"
#include <sstream>

//-----------------------------//
// Main
//-----------------------------//
void SquarePulse()
{
  
  // Make Canvas
  TCanvas* c = makeCanvas("c");
  
  // Make a pulse
  TH1F* pulse = makePulse("p0",kBlack,20,1.3);
  pulse->SetMinimum(-1);
  pulse->Draw();

  // Now get some functions
  vector<TF1*> funcs;
  funcs.push_back( getFit("f0",20) );
  //funcs.push_back( getFit("f1",10) );
  //funcs.push_back( getFit("f2",100) );

  // Colors
  int colors[] = {kRed, kBlue, kMagenta, kGreen};

  // Fit thos functions
  for(unsigned int i=0; i<funcs.size(); ++i){
    TF1* function = funcs.at(i);
    pulse->Fit(function->GetName(),"");
    function->SetLineWidth(2);
    function->SetLineColor(colors[i]);
    function->Draw("same");
  }
  
}

//-----------------------------//
// Get fit function
//-----------------------------//
TF1* getFit(TString name, int nmodes)
{
  
  // Build function
  stringstream func;
  for(int i=0; i<=nmodes; ++i){
    if(i==0) func <<" [0] ";
    else func << "[" << i << "]*sin(" << i << "*x/4.)";

    if( i!=nmodes ) func <<"+";
  }

  cout<<func.str()<<endl;

  // Make the TF1 object
  TF1* function = new TF1(name.Data(),func.str().c_str(),0,10);
  for(int i=0; i<nmodes; ++i){
    function->SetParameter(i,3);
  }

  return function;

}

//-----------------------------//
// Make square pulse
//-----------------------------//
TH1F* makePulse(TString name,
		int color,
		int marker,
		float Amplitude)
{
  
  // Make hist
  TH1F* pulse = makeHist(name,100000,0,10,"time [s]", "Ampltiude", color, marker);
  
  // Fill histogram
  int nbins = pulse->GetNbinsX();
  for(int bin=1; bin<=nbins; ++bin){
    float bc = pulse->GetBinCenter(bin);
    if( 3 < bc && bc < 7 )
      pulse->Fill(bc, Amplitude);
    else
      pulse->Fill(bc,0);
  }
  
  return pulse;

}

