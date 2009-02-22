#ifndef __COLLISION_HELPER_HPP__
#define __COLLISION_HELPER_HPP__

#include <irrlicht/irrlicht.h>

using namespace irr;
using namespace irr::core;
using namespace irr::scene;

/**
*	A utility class for aiding in various collision checks
*/
class CollisionHelper
{
public:

// collision between any triangle selector and a bounding box
static bool CheckCollision( const ITriangleSelector& selector, const aabbox3d<f32>& box );
// collision between any two bounding boxes
static bool CheckCollision( const core::aabbox3d<f32>& box1, const core::aabbox3d<f32>& box2 );
// check if the distance between the points is within the given tolerance
static bool CheckProximity( const vector3df& pos1, const vector3df& pos2, f32 tolerance );
};

#endif //__COLLISION_HELPER_HPP__