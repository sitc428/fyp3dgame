#include "Robot.hpp"
#include "Check.h"
#include "GameEngine.h"
#include "GameWorld.h"
#include "MainCharacter.hpp"
#include <ctime>
#include <iostream>

extern GameEngine* GEngine;

static const irr::core::vector3df	defaultPosition = irr::core::vector3df(10,50,10);
static const irr::core::vector3df	defaultRotation = irr::core::vector3df(0, 90, 0);
static const irr::core::vector3df	defaultScale = irr::core::vector3df(0.1, 0.1, 0.1);

static const irr::c8*		ROBOT_MODEL  = "media/model/robot2.x";
//static const irr::c8*		defaultTexture = "media/model/MainTexutre1.png";
static const irr::f32		ANIMATION_SPEED = 24;
static const irr::f32		ANIMATION_TRANSITION_BLEND_TIME = 0.2f;

// robot's animation information
/*static const irr::u32		ROBOT_ANIMATION_IDLE_START = 1;
static const irr::u32		ROBOT_ANIMATION_IDLE_END = 1;
static const irr::u32		ROBOT_ANIMATION_WALK_FORWARD_START = 4;
static const irr::u32		ROBOT_ANIMATION_WALK_FORWARD_END = 30;
static const irr::u32		ROBOT_ANIMATION_WALK_BACK_START = 38;
static const irr::u32		ROBOT_ANIMATION_WALK_BACK_END = 63;
static const irr::u32		ROBOT_ANIMATION_WALK_RUN_START = 72;
static const irr::u32		ROBOT_ANIMATION_WALK_RUN_END = 95;
static const irr::u32		ROBOT_ANIMATION_WALK_JUMP_START = -1;
static const irr::u32		ROBOT_ANIMATION_WALK_JUMP_END = -1;
static const irr::u32		ROBOT_ANIMATION_WALK_ATTACK_START = -1;
static const irr::u32		ROBOT_ANIMATION_WALK_ATTACK_END = -1;
static const irr::u32		ROBOT_ANIMATION_WALK_DEAD_START = -1;
static const irr::u32		ROBOT_ANIMATION_WALK_DEAD_END = -1;
*/

Robot::Robot( GameWorld& gameWorld, irr::video::IVideoDriver& driver )
	:Actor(gameWorld),
	node(NULL),
	collisionAnimator(NULL),
	world(gameWorld)
{
	irr::scene::ISceneManager& smgr = world.GetSceneManager();
	// load the animated mesh, and add a new scene graph node for it
	irr::scene::ISkinnedMesh* robotMesh = (irr::scene::ISkinnedMesh*)(smgr.getMesh( ROBOT_MODEL ));
	node = smgr.addAnimatedMeshSceneNode( robotMesh, smgr.getRootSceneNode() );
	node->setPosition( defaultPosition );
	node->setID( 999 );
	node->setRotation( defaultRotation );
	node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
	node->setScale(defaultScale);
	srand( time(0) );
}

Robot::~Robot()
{
	if(collisionAnimator)
	{
		collisionAnimator->drop();
		collisionAnimator = NULL;
	}
	
	irr::scene::ISceneManager& smgr = world.GetSceneManager();
	smgr.addToDeletionQueue( node );
}

static irr::f32 floating( irr::f32 delta, irr::s32 range )
{
	std::cout << "delta:          " << delta << std::endl;
	return range * sin(delta * 10);
}

void Robot::Tick( irr::f32 delta )
{
	irr::core::vector3df offset = irr::core::vector3df( 10, floating( delta, 20), 10);
	node->setPosition(world.GetCurrentPlayer().GetNodePosition() + offset);
}