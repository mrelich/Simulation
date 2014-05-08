
#include "Block.h"

//--------------------------------------//
// Check if position is in box
//--------------------------------------//
bool Block::inBlock(Position* pos)
{

  // Just check if it is not in range for each
  // axis. If it isn't, then we know it's not
  // inside this block. Otherwise, it must be.
  if( !inRange(m_pos.getX(),m_dx,pos.getX()) )
    return false;
  if( !inRange(m_pos.getY(),m_dy,pos.getY()) )
    return false;
  if( !inRange(m_pos.getZ(),m_dz,pos.getZ()) )
    return false;

  return true;

}

//--------------------------------------//
// Check if given point is in range
//--------------------------------------//
bool Block::inRange(double p, double d,
		    double point)
{

  // The idea is p is representative of the
  // central point on an axis. d is the 
  // distance of that side on that axis.
  // point is the point in question on this
  // axis.  Not really good explanation,
  // but you can draw it on paper...
  if( p - d/2. < point && point < p + d/2. )
    return true;
}
