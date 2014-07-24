
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
// Want to test the Track tool to see if the methods are //
// calculating what I had intended.                      //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//

#include "TrackTool.h"

using namespace std;

//--------------------------------------//
// Main
//--------------------------------------//
int main()
{

  // Intantiate an instance of TrackTool
  TrackTool* m_tool = new TrackTool();
  m_tool->setVerbose();

  // Initialize detectors
  Detectors* m_detectors = new Detectors();
  m_detectors->initialize();

  // Create some particles
  vector<Particle*> m_parts;
  
  // 40 MeV electron from 
  m_parts.push_back( new Particle(0,0,0,0,
				  -3.40943,3.15607,17.132,0.639248,
				  40.511,1,11) );
  
  // Now calculate vector field
  m_tool->EfieldZHSStyle(m_parts,m_detectors,0);
 
  // Clean up
  delete m_tool;
  delete m_detectors;
  
  for(uint i=0; i<m_parts.size(); ++i)
    delete m_parts.at(i);
  m_parts.clear();

  return 0;
 
}
