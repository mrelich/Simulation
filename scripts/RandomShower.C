
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
// Need to plot some formatted showers.  //
// Just plot 3 to illustrate the results //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//

#include "myHist.C"

TString savedir = "../plots/sep350ps/";

//------------------------//
// Main
//------------------------//
void RandomShower()
{

  // input file
  //TFile* file = new TFile("output_testbeam.root");
  TFile* file = new TFile("output_testbeam350ps.root");

  vector<TString> pnames;
  pnames.push_back("Qz_event0_pulse0");
  pnames.push_back("Qz_event0_pulse10");
  pnames.push_back("Qz_event0_pulse20");
  
  vector<TString> names;
  names.push_back("Pulse 0");
  names.push_back("Pulse 1");
  names.push_back("Pulse 2");

  // Attributes
  int colors[] = {kBlack, kRed, kBlue};
  TString xt = "z [cm]";
  TString yt = "Charge Excess";

  // Make canvas
  TCanvas* c = makeCanvas("c");
  
  // Legend
  TLegend* leg = makeLegend(0.7,0.85,0.80,0.9);

  // Loop and plot
  TProfile* prof = NULL;
  for(unsigned int i=0; i<pnames.size(); ++i){
    TString pname = pnames.at(i);
    TString name  = names.at(i);
    
    prof = getProfile(file,pname,xt,yt,colors[i],20);
    leg->Clear();
    leg->AddEntry(prof,name.Data(),"l");
    prof->Draw();
    leg->Draw("same");
    c->SaveAs((savedir+pname+".png").Data());
  }

  
}
