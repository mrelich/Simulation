
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
// Script to plot the vector potential and the  //
// electric field for various configurations.   //
// This will plot one event at a time.          //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//

#include "myHist.C"
#include "TVirtualFFT.h"

TString savedir = "../plots/";

//--------------------------------//
// Main
//--------------------------------//
void Plot(TString fpath,
	  int event,
	  int npulses,
	  int opt,
	  bool logy=false)
{

  // Decide what to plot based on the options
  if(opt == 0)
    PlotSingle(fpath,event,npulses,"E","|E(t)| [Vm^{-1}]",false);
  else if(opt == 1)
    PlotSingle(fpath,event,npulses,"A","|A(t)| [Vm^{-1}s]",logy);
  else if(opt == 2)
    PlotSum(fpath,event,npulses,"E","|E(t)| [Vm^{-1}]",false);
  else if(opt == 3)
    PlotSum(fpath,event,npulses,"A","|A(t)| [Vm^{-1}s]",logy);
  else if(opt == 4)
    PlotEw(fpath,event,npulses,"|E(#omega)| [Vm^{-1}MHz^{-1}]");
  else{
    cout<<"Option not supported"<<endl;
    printOptions();
  }

}

//--------------------------------//
// Print the options
//--------------------------------//
void printOptions()
{

  cout<<"\topt=0 -- Plot Single E"<<endl;
  cout<<"\topt=1 -- Plot Single A"<<endl;
  cout<<"\topt=2 -- Plot Sum E"<<endl;
  cout<<"\topt=3 -- Plot Sum A"<<endl;
  cout<<"\topt=4 -- Plot FFT of E"<<endl;

}

//--------------------------------//
// Plot each single E from beam
//--------------------------------//
void PlotSingle(TString fpath,
		int event,
		int npulses,
		TString var,
		TString ytitle,
		bool logy)
{
  // Open up the rootfile
  TFile* file = new TFile(fpath.Data());

  // Canvas
  TCanvas* c = makeCanvas("c");
  if(logy) c->SetLogy();

  // Make a generic histogram
  TString xtitle = "time [ns]";
  TH1F* h = makeHist("h",1000,100,130,xtitle,ytitle,kBlack,20);
  if(var == "E"){
    h->SetMaximum(0.1);
    h->SetMinimum(-0.1);
  }
  else{
    h->SetMaximum(4e-12);
    h->SetMinimum(1e-15);
  }
  h->Draw();

  stringstream ss;
  ss << var << "_det0_evtNum" << event << "_pulse";
  string base = ss.str();
  for(int np=1; np<=npulses; ++np){
    ss.str(""); ss << base << np;
    TGraph* gr = (TGraph*) file->Get(ss.str().c_str());
    gr->Draw("same");
    
  }// end loop over pulses

  // Save
  TString save = savedir + "Single" + var;
  if(logy) save += "_logy";
  save += ".png";
  c->SaveAs(save.Data());
  

}


//--------------------------------//
// Plot each single A from beam
//--------------------------------//
void PlotSum(TString fpath,
	     int event,
	     int npulses,
	     TString var,
	     TString ytitle,
	     bool logy)
{
  // Open up the rootfile
  TFile* file = new TFile(fpath.Data());
  
  // Canvas
  TCanvas* c = makeCanvas("c");
  if(logy) c->SetLogy();

  // Make a generic histogram
  TString xtitle = "time [ns]";
  TH1F* h = makeHist("h",30,100,130,xtitle,ytitle,kBlack,20);
  if( var == "E" ){ 
    h->SetMaximum(0.1);
    h->SetMinimum(-0.1);
  }
  else{
    h->SetMaximum(5e-12);
    h->SetMinimum(1e-15);
  }
  h->Draw();

  // Make place holders for TGraph
  const int npoints = 100000;
  Double_t time[npoints];
  Double_t V[npoints];
  int points = 0;
  for(int n=0; n<npoints; ++n){
    time[n] = 0; V[n] = 0;
  }
    
  // String stream to build name
  stringstream ss;
  ss << var << "_det0_evtNum" << event << "_pulse";
  string base = ss.str();

  // Initialize TGraph and loop
  TGraph* gr = NULL;
  for(int np=1; np<=npulses; ++np){
    ss.str(""); ss << base << np;
    gr = (TGraph*) file->Get(ss.str().c_str());
    
    // Get Points
    points = gr->GetN();
    double x=0, y=0;
    for(int n=0; n<points; ++n){
      gr->GetPoint(n,x,y);
      V[n] += y;
      if(np==1) time[n] = x;
    }

    delete gr;
  }// end loop over pulses

  // Make graph of sum
  gr = new TGraph(points, time, V);
  gr->Draw("same");

  // Save
  TString save = savedir + "Sum" + var;
  if(logy) save += "_logy";
  save += ".png";
  c->SaveAs(save.Data());

}

//--------------------------------//
// Plot E(w)
//--------------------------------//
void PlotEw(TString fpath,
	    int event,
	    int npulses,
	    TString ytitle)
{
  // Open up the rootfile
  TFile* file = new TFile(fpath.Data());
  
  // Canvas
  TCanvas* c = makeCanvas("c");

  // Make a generic histogram
  TString xtitle = "f [MHz]";
  TH1F* h = makeHist("h",10000,0,2000,xtitle,ytitle,kBlack,20);
  h->SetMaximum(5);
  h->SetMinimum(0);
  h->Draw("");

  TH1F* h_E = makeHist("h_E",10000,0,200,xtitle,ytitle,kBlack,20);
  
  // Make place holders for TGraph
  const int npoints = 100000;
  Double_t time[npoints];
  Double_t E[npoints];
  int points = 0;
  for(int n=0; n<npoints; ++n){
    time[n] = 0; E[n] = 0;
  }
    
  // String stream to build name
  stringstream ss;
  ss << "E_det0_evtNum" << event << "_pulse";
  string base = ss.str();

  // Initialize TGraph and loop
  TGraph* gr = NULL;
  for(int np=1; np<=npulses; ++np){
    ss.str(""); ss << base << np;
    gr = (TGraph*) file->Get(ss.str().c_str());
    
    // Get Points
    points = gr->GetN();
    double x=0, y=0;
    for(int n=0; n<points; ++n){
      gr->GetPoint(n,x,y);
      E[n] += y;
      h_E->Fill(x,y);
      if(np==1) time[n] = x;
    }

    delete gr;
  }// end loop over pulses

  TH1* fft = 0;
  TVirtualFFT::SetTransform(0);
  fft = h_E->FFT(fft,"MAG");
  fft->Draw("same");

}

