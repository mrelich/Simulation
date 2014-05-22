
#include "Analyze.h"

//-----------------------------------------------//
// Constructor
//-----------------------------------------------//
Analyze::Analyze() :
  m_dim3(NULL),
  m_mixer(NULL),
  m_detectors(NULL)
{

  

}

//-----------------------------------------------//
// Destructor
//-----------------------------------------------//
Analyze::~Analyze()
{

  delete m_dim3;
  delete m_mixer;

}

//-----------------------------------------------//
// Generate a given event
//-----------------------------------------------//
void Analyze::generateEvent()
{


}


//-----------------------------------------------//
// Generate a pulse that is a part of the beam
//-----------------------------------------------//
void Analyze::generatePulse(float dt)
{


}
