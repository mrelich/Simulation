
#include "GeoMessenger.h"

// For convenience
using namespace std;
typedef unsigned int uint;

// For sorting volumes
bool sortVolume (Block* b1, Block* b2){ 
  return b1.getV() < b2.getV(); 
}  

//------------------------------------//
// Constructor
//------------------------------------//
GeoMessenger::GeoMessenger(double l, double w, 
			   double h) :
  m_l(l), m_w(w), m_h(h)
{
  
}

//------------------------------------//
// Destructor
//------------------------------------//
GeoMessenger::~GeoMessenger()
{
  
  // Clean pointers. They will be cleaned
  // up in another area
  m_objects.clear();

}

//------------------------------------//
// Initialize Geometry
//------------------------------------//
void GeoMessenger::initialize()
{

  // First sort objects
  sortObjects();

  // Next check if objects overlap
  if( objectsOverlap() ){
    cout<<"Objects overlap in the volume."<<endl;
    cout<<" -------- ADD SEGFAULT ------ "<<endl;
  }

}

//------------------------------------//
// Sort objects
//------------------------------------//
void GeoMessenger::sortObjects()
{

  if(m_objects.size() > 1)
    sort(m_objects.begin(),m_objects.end(),sortVolume);
  
}

//------------------------------------//
// Check if volumes overlap
//------------------------------------//
bool GeoMessenger::objectsOverlap()
{

  // If we have less than 2 objects
  // it is impossible to have anything
  // overlap
  if(m_objects.size() < 2) return false;

  // Think about how to write this efficiently
  // For now just assume that the user is setting
  // concentric blocks and simply check that each
  // one is centered inside the other
  for(uint i=0; i<m_objects.size()-1; ++i){
    Block* b0 = m_objects(i);
    Block* b1 = m_objects(i+1);
    
    if( b0->getDX() > b1->getDX() ) return true;
    if( b0->getDY() > b1->getDY() ) return true;
    if( b0->getDZ() > b1->getDZ() ) return true;
    
  }// end loop over objects

  return false;

}

//------------------------------------//
// Check if a position is in volume
//------------------------------------//
bool GeoMessenger::isInVolume(Position* pos, 
			      Block* b)
{

  // Return the most inner volume that the point
  // belongs too. You will notice that it returns
  // the first volume it finds. This is still in
  // the spirit of concentric volumes.
  for(uint i=0; i<m_objects.size(); ++i)
    if( m_objects.at(i)->inBlock(pos) ) return true;
  
  return false;
}

//------------------------------------//
// Get N for where particle is
//------------------------------------//
double GeoMessenger::getN(Position* pos)
{

  // Loop over objects and find which one
  // our point is in. Then return N that
  // is associated with that object
  for(uint i=0; i<m_objects.size(); ++i)
    if( isInVolume(pos,m_objects.at(i)) )
      m_objects.at(i)->getN();
  
  // Shouldn't reach here.
  cout<<"No n associated with this position"<<endl;
  cout<<"Returning -1 for index of refraction"<<endl;

  return -1;

}
