#ifndef Position_h
#define Position_h

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
// Class to hold the x, y, and z coordinates for objects.  //
//                                                         //
// Author: M. Relich                                       //
// Penned: 6/5/2014                                        //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//

class Position
{

 public:
  
  // Constructor
  Position(double x, double y, double z){
    m_x = x;
    m_y = y;
    m_z = z;
  };
  
  // Destructor
  virtual ~Position(){};
  
  // Update position
  void setX(double x){ m_x = x; };
  void setY(double y){ m_y = y; };
  void setZ(double z){ m_z = z; };
  
  // Set entire position
  void setPos(double x, double y, double z){
    m_x = x;
    m_y = y;
    m_z = z;
  };

  // Get position
  double getX(){ return m_x; }; 
  double getY(){ return m_y; };
  double getZ(){ return m_z; };
  

 private:
   
  double m_x;  // x position
  double m_y;  // y position
  double m_z;  // z position

};

#endif
