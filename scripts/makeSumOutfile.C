
#include "BuildSum.C"
#include <sstream>

//---------------------------//
// Main
//---------------------------//
void makeSumOutfile(TString in, TString out)
{

  // Open up intput file
  TFile* infile = new TFile(in.Data());
  
  // Specify the number of pulses you want to use
  const int npulses = 10;
  int numPulses[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  TH1F* sum_s[npulses];

  stringstream ss;
  for(int i=0; i<npulses; ++i){
    ss.str(""); 
    ss << "Efield_" << numPulses[i];
    cout<<"Getting new sum: "<< ss.str() << endl;
    TH1F* temp = getSum(infile, "E", 0, 0, numPulses[i]);
    sum_s[i] = getInSeconds(temp, TString(ss.str().c_str()));
    delete temp;
  }

  // Open output file
  TFile* outfile = new TFile(out.Data(),"recreate");
  for(int i=0; i<npulses; ++i)
    sum_s[i]->Write();
  outfile->Write();
  outfile->Close();
  

}

//---------------------------//
// Put into seconds
//---------------------------//
TH1F* getInSeconds(TH1F* h_in,TString name)
{

  // Placeholders
  int nbins = h_in->GetNbinsX();
  float xmin = h_in->GetBinLowEdge(1) * 1e-9;
  float xmax = (h_in->GetBinLowEdge(nbins) + h_in->GetBinWidth(nbins)) * 1e-9;
  TH1F* h = new TH1F(name.Data(),"",nbins,xmin,xmax);
  
  for(int bin=1; bin<=nbins; ++bin){
    float bc = h_in->GetBinContent(bin);
    h->SetBinContent(bin,bc);
  }

  return h;

}
    
