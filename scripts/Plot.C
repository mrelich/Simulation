
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
// Script to plot the vector potential and the  //
// electric field for various configurations.   //
// This will plot one event at a time.          //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//

#include "myHist.C"
#include "TVirtualFFT.h"

TString savedir = "../plots/AraCollab_Req6m/";
int restrictpulses = 1;
TString savepulse = "1";

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
  //TH1F* h = makeHist("h",1000,100,130,xtitle,ytitle,kBlack,20);
  TH1F* h = makeHist("h",1000,40,65,xtitle,ytitle,kBlack,20);
  h->Fill(-10000);
  if(var == "E"){
    h->SetMaximum(0.2);
    h->SetMinimum(-0.2);
  }
  else{
    h->SetMaximum(1e-11);
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
  //TH1F* h = makeHist("h",30,100,130,xtitle,ytitle,kBlack,20);
  TH1F* h = makeHist("h",30,40,65,xtitle,ytitle,kBlack,20);
  h->Fill(-100000);
  if( var == "E" ){ 
    h->SetMaximum(0.2);
    h->SetMinimum(-0.12);
  }
  else{
    h->SetMaximum(11e-12);
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

  //TFile* output = new TFile("forRomain.root","recreate");
  //gr->SetName("Efield");
  //gr->Write();
  //output->Write();
  //output->Close();

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
  c->SetLogx();
  c->SetLogy();

  // Make a generic histogram
  TString xtitle = "f [MHz]";
  TH1F* h = makeHist("h",10000,0,20000,xtitle,ytitle,kBlack,20);
  h->SetMaximum(2e-4);
  h->SetMinimum(1e-7);
  h->GetXaxis()->SetTitleOffset(1.4);
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
  //for(int np=1; np<=npulses; ++np){
  for(int np=1; np<=restrictpulses; ++np){
    cout<<"Building: "<<np<<endl;
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

  // Now Fourier transform the points
  double ReE[npoints];
  double ImE[npoints];
  double Ef[npoints];
  double freq[npoints];
  int nstep = 2000;
  int step  = 10;
  double pi = TMath::Pi();
  double dt = time[10] - time[9];
  for(int is=0; is<nstep; ++is){
    ReE[is] = 0;
    ImE[is] = 0;
    freq[is] = (is+1)*step;
    for(int ip=0; ip<points; ++ip){
      ReE[is] += E[ip] * cos(2*pi*freq[is]*1e6*time[ip]*1e-9) * dt * 1e-9 * 1e6;
      ImE[is] += E[ip] * sin(2*pi*freq[is]*1e6*time[ip]*1e-9) * dt * 1e-9 * 1e6;
    }

    Ef[is] = sqrt(ReE[is]*ReE[is] + ImE[is]*ImE[is]);
    //cout<<"Re: "<<ReE[is]<<" Im: "<<ImE[is]<<" |E|: "<<Ef[is]<<endl;
  }

  // Make graph
  TGraph* res = new TGraph(nstep, freq, Ef);
  res->Draw("same");

  /*
  TH1* fft = 0;
  TVirtualFFT::SetTransform(0);
  fft = h_E->FFT(fft,"MAG");
  fft->Draw("same");
  */

  // Save
  c->SaveAs((savedir+"EvsF_pulses"+savepulse+".png").Data());

}

