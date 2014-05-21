
#include "Mixer.h"

using namespace std;

//------------------------------------------------//
// Constructor
//------------------------------------------------//
Mixer::Mixer(float Eprimary, 
	     int nPartPerEvent,
	     int nToBeMixed, 
	     int totEvents, 
	     int finalEvents,
	     string inname) :
  m_output(NULL),
  m_chain(NULL),
  m_rand(NULL),
  m_tobemixed(nToBeMixed),
  m_totEvents(totEvents),
  m_finalEvents(finalEvents),
  m_scale(nPartPerEvent),
  m_nbins(1.),
  m_xmin(0.),
  m_xmax(200.),
  m_step(0.5)
{
  
  // Build output file name
  stringstream ss;
  ss << getenv("PWD");
  ss << "/../output/mixedShower_Eprim" 
     << Eprimary
     << "_ToBeMixed" << m_tobemixed
     << "_scale" << m_scale
     << "_nEvents" << finalEvents
     << ".root";
  
  // Open root file
  m_output = new TFile(ss.str().c_str(),"recreate");

  // Build file reader
  m_chain  = new TChain("trkTree");
  m_chain->Add(inname.c_str());

  // Set event address
  m_event  = new Event();
  m_chain->SetBranchAddress("event", &m_event);

  // Create the random object
  m_rand   = new TRandom3();

  // Step size is when to count the particles.
  // In this case it is the m_xmax / nbins
  m_nbins = m_xmax / m_step;

  // Print some beginning info
  cout<<endl;
  cout<<"************************************************"<<endl;
  cout<<" Eprimary         = "<<Eprimary<<endl;
  cout<<" nToBeMixed       = "<<nToBeMixed<<endl;
  cout<<" scale            = "<<m_scale<<endl;
  cout<<" totEvents        = "<<totEvents<<endl;
  cout<<" nFinalEvents     = "<<finalEvents<<endl;
  cout<<" Mimicing "<<m_scale*nToBeMixed<<" particles"; 
  cout<<" with primary energy: "<<Eprimary<<" MeV"<<endl;
  cout<<"************************************************"<<endl;
  cout<<endl;

}

//------------------------------------------------//
// Destructor
//------------------------------------------------//
Mixer::~Mixer()
{

  // Close output file
  m_output->Write();
  m_output->Close();
  delete m_output;

  // Delete objects
  delete m_chain;
  delete m_event;
  delete m_rand;

  // Loop over and kill any remaining particles
  //for(uint i=0; i<m_parts.size(); ++i)
  //  delete m_parts.at(i);
  m_parts.clear();

}

//------------------------------------------------//
// Generate events
//------------------------------------------------//
void Mixer::generateEvents()
{
  
  // Make sure root directory is in root file
  m_output->cd();

  // Name for output histogram
  stringstream pname;

  // Loop over the number of events to be generated
  for(int iEvt=0; iEvt<m_finalEvents; ++iEvt){
    if(iEvt % 10 == 0)
      cout<<"Working on "<<iEvt<<endl;

    // Specify output name
    pname.str("");
    pname << "h_evt" << iEvt;

    // Make histogram
    TH1D* h_evt = new TH1D(pname.str().c_str(),"",
			   m_nbins, m_xmin, m_xmax);
    
    // Now loop over total times to reuse
    for(int iMix=0; iMix<m_tobemixed; ++iMix){
      int rndEvent = getEventNum();
      TH1D* h_temp = generateEvent(rndEvent);
      h_evt->Add( h_temp );
      delete h_temp;
    }// end loop over mixed events

    // Write histogram
    h_evt->Write();
    delete h_evt;

  }// end loop over tot events to be generated

}

//------------------------------------------------//
// Generate a single event
//------------------------------------------------//
TH1D* Mixer::generateEvent(int evtNum)
{

  // Load the particles for a given event
  m_chain->GetEntry(evtNum);
  m_parts = m_event->getParticles();
  
  // Create temporary histogram
  TH1D* h_temp = new TH1D("h_temp","",m_nbins,m_xmin,m_xmax);
  
  // Loop over particles
  //cout<<"Number of Particles: "<<m_parts.size()<<" Event: "<<evtNum<<endl;
  for(uint i=0; i<m_parts.size(); ++i){
    Particle* p = &m_parts.at(i);

    // Only count electrons
    int pdg = p->pdg();
    if( abs(pdg) != 11 ) continue;

    // TODO: Make the bin width variable
    // this should be easy to do!!
    //cout<<"\tStart: "<<p->ZI()<<" last: "<<p->ZF()<<endl;
    int lowbin  = h_temp->GetXaxis()->FindBin(p->ZI());
    int highbin = h_temp->GetXaxis()->FindBin(p->ZF());
    
    //p->print();
    //cout<<"Particle: "<<i<<endl;
    //cout<<"lowbin: "<<lowbin<<" highbin: "<<highbin<<endl;

    // If in same bin, do nothing
    if(lowbin == highbin) continue;
    if(highbin > m_nbins) highbin = m_nbins;

    // Loop from low to high
    int sign_pdg = pdg > 0 ? 1 : -1;
    for(int bin=lowbin; bin<highbin; ++bin){
      float bc = h_temp->GetBinCenter(bin);
      h_temp->Fill(bc, sign_pdg * m_scale);
    }
  }// end loop over particles
  
  return h_temp;

}

//------------------------------------------------//
// Get a random event number
//------------------------------------------------//
int Mixer::getEventNum()
{
  
  return (int) (m_rand->Rndm() * (m_totEvents-1));
  
}
