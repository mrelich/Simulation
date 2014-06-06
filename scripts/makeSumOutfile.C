
#include "BuildSum.C"

//---------------------------//
// Main
//---------------------------//
void makeSumOutfile(TString in, TString out)
{

  // Open up intput file
  TFile* infile = new TFile(in.Data());
  
  // Get the sum
  TH1F* sum = getSum(infile, "E", 0, 0, 57);
  sum->SetName("Efield_ns");

  // Get also in seconds
  TH1F* sec = getInSeconds(sum);
  
  // Open output file
  TFile* outfile = new TFile(out.Data(),"recreate");
  sum->Write();
  sec->Write();
  outfile->Write();
  outfile->Close();


}

//---------------------------//
// Put into seconds
//---------------------------//
TH1F* getInSeconds(TH1F* h_in)
{

  // Placeholders
  int nbins = h_in->GetNbinsX();
  float xmin = h_in->GetBinLowEdge(1) * 1e-9;
  float xmax = (h_in->GetBinLowEdge(nbins) + h_in->GetBinWidth(nbins)) * 1e-9;
  TH1F* h = new TH1F("Efield_s","",nbins,xmin,xmax);
  
  for(int bin=1; bin<=nbins; ++bin){
    float bc = h_in->GetBinContent(bin);
    h->SetBinContent(bin,bc);
  }

  return h;

}
    
