
#include "TreeMaker.h"

using namespace std;

//---------------------------------------------------//
// Constructor
//---------------------------------------------------//
TreeMaker::TreeMaker(string outname, string inname) :
  m_outfile(NULL),
  m_tree(NULL),
  m_fRead(NULL)
{
  
  // Open up a file reader object
  m_fRead = new FileReader(inname);

  // Create a track tree
  m_event = new Event();

  // Open output root file
  m_outfile = new TFile(outname.c_str(),"recreate");

  // Create TTree object and assign this
  // trkTree to that tree
  m_tree = new TTree("trkTree","trkTree");
  m_tree->SetAutoSave(1000000);
  m_tree->SetMaxTreeSize(3000000000u);
  m_tree->Branch("event", &m_event,32000,1);
  
}

//---------------------------------------------------//
// Destructor
//---------------------------------------------------//
TreeMaker::~TreeMaker()
{

  m_outfile->Write("",TObject::kOverwrite);
  m_outfile->Close();
  delete m_outfile;
  delete m_event;
  delete m_fRead;

}

//---------------------------------------------------//
// Loop over events
//---------------------------------------------------//
void TreeMaker::loop(int nEvent)
{
  
  vector<Particle*> particles;

  // nEvent = the number of events to process. It is
  // the users job to make sure there are enough
  // events in the input file!
  for(int evt=0; evt<nEvent; ++evt){

    // Some print out so user doesn't get bored
    if(evt % 100000 == 0) 
      cout<<"Processing Event "<<evt<<endl;


    m_event->clear();                 // Make sure event empty
    m_fRead->setParticles(particles); // load particles
    m_event->addParticles(particles); // put them in the tree
    fill();                           // fill this event
  }

  // Clean up left over particles from last event
  for(unsigned int i=0; i<particles.size(); ++i)
    delete particles.at(i);
  particles.clear();

}

