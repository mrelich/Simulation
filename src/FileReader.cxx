
#include "FileReader.h"

using namespace std;

//------------------------------------------//
// Constructor
//------------------------------------------//
FileReader::FileReader(string filename)
{

  // Open file
  m_input.open(filename.c_str(), ifstream::in);


}

//------------------------------------------//
// Destructor
//------------------------------------------//
FileReader::~FileReader()
{

  // Close file
  m_input.close();

}

//------------------------------------------//
// Set Particles
//------------------------------------------//
void FileReader::setParticles(vector<Particle*> &parts)
{

  // Delete old particles
  for(uint i=0; i<parts.size(); ++i)
    delete parts.at(i);
  parts.clear();

  // Set the kill switches
  string event = "Event:";
  string end   = "End:";

  // Variables to be read in
  // [0,1,2,3]  == xi, yi, zi, ti
  // [4,5]      == E, Etot
  // [6,7,8,9]  == xf, yf, zf, tf
  // [10,11,12] == trkID, momID, pdg
  const int nPars = 13;
  float vars[nPars];
  
  // Loop over and load input
  int prevPos = 0;
  while( !m_input.eof() ){

    // Specify some generic char vector
    char buf[512];

    // Get the line and save previous position
    prevPos = m_input.tellg();
    m_input.getline(buf, 512);

    // Now parse the buffer
    const char* tokens[nPars] = {};
    tokens[0] = strtok(buf, " ");

    if( event.compare(tokens[0]) == 0 ) continue;
    if( end.compare(tokens[0]) == 0)    break;

    // Now save the variables
    vars[0] = atof(tokens[0]);
    for(int i=1; i<nPars; ++i){
      vars[i] = atof(strtok(0," "));
    }

    // Skip photons
    if( ((int) vars[12]) == 22 ) continue;

    // Now construct the particle
    Particle* p = new Particle(vars[0],     // xi
			       vars[1],     // yi
			       vars[2],     // zi
			       vars[3],     // ti
			       vars[6],     // xf
			       vars[7],     // yf
			       vars[8],     // zf
			       vars[9],     // tf
			       vars[5],     // Etot
			       vars[10],     // trkID
			       vars[12]);   // pdg
    //p->print();
    parts.push_back(p);
    
  }// end while loop

}

