
#include "DataPoints.h"

//-------------------------------------------//
// Constructor
//-------------------------------------------//
DataPoints::DataPoints()
{

  m_times.clear();
  m_variables.clear();

}

//-------------------------------------------//
// Destructor
//-------------------------------------------//
DataPoints::~DataPoints()
{

  m_times.clear();
  m_variables.clear();

}

//-------------------------------------------//
// Add a data point
//-------------------------------------------//
void DataPoints::addPoint(double t, double V)
{

  m_times.push_back(t);
  m_variables.push_back(V);

}

//-------------------------------------------//
// Accessors
//-------------------------------------------//
void DataPoints::getPoint(unsigned int i,
			  double &t,
			  double &V)
{

  // Todo: Add error message?
  if( i >= m_times.size() ){
    t = 0;
    V = 0;
    return;    
  }

  // Assign the variable
  t = m_times.at(i);
  V = m_variables.at(i);
  return;

}
