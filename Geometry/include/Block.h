#ifndef Block_h
#define Block_h

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
// A class for a basic rectangular object to contain properties   //
// relevant for implementing Maxwell's equations.                 //
//                                                                //
// Author: M. Relich                                              //
// Penned: 6/5/2014                                               //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//

#include "Position.h"

class Block
{

 public:

  // Constructor for a cube
  Block(double x, double y, double z, double dx, double n){
    Block(x,y,z,dx,dx,dx,n);
  };

  // Constructor for rectangular prism
  Block(double x, double y, double z,
	double dx, double dy, double dz,
	double n){
    m_pos = Position(x,y,z);
    m_dx  = dx;
    m_dy  = dy;
    m_dz  = dz;
    m_n   = n;
  };

  // Destructor
  virtual ~Block(){};

  // Update position
  void setPosition(double x, double y, double z){
    m_pos.setPos(x,y,z);
  };

  // Update dimensions
  void setDX(double dx){ m_dx = dx; };
  void setDY(double dy){ m_dy = dy; };
  void setDZ(double dz){ m_dz = dz; };

  // Retrieve position
  Position* getPosition(){ return &m_pos; };

  // Get dimensions
  double getDX(){ return m_dx; };
  double getDY(){ return m_dy; };
  double getDZ(){ return m_dz; };
  double getV(){ return m_dx*m_dy*m_dz; };

  // Update index of refraction
  void setIR(double n){ m_n = n; };
  
  // Get index of refraction
  void getN(){ return m_n; };

  // Is position in this volume
  bool inBlock(Position* pos);
  
  // Calculate the range for a side
  bool inRange(double p,        // central position
	       double d,        // distance on either side
	       double point);   // point in question
  
 private:
  
  Position m_pos;   // Central location in (x,y,z)
  double m_dx;      // length in x direction
  double m_dy;      // length in y direction
  double m_dz;      // length in z direction
  
  double m_n;       // index of refraction
  
};

#endif
