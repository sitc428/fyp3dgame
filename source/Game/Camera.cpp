#include "Camera.h"
#include "Check.h"
#include "GameEngine.h"
#include "GameWorld.h"
#include "Player.h"
#include "InputEventReceiver.hpp"
#include <irrlicht/irrlicht.h>

// Parameters specifying default parameters
static const irr::core::vector3df defaultPosition = irr::core::vector3df(0, 60, 10);
static const irr::core::vector3df defaultRotation = irr::core::vector3df(0, 0, 0);
static const irr::core::vector3df cameraOffset = irr::core::vector3df(0.0f, 30.0f, 60.0f);

extern GameEngine* GEngine;

// constructor
Camera::Camera( GameWorld& gameWorld,
		irr::video::IVideoDriver& driver,
		irr::scene::ITriangleSelector& levelSelector,
		Player& player )
	:Actor(gameWorld),
	node(NULL),
	levelTriangleSelector(levelSelector),
	target(&player),
	lastSelectedSceneNode(NULL),
	zoom(1)
{
	//node = world.GetSceneManager().addCameraSceneNode( 0, defaultPosition, target->GetNodePosition());
	node = world.GetSceneManager().addCameraSceneNode( 0, defaultPosition, irr::core::vector3df(0, 0, 0) );

	node->setPosition( defaultPosition );
	node->setRotation( defaultRotation );

	node->setAutomaticCulling( irr::scene::EAC_FRUSTUM_BOX );
	node->setFarValue( 500 );

	// setup camera collision with the world
	/* irr::scene::ISceneNodeAnimator* anim = world.GetSceneManager().createCollisionResponseAnimator(
	   &levelTriangleSelector, node, irr::core::vector3df( 5, 5, 5 ),
	   irr::core::vector3df(0, 0, 0 ), // gravity
	   irr::core::vector3df( 0, 0, 0 ), // ellipsoid translation
	   0.0001f ); // sliding value
	   node->addAnimator(anim);
	   anim->drop();
	   */
}

// destructor, protected to force user to call Actor::DestroyActor
Camera::~Camera()
{
	world.GetSceneManager().addToDeletionQueue( node );
}

// changes the look at target for this camera
void Camera::SetAimTarget( Player& player )
{
	target = &player;
}

// get camera's target's position
irr::core::vector3df Camera::GetTarget()
{
	return target->GetNodePosition();
}

// updates the camera every fram with the elapsed time since last frame
void Camera::Tick( irr::f32 delta )
{
	DoInput( delta );

	/*node->setPosition( target->GetNode().getAbsolutePosition() + zoom * cameraOffset + translation);

	node->setTarget( target->GetNodePosition() + translation );

	irr::core::position2d<irr::s32> mouseDelta = GEngine->GetMouseDelta();
	irr::f32 mouseDX = mouseDelta.X * 0.2f;
	irr::f32 mouseDY = mouseDelta.Y * 0.075f;
	if( mouseDX || mouseDY)
	{
		node->setRotation( irr::core::vector3df( -mouseDY, mouseDX, 0.0f) );
	}*/

	Player* player = (Player *)target;
	irr::core::vector3df rotation = player->GetRotation();

	irr::core::vector3df aimVector = target->GetAimVector();
	irr::core::vector3df position = target->GetNodePosition();
	position += target->GetAimVector() * zoom * cameraOffset.Z;
	position.Y += zoom * cameraOffset.Y - rotation.X;

	// update camera position
	node->setPosition( position );

	// update target position
	node->setTarget( target->GetNodePosition() + irr::core::vector3df(0.0f, cameraOffset.Y + rotation.X, 0.0f) );

}

void Camera::DoInput( irr::f32 delta )
{
	InputEventReceiver& receiver = GEngine->GetReceiver();

	/*irr::core::vector3df cameraTranslation(0, 0, 0);

	if(receiver.keyDown(irr::KEY_KEY_1))
	{
		cameraTranslation.Y = 20;
	}
	else if(receiver.keyDown(irr::KEY_KEY_2))
	{
		cameraTranslation.Y = -20;
	}
	else if(receiver.keyDown(irr::KEY_KEY_Q))
	{
		cameraTranslation.X = 20;
	}
	else if(receiver.keyDown(irr::KEY_KEY_E))
	{
		cameraTranslation.X = -20;
	}*/

	zoom = zoom - receiver.wheel() * delta;

	if( zoom < 0.5 )
		zoom = 0.5;
	if( zoom > 3.0 )
		zoom = 2.0;

	//translation += cameraTranslation * delta;
}
