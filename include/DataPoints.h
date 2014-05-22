#ifndef DataPoints_h
#define DataPoints_h

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
// Class to hold the resulting time and whatever information. This  //
// can be used to hold the time vs. electric field, time vs. vector //
// potential, or someother quantity I haven't thought of yet...     //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//

#include <vector>
#include <iostream>

class DataPoints
{

 public: 

  // Constructor
  DataPoints();

  // Destructor
  virtual ~DataPoints();

  // Method to add a new point
  void addPoint(double t, double V);

  // Retrieve all m_times and variables
  std::vector<double> getTimes(){ return m_times; };
  std::vector<double> getVar()  { return m_variables; };

  // Retrieve a specific point
  void getPoint(unsigned int i, double &t, double &V);

  // Get the number of stored points
  unsigned int getN(){ return m_times.size(); };
  
 private:
  
  std::vector<double> m_times;        // vector to hold times
  std::vector<double> m_variables;    // vector to hold variable vs. time.
  

};

#endif
