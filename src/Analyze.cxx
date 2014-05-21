
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
