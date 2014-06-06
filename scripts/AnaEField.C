
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
// Quick electric field calculation from the paper measuring //
// Askaryan effect at SLAC.                                  //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//

#include "myHist.C"
#include "TF1.h"

//------------------------------------//
// Main
//------------------------------------//
void AnaEField()
{

  // Make Canvas 
  TCanvas* can = makeCanvas("can");
  can->SetLogy();
  can->SetGridx();
  can->SetGridy();

  // Define the function here with parameters:
  // [0] = L
  // [1] = freq
  // [2] = k
  // [3] = n
  // [4] = sqrt(2pi) * mu * mu0
  TString func = "[4]*[0]*[1]*sin(x/57.2957)*exp(-pow([2]*[0],2)*pow(cos(x/57.2957)-1/[3],2)/2)";
  //TString func = "[4]*[1]*sin(x/57.2957)*exp(-pow([2]*[0],2)*pow(cos(x/57.2957)-1/[3],2)/2)";
  //TString func = "[4]*[0]*[1]*exp(-pow([2]*[0],2)*pow(cos(x/57.2957)-1/[3],2)/2)";

  // Now fix some of the variables:
  double freq = 1e9; //600e6; // Hz
  double c    = 3e8;   // m/s
  double n    = 1.3; //1.78;
  double k    = 2*TMath::Pi() * n * freq/c; // 1/m
  double Const= sqrt(2*TMath::Pi()) * 4 * TMath::Pi() * 1e-7 * 1;

  // Make a dummy histogram
  TH1F* h = makeHist("h",100,0,90,"Angle [deg]", "Field Strength",kBlack,0);
  h->Fill(1e10);
  h->SetMinimum(10);
  h->SetMaximum(3000);
  h->Draw();

  // Make two instances of the function
  TF1* f0 = new TF1("f0",func.Data(),0,90);
  setParam(f0,1.2,freq,k,n,Const,kBlack);

  TF1* f1 = new TF1("f1",func.Data(),0,90);
  setParam(f1,0.1,freq,k,n,Const,kBlue);
 
  // Draw
  f0->Draw("same");
  f1->Draw("same");
  
  // Add Legend
  TLegend* leg = makeLegend(0.15,0.3,0.7,0.9);
  leg->SetHeader("f = 600 MHz");
  leg->AddEntry(f0,"L = 1.2m","l");
  leg->AddEntry(f1,"L = 0.1m","l");
  leg->Draw("same");
  
  //can->SaveAs("../plots/quickAnalytic_600MHz.png");

}

//------------------------------------//
// Set params
//------------------------------------//
void setParam(TF1* &f, double par0,
	      double par1, double par2,
	      double par3, double par4,
	      int color)
{

  f->SetParameter(0,par0);
  f->SetParameter(1,par1);
  f->SetParameter(2,par2);
  f->SetParameter(3,par3);
  f->SetParameter(4,par4);
  f->SetLineWidth(2);
  f->SetLineColor(color);

}
