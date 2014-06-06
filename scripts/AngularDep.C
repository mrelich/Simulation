
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
// One thing we want to know is the angular dependence to     //
// compare with simple formula from the Askarayan measurement //
// from SLAC.                                                 //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//

#include "myHist.C"
#include <sstream>
#include "BuildSum.C"

// Need to add metadata to the detector class
// so that when writing information I will know
// where the detectors are placed.  Until that
// happens, hardcode here for now.
const int ndet   = 90;
double angleStep = 1; // degree
//const int ndet   = 9;
//double angleStep = 10; // degree

// Specify the number of pulses that are used
// could probably do this more dynamically
// but we can safely assume we have 57
const int npulses = 57;

TString savedir = "../plots/AngularDep/";

//----------------------------------------//
// Main
//----------------------------------------//
void AngularDep(TString fname, int opt)
{
  
  // Specify the file
  TFile* file = new TFile(fname.Data());


  // Plot single
  if(opt == 0)
    plotSingle(file);
  else if(opt == 1)
    plotSum(file);

}

//----------------------------------------//
// Plot for a single pulse for comparison
//----------------------------------------//
double plotSingle(TFile* file)
{

  // Make canvas
  TCanvas* c = makeCanvas("c");
  c->SetLogy();

  // Specify the placeholders
  double Ew[ndet];
  double angle[ndet];

  // Specify the labels for the TGraphs
  TString xtitle = "Angle [deg]";
  TString ytitle = "|E(f)| [V m^{-1} MHz^{-1}]";
  int colors[] = {kBlack, kRed, kBlue, kMagenta};

  // Make a frame histogram
  // Make a frame histogram
  TH1F* h = makeHist("h",1000,0,90,xtitle,ytitle,kBlack,20);
  h->SetMinimum(1e-8);
  h->SetMaximum(3e-5);
  h->Draw();

  // Specify the frequency here
  vector<double> freqs;
  //freqs.push_back(200);
  //freqs.push_back(400);
  //freqs.push_back(600);
  //freqs.push_back(800);
  freqs.push_back(1000);
  freqs.push_back(1500);
  freqs.push_back(2000);
  freqs.push_back(2500);

  // Make legend
  TLegend* leg = makeLegend(0.15,0.3,0.7,0.9);

  // Loop over frequencies
  for(unsigned int f=0; f<freqs.size(); ++f){
    double freq = freqs.at(f);
    
    // Loop over points and
    stringstream pname;
    TGraph* gr_E = NULL;
    for(int i=0; i<ndet; ++i){
      
      // Create det name
      pname.str("");
      pname << "E_det" << i << "_evtNum0_pulse1";
      
      // Load the graph
      gr_E = (TGraph*) file->Get(pname.str().c_str());
      
      // Save information
      angle[i] = i * angleStep;
      Ew[i]    = getFT(gr_E, freq);
    
    }// now have angular plot
    
    // Make graph
    TGraph* gr_Ang = new TGraph(ndet, angle, Ew);
    formatGraph(gr_Ang, xtitle, ytitle, colors[f]);
   
    // Add graph to legend
    leg->AddEntry(gr_Ang,Form("f = %3.0f MHz",freq),"l");
 
    // Draw
    gr_Ang->Draw("same");

  }

  leg->Draw("same");
  
  // Save the single pulse results
  c->SaveAs((savedir + "singlePulse_highFreq.png").Data());

}

