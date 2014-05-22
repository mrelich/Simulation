
#include "Mixer.h"

using namespace std;

//------------------------------------------------//
// Constructor
//------------------------------------------------//
Mixer::Mixer(float Eprimary, 
	     int nPartPerEvent,
	     int nToBeMixed, 
	     int totEvents,
	     string inname) :
  m_chain(NULL),
  m_rand(NULL),
  m_tobemixed(nToBeMixed),
  m_totEvents(totEvents),
  m_scale(nPartPerEvent)
{
  
  // Build output file name
  stringstream ss;
  ss << getenv("PWD");
  ss << "/../output/mixedShower_Eprim" 
     << Eprimary
     << "_ToBeMixed" << m_tobemixed
     << "_scale" << m_scale
     << ".root";
  
  // Build file reader
  m_chain  = new TChain("trkTree");
  m_chain->Add(inname.c_str());

  // Set event address
  m_event  = new Event();
  m_chain->SetBranchAddress("event", &m_event);

  // Create the random object
  m_rand   = new TRandom3();

  // Print some beginning info
  cout<<endl;
  cout<<"************************************************"<<endl;
  cout<<" Mixer initialized with following properties: "<<endl;
  cout<<" Eprimary         = "<<Eprimary<<endl;
  cout<<" nToBeMixed       = "<<nToBeMixed<<endl;
  cout<<" scale            = "<<m_scale<<endl;
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
vector<double> Mixer::generateQz(int nsteps, float zmin,
				 float zmax)
{

  // Charge excess
  vector<double> Qz (nsteps,0);
  
  // Now loop over total times to reuse
  for(int iMix=0; iMix<m_tobemixed; ++iMix){
    int rndEvent = getEventNum();
    addSingleQz(rndEvent, nsteps, zmin, zmax, Qz);
  }// end loop over mixed events
  
  return Qz;

}

//------------------------------------------------//
// Generate a single event
//------------------------------------------------//
void Mixer::addSingleQz(int evtNum, int nsteps,
			float zmin, float zmax,
			vector<double> &Qz)
{
  
  // Load the particles for a given event
  m_chain->GetEntry(evtNum);
  m_parts = m_event->getParticles();

  // Calculate the bin width considered
  double bw = (zmax-zmin)/nsteps;
  
  // Loop over particles
  for(uint i=0; i<m_parts.size(); ++i){
    Particle* p = &m_parts.at(i);

    // Only count electrons
    int pdg = p->pdg();
    if( abs(pdg) != 11 ) continue;

    // Find bin that this particle falls in
    int low  = (int) (p->ZI() / bw);
    int high = (int) (p->ZF() / bw);

    // If in same bin, do nothing
    if(low == high) continue;
    if(high > nsteps) high = nsteps;

    // Loop from low to high and record
    // the charge excess in each bin
    int sign_pdg = pdg > 0 ? 1 : -1;
    for(int bin=low; bin<high; ++bin)
      Qz.at(bin) += sign_pdg * m_scale;
    
  }// end loop over particles
  
}

//------------------------------------------------//
// Get a random event number
//------------------------------------------------//
int Mixer::getEventNum()
{
  
  return (int) (m_rand->Rndm() * (m_totEvents-1));
  
}
