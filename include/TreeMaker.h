#ifndef TreeMaker_h
#define TreeMaker_h

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
// Tree Maker class to take the track output from G4 and //
// put it into a convenient format to mix events. Trying //
// to see if this is tracktable (10^6 events).           //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//

#include "FileReader.h"
#include "Event.h"
#include "TTree.h"
#include "TFile.h"
#include <string>

class TreeMaker
{

 public:
  
  // Constructor
  TreeMaker(std::string outname, std::string inname);
  
  // Destructor
  virtual ~TreeMaker();

  // Loop over N Events
  void loop(int nEvent);

  // Fill the tree
  void fill(){ m_tree->Fill(); };

 private:

  TFile* m_outfile;      // The output file
  TTree* m_tree;         // The tree
  Event* m_event;        // Track event object
  FileReader* m_fRead;   // Text file Reader

};

#endif
