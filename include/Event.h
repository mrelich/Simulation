#ifndef Event_h
#define Event_h

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
// In order to mix the events quickly, it will help to have  //
// the information stored within a tree.  So I will have to  //
// add another loop.  This may end up creating something too //
// big, so do this quickly and see the size                  //
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//

#include "TObject.h"
#include "Particle.h"
#include <vector>

class Event : public TObject
{

 public:

  // Constructor Destructor
  Event(){};
  virtual ~Event(){clear();};
  
  // Add Particle
  void addParticle(Particle p){ m_particles.push_back(p); };
  
  // Add Particles
  void addParticles(std::vector<Particle*> parts){
    for(unsigned int i=0; i<parts.size(); ++i)
      m_particles.push_back( *parts.at(i) );
  }
  
  // Get Particle
  std::vector<Particle> getParticles(){return m_particles;};
  
  // Get a particle
  Particle* getParticle(unsigned int i){
    return &m_particles.at(i);
  };

  // Clear
  void clear(){ m_particles.clear(); };

  ClassDef(Event,1);

 private:
  
  std::vector<Particle> m_particles;   // vector to hold the particles

};

#endif
