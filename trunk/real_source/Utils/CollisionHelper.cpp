#include "CollisionHelper.h"
#include "Check.h"

// collision between any triangle selector and a bounding box
bool CollisionHelper::CheckCollision( const ITriangleSelector& selector, const core::aabbox3d<f32>& box )
{
	// check if our bounding box intersects any triangles from the selector
	triangle3df intersectingTriangles[1];
    intersectingTriangles[0] = triangle3d<f32>();
    s32 temp;
    selector.getTriangles( intersectingTriangles, 1, temp, box );

    if (intersectingTriangles[0] != triangle3d<f32>())
    {
        return true;
    } 

	return false;
}

// collision between any two bounding boxes
bool CollisionHelper::CheckCollision( const core::aabbox3d<f32>& box1, const core::aabbox3d<f32>& box2 )
{
	return box1.intersectsWithBox(box2);
}

// check if the distance between the points is within the given tolerance
bool CollisionHelper::CheckProximity( const vector3df& pos1, const vector3df& pos2, f32 tolerance )
{
	check( tolerance >= 0.0f );
	// get the distance between the points
	f32 dist = pos1.getDistanceFrom( pos2 );

	return (dist <= tolerance);
}