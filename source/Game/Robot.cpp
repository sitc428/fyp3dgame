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
	static irr::f32 total_delta = 0;
	total_delta += delta;
	//std::cout << "delta:                " << delta << std::endl;
	//std::cout << "total_delta:                " << total_delta << std::endl;
	return range * sin(total_delta*2);
}

void Robot::Tick( irr::f32 delta )
{
	//std::cout << "Xdeg: " << world.GetCurrentPlayer().GetNodeRotation().X << "   X: " << world.GetCurrentPlayer().GetNodePosition().X << std::endl;
	//std::cout << "Ydeg: " << world.GetCurrentPlayer().GetNodeRotation().Y << "   Y: " << world.GetCurrentPlayer().GetNodePosition().Y << std::endl;
	//std::cout << "Zdeg: " << world.GetCurrentPlayer().GetNodeRotation().Z << "   Z: " << world.GetCurrentPlayer().GetNodePosition().Z << std::endl;
	std::cout << "AimVecrot.X : " << world.GetCurrentPlayer().GetAimVector().X << std::endl;
	std::cout << "AimVecrot.Y : " << world.GetCurrentPlayer().GetAimVector().Y << std::endl;
	std::cout << "AimVecrot.Z : " << world.GetCurrentPlayer().GetAimVector().Z << std::endl;

	irr::core::vector3df offset = irr::core::vector3df( 0, floating( delta, 5), 0);
	//node->setPosition(world.GetCurrentPlayer().GetNodePosition() - world.GetCurrentPlayer().GetAimVector()*-offset);//-20);// * -5.0f);
	//node->setPosition(world.GetCurrentPlayer().GetNodePosition() + offset);
	irr::core::vector3df tmp = world.GetCurrentPlayer().GetNodePosition() - world.GetCurrentPlayer().GetAimVector()*-15;
	//irr::core::vector3df tmp = world.GetCurrentPlayer().GetNodePosition();
	irr::core::vector3df aimVec = world.GetCurrentPlayer().GetAimVector();
	aimVec.rotateXZBy(world.GetCurrentPlayer().GetNodeRotation().Y, world.GetCurrentPlayer().GetNodePosition());
	//std::cout << "Player.Postition.X  : " << world.GetCurrentPlayer().GetNodePosition().X << std::endl;
	//std::cout << "Player.Postition.Y  : " << world.GetCurrentPlayer().GetNodePosition().Y << std::endl;
	//std::cout << "Player.Postition.Z  : " << world.GetCurrentPlayer().GetNodePosition().Z << std::endl;
	std::cout << "Rotated AimVector.X : " << aimVec.X << std::endl;
	std::cout << "Rotated AimVector.Y : " << aimVec.Y << std::endl;
	std::cout << "Rotated AimVector.Z : " << aimVec.Z << std::endl;
	std::cout << std::endl;
	//tmp.X -= aimVec.X*-13;//(world.GetCurrentPlayer().GetAimVector().X *-13);
	//tmp.Y -= (world.GetCurrentPlayer().GetAimVector().Y *-20);
	//tmp.Z -= aimVec.Z*-13;//(world.GetCurrentPlayer().GetAimVector().Z *-13);
	//tmp.X -= 13;
	//tmp.Z -= 13;
	//aimVec.Z += 13;
	//aimVec.Z -= 13;
	node->setPosition(tmp+offset);
	node->setRotation(world.GetCurrentPlayer().GetNodeRotation());
	
}