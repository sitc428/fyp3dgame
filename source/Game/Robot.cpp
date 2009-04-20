#include "Robot.hpp"
#include "Check.hpp"
#include "GameEngine.hpp"
#include "GameWorld.hpp"
#include "MainCharacter.hpp"
#include "ShaderFactory.hpp"
#include <ctime>
#include <iostream>

static const irr::core::vector3df	defaultPosition = irr::core::vector3df(10,50,10);
static const irr::core::vector3df	defaultRotation = irr::core::vector3df(0, 90, 0);
static const irr::core::vector3df	defaultScale = irr::core::vector3df(0.1, 0.1, 0.1);

static const irr::c8*		ROBOT_MODEL  = "media/model/robot22.x";
static const irr::c8*		defaultTexture0 = "media/model/robot_UV.png";
static const irr::c8*		defaultTexture1 = "media/model/shade_line.png";

Robot::Robot( GameEngine& gameEngine, GameWorld& gameWorld )
	:Player(gameEngine, gameWorld),
	node(NULL),
	collisionAnimator(NULL)
{
	Shader* shader = GEngine.GetShaderFactory().createShader( "media/shader/robot.vert", "media/shader/robot.frag", 2, irr::video::EMT_SOLID );

	irr::video::IVideoDriver& driver = GEngine.GetDriver();

	irr::scene::ISceneManager& smgr = world.GetSceneManager();
	// load the animated mesh, and add a new scene graph node for it
	irr::scene::ISkinnedMesh* robotMesh = (irr::scene::ISkinnedMesh*)(smgr.getMesh( ROBOT_MODEL ));
	node = smgr.addAnimatedMeshSceneNode( robotMesh, smgr.getRootSceneNode() );
	node->setPosition( defaultPosition );
	node->setID( 999 );
	node->setRotation( defaultRotation );
	if(GEngine.GetShaderFactory().ShaderAvailable())
		node->setMaterialType((irr::video::E_MATERIAL_TYPE) shader->GetShaderMaterial());
	else 
		node->setMaterialType(irr::video::EMT_SOLID);
	node->setMaterialTexture(0, driver.getTexture( defaultTexture0 ));
	node->setMaterialTexture(1, driver.getTexture( defaultTexture1 ));
	//node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
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

void Robot::RecreateCollisionResponseAnimator()
{
	// drop the current collision response animator
	if( collisionAnimator )
	{
		node->removeAnimator( collisionAnimator );
		collisionAnimator->drop();
		collisionAnimator = NULL;
	}

	// setup torso collision with the world
	irr::core::aabbox3df box = node->getMesh()->getMesh(0)->getBoundingBox();
	irr::core::vector3df radius = box.MaxEdge - box.getCenter();

	collisionAnimator = world.GetSceneManager().createCollisionResponseAnimator(
			&world.GetLevelTriangleSelector(), node, radius, irr::core::vector3df(0,-0.08,0), // gravity
			irr::core::vector3df(0, 0, 0), // ellipsoid translation
			0); // sliding value

	node->addAnimator(collisionAnimator);
}

static irr::f32 floating( irr::f32 delta, irr::s32 range )
{
	static irr::f32 total_delta = 0;
	total_delta += delta;
	return range * sin( total_delta * 2 );
}

void Robot::Tick( irr::f32 delta )
{
	//! random the y offset of the robot
	irr::core::vector3df offset = irr::core::vector3df( 0, floating( delta, 5), 0);

	//! get the direction the main character facing
	irr::core::vector3df aimVec = world.GetCurrentPlayer().GetFaceVector();

	//! put the robot at the right position
	irr::core::vector3df tmp = world.GetCurrentPlayer().GetNodePosition() - aimVec * -10;
	tmp.rotateXZBy(90, world.GetCurrentPlayer().GetNodePosition());

	//! set the position of the robot
	node->setPosition(tmp+offset);
	node->setRotation(world.GetCurrentPlayer().GetNodeRotation());
}