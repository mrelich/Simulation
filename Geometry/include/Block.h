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
  Block(double x, double y, double z, double l, double n){
    Block(x,y,z,l,l,l,n);
  };

  // Constructor for rectangular prism
  Block(double x, double y, double z,
	double l, double w, double h,
	double n){
    m_pos = Position(x,y,z);
    m_l   = l;
    m_w   = w;
    m_h   = h;
    m_n   = n;
  };

  // Destructor
  virtual ~Block(){};

  // Update position
  void setPosition(double x, double y, double z){
    m_pos.setPos(x,y,z);
  };

  // Update dimensions
  void setLength(double l){ m_l = l; };
  void setHeight(double h){ m_h = h; };
  void setWidth(double w) { m_w = w; };

  // Retrieve position
  Position* getPosition(){ return &m_pos; };

  // Get dimensions
  double getL(){ return m_l; };
  double getW(){ return m_w; };
  double getH(){ return m_h; };

  // Update index of refraction
  void setIR(double n){ m_n = n; };
  
  // Get index of refraction
  void getN(){ return m_n; };
  
 private:
  
  Position m_pos;   // Central location in (x,y,z)
  double m_l;       // length
  double m_w;       // width
  double m_h;       // height
  
  double m_n;       // index of refraction
  
};

#endif
