
#include "TrackTool.h"

using namespace std;

//--------------------------------------------//
// Constructor
//--------------------------------------------//
TrackTool::TrackTool()
{


}


//--------------------------------------------//
// Destructor
//--------------------------------------------//
TrackTool::~TrackTool()
{


}

//--------------------------------------------//
// Main method for calculation
//--------------------------------------------//
void TrackTool::EfieldZHSStyle(vector<Particle*> parts,
			       Detectors* detectors,
			       double t0)
{

  // Load the vector of detectors
  vector<Detector*> dets = detectors->getDetectors();
  
  // Here loop over each particle
  // and the detectors 
  for(uint ip=0; ip<parts.size(); ++ip){
    Particle* part = parts.at(ip);
    
    // Get beta
    TVector3 beta = getBeta(part);

    for(uint id=0; id<dets.size(); ++id){
      Detector* det = dets.at(id);
      TVector3* pol = det->getPol();
      TVector3 pos  = TVector3(det->getX(),
			       det->getY(),
			       det->getZ());

      // Get u and R
      TVector3 u = getUnitVector(part, &pos);
      double R   = getR(part,&pos);
      
      // We will add two points to detectors data
      // points for the start of the track and
      // the end of the track

      // Times
      double tDi = getTDetector(&beta,&u,R,part->TI(),t0);
      double tDf = getTDetector(&beta,&u,R,part->TF(),t0);
      
      // Efield
      double E = Efield(&beta,&u,pol,R);
      
      // Save
      det->addTE(tDi, E);
      det->addTE(tDf, -E);
      
      // Clean up
      delete pol;
      delete det;

    }// end loop over detectors

  }// end loop over particles

}

//--------------------------------------------//
// Efield for particular time
//--------------------------------------------//
double TrackTool::Efield(TVector3* beta,
			 TVector3* u,
			 TVector3* detPol,
			 double R)
{

  // Calculate the constant terms
  double C = Phys::mu0 * Phys::mur * Phys::e0;
  C /= (4 * Phys::pi * R * Phys::c);
  
  // Take magnitude of beta with det polarizatin
  double pol = (*detPol) * (u->Cross(u->Cross(*beta)));
  
  // Denominator
  double den = 1 - Phys::nICE * beta->Dot(*u);
  
  // Return result
  return C * pol / den;

}			 

//--------------------------------------------//
// Get detector time
//--------------------------------------------//
double TrackTool::getTDetector(TVector3* beta,
			       TVector3* u,
			       double R,
			       double t,
			       double t0)
{

  double n = Phys::nICE;
  double c = Phys::c;
  return t + n*R/c - n * beta->Dot(*u) * (t - t0);

}

//--------------------------------------------//
// Get Beta for this particle
//--------------------------------------------//
TVector3 TrackTool::getBeta(Particle* part)
{

  double c   = Phys::c;
  double dt  = part->TF() - part->TI();

  double v_x = (part->XF() - part->XI())/dt;
  double v_y = (part->YF() - part->YI())/dt;
  double v_z = (part->ZF() - part->ZI())/dt;



  return TVector3(v_x/c,v_y/c,v_z/c);

}

//--------------------------------------------//
// Get Unit vector that points to detector
// from middlepoint of the track
//--------------------------------------------//
TVector3 TrackTool::getUnitVector(Particle* part,
				   TVector3* detPos)
{
  
  // Get the midpoint for the track
  TVector3 midpoint = TVector3((part->XF() + part->XI())/2.,
                               (part->YF() + part->YI())/2.,
                               (part->XF() + part->ZI())/2.);
  
  // Now return a unit vector
  return (*detPos - midpoint).Unit();
  
}

//--------------------------------------------//
// Get distance to detector from midpoint
//--------------------------------------------//
double TrackTool::getR(Particle* part,
		       TVector3* detPos)
{
  
  // Get the midpoint of the track
  TVector3 midpoint = TVector3((part->XF() + part->XI())/2.,
                               (part->YF() + part->YI())/2.,
                               (part->XF() + part->ZI())/2.);
  
  // Now take the difference and return
  // the magnitude
  return (midpoint - *detPos).Mag();

}
