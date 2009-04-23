#ifndef __DEBUG_INFO_HPP__
#define __DEBUG_INFO_HPP__

#include <irrlicht/irrlicht.h>
#include "Actor.hpp"
#include "Camera.hpp"
#include "GameWorld.hpp"
#include "MainCharacter.hpp"

/*
 * A utility class for controlling debuggin information
 */
class DebugInfo
{
public:
	static void enableDebugBBox( GameWorld& );
	static void disableDebugBBox( GameWorld& );
	static void nextCullingMode( Camera& );
	static void mainCharacterFrameNum( MainCharacter& );
	static void enableDebugCamera( GameWorld&, Camera* );
	static void disableDebugCamera( GameWorld& );
	static void killMainCharacter( MainCharacter& );
	static void teleportPlayer( MainCharacter& );

private:
	static bool enabledDebugBBox;
	static irr::scene::E_CULLING_TYPE cameraCullingMode;
	static irr::scene::ICameraSceneNode* debugCamera;
	static irr::scene::ICameraSceneNode* normalCamera;

	static Actor* showDebugBox( Actor* actor )
	{
		actor->GetNode().setDebugDataVisible( irr::scene::EDS_BBOX );
		return actor;
	}

	static Actor* hideDebugBox( Actor* actor )
	{
		actor->GetNode().setDebugDataVisible( irr::scene::EDS_OFF );
		return actor;
	}

	static irr::scene::IMeshSceneNode* showDebugBox2( irr::scene::IMeshSceneNode* node )
	{
		node->setDebugDataVisible( irr::scene::EDS_BBOX );
		return node;
	}

	static irr::scene::IMeshSceneNode* hideDebugBox2( irr::scene::IMeshSceneNode* node )
	{
		node->setDebugDataVisible( irr::scene::EDS_OFF );
		return node;
	}
};

#endif //__DEBUG_INFO_HPP__
