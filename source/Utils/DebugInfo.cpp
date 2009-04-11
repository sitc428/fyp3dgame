#include "DebugInfo.hpp"

bool DebugInfo::enabledDebugBBox = false;
irr::scene::E_CULLING_TYPE DebugInfo::cameraCullingMode = irr::scene::EAC_OFF;

void DebugInfo::enableDebugBBox( GameWorld& world )
{
	if( enabledDebugBBox )
		return;

	enabledDebugBBox = true;
	std::transform(
		&((world.GetActors())[0]),
		&((world.GetActors())[world.GetActors().size()-1]),
		&((world.GetActors())[0]),
		DebugInfo::showDebugBox
	);
	std::transform(
		&((world.GetBlocking())[0]),
		&((world.GetBlocking())[world.GetBlocking().size()-1]),
		&((world.GetBlocking())[0]),
		DebugInfo::showDebugBox2
	);
}

void DebugInfo::disableDebugBBox( GameWorld& world )
{
	if( enabledDebugBBox )
	{
		enabledDebugBBox = false;
		std::transform(
			&((world.GetActors())[0]),
			&((world.GetActors())[world.GetActors().size()-1]),
			&((world.GetActors())[0]),
			DebugInfo::hideDebugBox
		);
		std::transform(
			&((world.GetBlocking())[0]),
			&((world.GetBlocking())[world.GetBlocking().size()-1]),
			&((world.GetBlocking())[0]),
			DebugInfo::hideDebugBox2
		);
	}
}

void DebugInfo::nextCullingMode( Camera& cam )
{
	if( cameraCullingMode == irr::scene::EAC_OFF )
		cameraCullingMode == irr::scene::EAC_BOX;
	else if( cameraCullingMode == irr::scene::EAC_BOX )
		cameraCullingMode == irr::scene::EAC_FRUSTUM_BOX;
	else if( cameraCullingMode == irr::scene::EAC_FRUSTUM_BOX )
		cameraCullingMode == irr::scene::EAC_FRUSTUM_SPHERE;
	else if( cameraCullingMode == irr::scene::EAC_FRUSTUM_SPHERE )
		cameraCullingMode == irr::scene::EAC_OFF;

	cam.GetNode().setAutomaticCulling( cameraCullingMode );
}
