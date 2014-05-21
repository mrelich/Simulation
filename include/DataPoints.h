#ifndef DataPoints_h
#define DataPoints_h

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
// Class to hold the resulting time and whatever information. This  //
// can be used to hold the time vs. electric field, time vs. vector //
// potential, or someother quantity I haven't thought of yet...     //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//

#include <vector>

class DataPoints
{

 public: 

  // Constructor
  DataPoints(){};

  // Destructor
  virtual ~DataPoints(){
    times.clear();
    variables.clear();
  };

  // Method to add a new point
  void addPoint(double t, double V){
    times.push_back(t);
    variables.push_back(V);
  };

  // Retrieve all times and variables
  std::vector<double> getTimes(){ return times; };
  std::vector<double> getVar()  { return variables; };

  // Retrieve a specific point
  void getPoint(int i, double &t, double &V){

    // Check bounds
    // TODO: Add error message?
    if( i >= times.size() ){
      t = 0; 
      V = 0; 
      return;
    }
    
    // Assign variable
    t = times.at(i);
    V = variables.at(i);
    return;
  };

  // Get the number of stored points
  void getN(){ return times.size(); };

 private:
  
  std::vector<double> times;        // vector to hold times
  std::vector<double> variables;    // vector to hold variable vs. time.
  

};

#endif
