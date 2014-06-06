
#include "SaveOutput.h"

using namespace std;

//---------------------------------------------//
// Fill charge excess profiles
//---------------------------------------------//
void SaveOutput::fillQz(vector<double> Qz,
			int nbins,
			double min,
			double max,
			int evtNum,
			TFile* file)
{

  // Change roots directory to 
  // the file directory
  file->cd();

  // Create name for histogram
  stringstream ss;
  ss << "Qz_event" << evtNum << "_pulse" << m_QzCounter;
  m_QzCounter+=1;

  // Create histogram
  TH1F* h = new TH1F(ss.str().c_str(),"",nbins,min,max);
  h->GetXaxis()->SetTitle("Shower Depth [m]");
  h->GetYaxis()->SetTitle("Charge Excess");

  // Loop over Qz and fill histogram
  for(unsigned int i=0; i<Qz.size(); ++i){
    float bc = h->GetBinCenter(i+1);
    h->Fill(bc, Qz.at(i));
  }

  // Save histogram
  h->Write();
  delete h;

}

//---------------------------------------------//
// Fill Near-Field approxmation result
//---------------------------------------------//
void SaveOutput::fillA(Detectors* detectors,
		       int evtNum,
		       TFile* file)
{

  // Change roots directory
  // Not really sure if this is necessary
  file->cd(); 
  
  // Now need to loop over detectors
  stringstream outname;
  for(unsigned int id=0; id<detectors->getN(); ++id){

    // Start building name
    outname.str("");
    outname << "A_det" << id << "_evtNum" << evtNum <<"_pulse" << m_tACounter;
    
    // Get detector
    Detector* det = detectors->getDetector(id);
    
    // Loop over the data points and save
    int np = 0;
    double t[100000];
    double A[100000];
    for(unsigned int ip=0; ip<det->getN(); ++ip){
      
      det->getPoint(ip, t[ip], A[ip]);
      np++;

    }// end loop over points

    // Make graph
    TGraph* gr = new TGraph(np, t, A);
    gr->SetName(outname.str().c_str());
    gr->GetXaxis()->SetTitle("time [ns]");
    gr->GetYaxis()->SetTitle("|A|");
    gr->Write();
    
    // Clean up
    delete gr;

  }// end loop over detectors
  
  // Increment pulse counter
  m_tACounter++;
  
}


//---------------------------------------------//
// Fill E Field calculated from A
//---------------------------------------------//
void SaveOutput::fillE(Detectors* detectors,
		       int evtNum,
		       TFile* file)
{

  // Change roots directory
  // Not really sure if this is necessary
  file->cd(); 
  
  // Now need to loop over detectors
  stringstream outname;
  for(unsigned int id=0; id<detectors->getN(); ++id){

    // Start building name
    outname.str("");
    outname << "E_det" << id << "_evtNum" << evtNum <<"_pulse" << m_tECounter;
    
    // Get detector
    Detector* det = detectors->getDetector(id);
    
    // Loop over the data points and save
    int np = 0;
    double t[100000];
    double E[100000];
    for(unsigned int ip=0; ip<det->getNE(); ++ip){
      
      det->getE(ip, t[ip], E[ip]);
      np++;

    }// end loop over points

    // Make graph
    TGraph* gr = new TGraph(np, t, E);
    gr->SetName(outname.str().c_str());
    gr->GetXaxis()->SetTitle("time [ns]");
    gr->GetYaxis()->SetTitle("|E|");
    gr->Write();
    
    // Clean up
    delete gr;

  }// end loop over detectors
  
  // Increment pulse counter
  m_tECounter++;
  
}
