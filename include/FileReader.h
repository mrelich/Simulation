#ifndef FileReader_h
#define FileReader_h

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
// Need to read in the filelist containing the event information. //
// The idea is that I want to load all the particles in a given   //
// event (at least at first, might be harsh on memory) then use   //
// that vector in analysis.                                       //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//

// Mine
#include "Particle.h"

// Standard
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include <stdlib.h>

typedef unsigned int uint;

class FileReader
{

 public:

  // Constructor / Destructor
  FileReader(std::string filename);
  virtual ~FileReader();

  // Set the next events particles
  void setParticles(std::vector<Particle*> &parts);
  
 private:
  
  std::ifstream m_input;    // the input file
  
};

#endif
