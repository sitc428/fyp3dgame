#include "CollisionHelper.hpp"
#include "Check.hpp"

// collision between any triangle selector and a bounding box
bool CollisionHelper::CheckCollision( const irr::scene::ITriangleSelector& selector, const irr::core::aabbox3d<irr::f32>& box )
{
	// check if our bounding box intersects any triangles from the selector
	irr::core::triangle3df intersectingTriangles[1];
	intersectingTriangles[0] = irr::core::triangle3d<irr::f32>();
	irr::s32 temp;
	selector.getTriangles( intersectingTriangles, 1, temp, box );

	if (intersectingTriangles[0] != irr::core::triangle3d<irr::f32>())
	{
		return true;
	} 

	return false;
}

// collision between any two bounding boxes
bool CollisionHelper::CheckCollision( const irr::core::aabbox3d<irr::f32>& box1, const irr::core::aabbox3d<irr::f32>& box2 )
{
	return box1.intersectsWithBox(box2);
}

// check if the distance between the points is within the given tolerance
bool CollisionHelper::CheckProximity( const irr::core::vector3df& pos1, const irr::core::vector3df& pos2, irr::f32 tolerance )
{
	check( tolerance >= 0.0f );
	// get the distance between the points
	irr::f32 dist = pos1.getDistanceFrom( pos2 );

	return (dist <= tolerance);
}

// check if the distance between the points is within the given tolerance
bool CollisionHelper::CheckProximity2D( const irr::core::vector3df& pos1, const irr::core::vector3df& pos2, irr::f32 tolerance )
{
	check( tolerance >= 0.0f );
	// get the distance between the points
	irr::f32 dist = pos1.getDistanceFrom( irr::core::vector3df(pos2.X, pos1.Y, pos2.Z) );

	return (dist <= tolerance);
}