//----------------------------------------//
// Plot for a single pulse for comparison
//----------------------------------------//
double plotSum(TFile* file)
{

  // Make canvas
  TCanvas* c = makeCanvas("c");
  c->SetLogy();

  // Specify the placeholders
  double Ew[ndet];
  double angle[ndet];

  // Specify the labels for the TGraphs
  TString xtitle = "Angle [deg]";
  TString ytitle = "|E(f)| [V m^{-1} MHz^{-1}]";
  int colors[] = {kBlack, kRed, kBlue, kMagenta};

  // Make a frame histogram
  TH1F* h = makeHist("h",1000,0,90,xtitle,ytitle,kBlack,20);
  h->SetMinimum(1e-8);
  h->SetMaximum(3e-5);
  h->Draw();

  // Specify the frequency here
  vector<double> freqs;
  //freqs.push_back(200);
  //freqs.push_back(400);
  //freqs.push_back(600);
  //freqs.push_back(800);
  freqs.push_back(1000);
  freqs.push_back(1500);
  freqs.push_back(2000);
  freqs.push_back(2500);

  // Make legend
  TLegend* leg = makeLegend(0.15,0.3,0.7,0.9);

  // Loop over frequencies
  for(unsigned int f=0; f<freqs.size(); ++f){
    double freq = freqs.at(f);
    
    // Loop over points and
    stringstream pname;
    TGraph* gr_E = NULL;
    for(int i=0; i<ndet; ++i){
      
      // Create det name
      pname.str("");
      pname << "E_det" << i << "_evtNum0_pulse1";
      
      // Load the graph
      //gr_E = getSumE(file,i,0, (f==0));
      gr_E = getSum(file,"E",i,0,npulses);
      
      // Save information
      angle[i] = i * angleStep;
      Ew[i]    = getFT(gr_E, freq);
    
      // Delete this graph
      delete gr_E;

    }// now have angular plot
    
    // Make graph
    TGraph* gr_Ang = new TGraph(ndet, angle, Ew);
    formatGraph(gr_Ang, xtitle, ytitle, colors[f]);
   
    // Add graph to legend
    leg->AddEntry(gr_Ang,Form("f = %3.0f MHz",freq),"l");
 
    // Draw
    gr_Ang->Draw("same");
    
  }

  leg->Draw("same");
  
  // Save the single pulse results
  //c->SaveAs((savedir + "sumPulses.png").Data());
  //c->SaveAs((savedir + "sumPulses_highFreq.png").Data());

}

//----------------------------------------//
// Get the sum of the electric field
//----------------------------------------//
TGraph* getSumE(TFile* file, int det,
		int evtNum, bool save)
{

  // Specify a string stream to construct 
  // graph names to read from the file
  stringstream pname;
  pname << "E_det" << det 
	<< "_evtNum" << evtNum
	<< "_pulse1"; 
  TGraph* SumE = (TGraph*) file->Get(pname.str().c_str());
  int np = SumE->GetN();

  // Now I have the intial graph so loop
  // over the remainder and add them up
  double Esum = 0, tsum = 0;
  double E = 0, t = 0;
  TGraph* gr = NULL;
  for(int i=2; i<=npulses; ++i){
    
    // Reset the pname
    pname.str("");
    pname << "E_det" << det 
	  << "_evtNum" << evtNum
	  << "_pulse" << i;
    
    // Get new graph
    gr = (TGraph*) file->Get(pname.str().c_str());
    
    // Add these points
    for(int n=0; n<np; ++n){
      SumE->GetPoint(n,tsum,Esum);
      gr->GetPoint(n,t,E);
      
      SumE->SetPoint(n,tsum,Esum+E);
    }
  }// end loop over npulses

  // Draw the sum and save
  if(save){
    TCanvas* cSum = makeCanvas("cSum");
    int low = SumE->GetXaxis()->FindBin(35);
    int high = SumE->GetXaxis()->FindBin(70);
    SumE->GetXaxis()->SetRange(low,high);
    SumE->Draw();
    pname.str(""); pname << "det" << det << ".png";
    cSum->SaveAs((savedir+"sumPlots/"+TString(pname.str().c_str())).Data());
    delete cSum;
  }

  return SumE;
}

//----------------------------------------//
// Get fourier transform for given freq
//----------------------------------------//
double getFT(TGraph* EField, double f)
{

  double Real = 0;
  double Imag = 0;
  double E=0, t=0;
  double np = EField->GetN();
  double dt = 0;
  EField->GetPoint(2,dt,E);
  EField->GetPoint(1,t,E);
  dt -= t;
  double pi = TMath::Pi();

  // Integrate over Efield
  for(int n=0; n<np; ++n){
    EField->GetPoint(n,t,E);
    Real += E * dt * 1e-9 * cos(2*pi*f*1e6*t*1e-9) * 1e6;
    Imag += E * dt * 1e-9 * sin(2*pi*f*1e6*t*1e-9) * 1e6;
  }// end loop over points

  // Return the fourier transform 
  // for this frequency
  return sqrt(Real*Real + Imag*Imag);
}
