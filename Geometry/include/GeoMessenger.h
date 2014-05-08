#ifndef GeoMessenger_h
#define GeoMessenger_h

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
// This class will hold the objects that are required for the  //
// analysis. It will be very primative at first, and may never //
// develop beyond there. However, I think it is better to have //
// it for now to allow for expansion to multi-objects.         //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//

// Local Goodies
#include "Block.h"
#include "Position.h"

// Standard
#include <string>
#include <vector>
#include <algorithm>

class GeoMessenger
{

 public:

  // Constructor
  GeoMessenger(double l, double w, double h);

  // Destructor
  virtual ~GeoMessenger();
  
  // Add an object into the world
  void addObject(Block* b){ m_objects.push_back(b); };

  // Initialize and make sure objects are ok
  void initialize();

  // Retrieve properties of volume
  // so far this only includes index 
  // of refraction but more will come
  double getN(Position* pos);

 private:

  //
  // Methods
  //

  // Check if any objects overlap
  bool objectsOverlap();

  // Sort objects such that smallest on inside
  void sortObjects();

  // Check if position iis in volume
  bool isInVolume(Position* pos, Block* b);

  //
  // Variables
  //

  std::vector<Block*> m_objects;   // mediums to include

  double m_l;                      // length of world volume
  double m_h;                      // height of world volume
  double m_w;                      // width of world volume
  

};

#endif
