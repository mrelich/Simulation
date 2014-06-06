
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
// Don't fully understand the Fourier properties of    //
// pulse, so I want to study the effect in more detail //
// using a single pulse and shifting it in time.       //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//

#include "myHist.C"

TString savedir = "../plots/FourierStudy/";

//----------------------------------------//
// Main
//----------------------------------------//
void FourierStudy()
{
  
  // Specify the input file
  TFile* file = new TFile("output_Req6m_AraCollab.root");
  
  // Plot single Fourier part from two pulses
  //plotSingleFourier(file);
  plotMultipleFourier(file);
  //plotPulses(file);

}

//----------------------------------------//
// Plot Single Fourier
//----------------------------------------//
void plotSingleFourier(TFile* file)
{

  // Make canvas
  TCanvas* c = makeCanvas("c");
  c->SetLogy();
  c->SetLogx();

  // Specify the plot and load it
  TString pname = "E_det0_evtNum0_pulse1";
  TGraph* Efield = (TGraph*) file->Get(pname.Data());
  
  // Specify the points to consider for fourier transform
  int npoints = 1000;
  float step  = 10;
  
  TGraph* fourier = getFT(npoints,step,Efield);

  fourier->Draw();

}

//----------------------------------------//
// Plot multiple plots
//----------------------------------------//
void plotMultipleFourier(TFile* file)
{

  // Make canvas
  TCanvas* c = makeCanvas("c");
  //c->SetLogy();
  //c->SetLogx();

  // Specify the plot and load it
  TString pname = "E_det0_evtNum0_pulse1";
  TGraph* Efield = (TGraph*) file->Get(pname.Data());

  // Specify the offsets and build the graphs
  const int noffset = 5;
  int offsetStep    = 4; // ns
  TGraph* fourier[noffset];
  int colors[] = {kBlack, kRed, kBlue, kMagenta, kGreen};

  TString xtitle = "f [MHz]";
  TString ytitle = "|E(#omega)| [V MHz^{-1} m^{-1}]";

  // Loop
  for(int i=0; i<noffset; ++i){

    // Clone the graph as a placeholder
    TGraph* SumEField = (TGraph*) Efield->Clone();
    addOffset(SumEField, Efield, i*offsetStep);
  
    // Specify the points to consider for fourier transform
    int npoints = 1000;
    float step  = 10;  
    fourier[i] = getFT(npoints,step,SumEField);
    format(fourier[i],xtitle,ytitle,colors[i]);

    // Delete sum
    delete SumEField;

  }

  // Now loop and plot
  fourier[0]->Draw();
  for(int i=1; i<noffset; ++i)
    fourier[i]->Draw("same");

}

//----------------------------------------//
// Draw Pulses
//----------------------------------------//
void plotPulses(TFile* file)
{

  // Make canvas
  TCanvas* c = makeCanvas("c");

  // Specify the plot and load it
  TString pname = "E_det0_evtNum0_pulse1";
  TGraph* Efield = (TGraph*) file->Get(pname.Data());  

  // Specify the offsets and build the graphs
  int noffset    = 1;
  int offsetStep = 5; // ns

  // Labels and shiz
  TString xtitle = "time [ns]";
  TString ytitle = "|E(t)| [V m^{-}]";

  // Loop and make plot
  stringstream save;
  for(int i=0; i<noffset; ++i){

    // Clone the graph as a placeholder
    TGraph* SumEField = (TGraph*) Efield->Clone();
    addOffset(SumEField, Efield, ((i+1)*offsetStep));

    // Draw pulses to test
    format(SumEField, xtitle, ytitle, kBlack);
    format(SumEField, xtitle, ytitle, kRed);
    SumEField->Draw();
    Efield->Draw("same");

    // Now save
    save.str("");
    save << savedir << "OffsetCheck_" << (i*offsetStep) << "ns.png";
    c->SaveAs(save.str().c_str());
    delete SumEField;
  }

}

//----------------------------------------//
// Format graph
//----------------------------------------//
void format(TGraph* &gr, TString xtitle,
	    TString ytitle, int color)
{

  gr->SetTitle("");
  gr->GetYaxis()->SetTitle(ytitle.Data());
  gr->GetXaxis()->SetTitle(xtitle.Data());
  gr->SetLineColor(color);
  gr->GetYaxis()->SetTitleOffset(1.5);
  
}

//----------------------------------------//
// Add another offset
//----------------------------------------//
void addOffset(TGraph* &gr, TGraph* added, 
	       int offset)
{

  // Get Npoints
  int np = gr->GetN();

  // Specify place holders
  double E0=0, t0=0;
  double E1=0, t1=0;
  
  // Figure out the number of steps to ignore
  double dt = 0; gr->GetPoint(1,dt,E0);
  gr->GetPoint(2,t0,E0);
  dt = t0 - dt;
  int npIgnore = (int) offset/dt;
  cout<<"Number to ignore: "<<npIgnore<<endl;

  // Now loop over and add to the existing
  // points in the graph
  for(int ip=0; ip<np; ++ip){
    gr->GetPoint(ip,t0,E0);
    t1 = E1 = 0;
    if( npIgnore <= ip )
      added->GetPoint(ip-npIgnore,t1,E1);
    
    // Reset point
    gr->SetPoint(ip,t0,E0+E1);
  }// end loop over points

}

//----------------------------------------//
// Make Fourier Transform
//----------------------------------------//
TGraph* getFT(const int npoints, 
	      const float step,
	      TGraph* SumE)
{

  // Make place holders
  Double_t ReE[npoints];
  Double_t ImE[npoints];
  Double_t Ef[npoints];
  Double_t freq[npoints];
  double E=0, t=0;
  int np = SumE->GetN();
  Double_t pi = TMath::Pi();
  int filledPoints = 0;

  // Get the time step from the graph
  double dt = 0; SumE->GetPoint(2,dt,E);
  SumE->GetPoint(3,t,E);
  dt = t - dt;  

  // Now loop and calculate the values
  for(int is=0; is<npoints; ++is){
    ReE[is]  = 0;
    ImE[is]  = 0;
    freq[is] = (is+1)*step;
    filledPoints += 1;

    // Now loop over graph points to 
    // get the integral for this freq
    for(int ip=0; ip<np; ++ip){
      SumE->GetPoint(ip,t,E);
      ReE[is] += E * cos(2*pi*freq[is]*1e6*t*1e-9) * dt * 1e-9 * 1e6;
      ImE[is] += E * sin(2*pi*freq[is]*1e6*t*1e-9) * dt * 1e-9 * 1e6;
    }// loop over time and points

    Ef[is] = sqrt(ReE[is]*ReE[is] + ImE[is]*ImE[is]);
    
  }// end loop over frequency points
  
  
  TGraph* gr = new TGraph(filledPoints, freq, Ef);

  return gr;
}
