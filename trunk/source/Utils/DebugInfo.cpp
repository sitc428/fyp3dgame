#include "DebugInfo.hpp"

#include <algorithm>
#include <iostream>

bool DebugInfo::enabledDebugBBox = false;
irr::scene::E_CULLING_TYPE DebugInfo::cameraCullingMode = irr::scene::EAC_OFF;
irr::scene::ICameraSceneNode* DebugInfo::debugCamera = NULL;
irr::scene::ICameraSceneNode* DebugInfo::normalCamera = NULL;

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

void DebugInfo::mainCharacterFrameNum(MainCharacter & mainCharacter)
{
}

void DebugInfo::enableDebugCamera( GameWorld& world, Camera* norCam)
{
	normalCamera = (irr::scene::ICameraSceneNode*)(&(norCam->GetNode()));
	if( debugCamera == NULL)
	{
		debugCamera = world.GetSceneManager().addCameraSceneNodeFPS(0, 100, 1000, -1);
		debugCamera->setPosition(irr::core::vector3df(0, 500, 0));
		debugCamera->setTarget( world.GetCurrentPlayer().GetNodePosition() );
	}
	world.GetSceneManager().setActiveCamera( debugCamera );
	debugCamera->setPosition( world.GetCurrentPlayer().GetNodePosition() + irr::core::vector3df(0, 500, 0) );
	debugCamera->setTarget( world.GetCurrentPlayer().GetNodePosition() );
}

void DebugInfo::disableDebugCamera( GameWorld & world )
{
	world.GetSceneManager().setActiveCamera( normalCamera );
	if( debugCamera == NULL)
	{
		debugCamera = world.GetSceneManager().addCameraSceneNodeFPS(0, 100, 1000, -1);
		debugCamera->setPosition(irr::core::vector3df(0, 500, 0));
		debugCamera->setTarget( world.GetCurrentPlayer().GetNodePosition() );
	}
}

void DebugInfo::killMainCharacter( MainCharacter& mainCharacter )
{
	mainCharacter.ReceiveDamage( mainCharacter.GetHealth() + 1 );
}

void DebugInfo::teleportPlayer( MainCharacter& mainCharacter )
{
	int x, y, z;
	std::cin >> x >> y >> z;
	mainCharacter.SetNodePosition(irr::core::vector3df( x, y, z ));
}

void DebugInfo::addExp( MainCharacter& mainCharacter )
{
	mainCharacter.SetEXP( (mainCharacter.GetEXP() + 1 ) * 2 );
}
