#ifndef Detector_h
#define Detector_h

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
// A class to hold the position of the detector and the resulting //
// physics information that is necessary for the analysis.        //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//

// My goodies
#include "DataPoints.h"

// Standard
#include <cmath>
#include <iostream>

class Detector
{
  
 public:

  // Constructor
  Detector(double x, double y, double z, double Athresh){
    m_x   = x;
    m_y   = y;
    m_z   = z;
    m_r   = sqrt(x*x+y*y);
    m_phi = atan(y/x);

    m_AThresh = Athresh;
    
    m_tvsA = new DataPoints();
    m_tvsE = new DataPoints();
  }; 
  
  // Destructor
  virtual ~Detector(){
    delete m_tvsA;
    delete m_tvsE;
  };

  // Reset the detector quantites
  void reset(){
    m_x = m_y = m_z = 0;
    m_r = m_phi = 0;
    m_AThresh = 0;
  };

  // Reset the data
  void clearData(){
    m_tvsA->clear();
    m_tvsE->clear();
  };

  //
  // Geometry info
  //

  // Accessors to set the quantities
  void setX(double x)     { m_x = x;     };
  void setY(double y)     { m_y = y;     };
  void setZ(double z)     { m_z = z;     };
  void setR(double r)     { m_r = r;     };
  void setPHI(double phi) { m_phi = phi; };

  // Accessors to retrieve information
  double getX()  { return m_x; };
  double getY()  { return m_y; };
  double getZ()  { return m_z; };
  double getR()  { return m_r; };
  double getPHI(){ return m_phi; };

  //
  // Physics info
  //

  // Time and vector potential
  void addTA(double t, double A){
    m_tvsA->addPoint(t,A);
  };

  // Time and electric field
  void addTE(double t, double E){
    m_tvsE->addPoint(t,E);
  };
  
  // Access a specific data point for electric field
  void getPoint(unsigned int i, double &t, double &A){
    m_tvsA->getPoint(i, t, A);
  };

  // Access a specific data point for electric field
  void getE(unsigned int i, double &t, double &E){
    m_tvsE->getPoint(i, t, E);
  };
  
  // Get the number of data points 
  // for the vector potential
  unsigned int getN(){ return m_tvsA->getN(); };

  // Get the number of data points
  // for the electrci field
  unsigned int getNE(){ return m_tvsE->getN(); };

  // Method to check vector potential thresholds
  void setAThresh(double AThresh){ m_AThresh = AThresh;  };
  double getAThresh()            { return m_AThresh;     };
  bool passAThresh(double A)     { return A > m_AThresh; };

 private:

  // Location information
  double m_x;        // x position relative to beam
  double m_y;        // y position relative to beam
  double m_z;        // z position relative to beam
  double m_r;        // r position in cylindrical coords
  double m_phi;      // phi coordinate in cylindrical coords

  // Physics information
  DataPoints* m_tvsA;  // Store time and vector potential info
  DataPoints* m_tvsE;  // Store the electric field vs. time

  // Threshold
  double m_AThresh;    // Threshold to start recording. 

};


#endif
