#ifndef __COLLISION_HELPER_HPP__
#define __COLLISION_HELPER_HPP__

#include <irrlicht/irrlicht.h>

/*
 * A utility class for aiding in various collision checks
 */
class CollisionHelper
{
	public:

		// collision between any triangle selector and a bounding box
		static bool CheckCollision( const irr::scene::ITriangleSelector& selector, const irr::core::aabbox3d<irr::f32>& box );

		// collision between any two bounding boxes
		static bool CheckCollision( const irr::core::aabbox3d<irr::f32>& box1, const irr::core::aabbox3d<irr::f32>& box2 );

		// check if the distance between the points is within the given tolerance
		static bool CheckProximity( const irr::core::vector3df& pos1, const irr::core::vector3df& pos2, irr::f32 tolerance );
};

#endif //__COLLISION_HELPER_HPP__
