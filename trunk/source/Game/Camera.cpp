#include "Camera.h"
#include "Check.h"
#include "GameEngine.h"
#include "GameWorld.h"
#include "Player.h"
#include "InputEventReceiver.hpp"
#include <irrlicht/irrlicht.h>

// Parameters specifying default parameters
static const irr::core::vector3df cameraOffset = irr::core::vector3df(0.0f, 50.0f, 100.0f);

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
	node = world.GetSceneManager().addCameraSceneNode(0);
	node->setAutomaticCulling( irr::scene::EAC_FRUSTUM_BOX );
	node->setFarValue( 1000 );
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

	irr::core::vector3df aimVector = target->GetAimVector();
	irr::core::vector3df position = target->GetNodePosition();
	position -= aimVector * zoom * cameraOffset.Z;
	position.Y += cameraOffset.Y;
	//position += target->GetAimVector() * zoom * cameraOffset.Z;
	//position.Y += zoom * cameraOffset.Y - rotation.X;

	// update camera position
	node->setPosition( position );

	// update target position
	//node->setTarget( target->GetNodePosition() + irr::core::vector3df(0.0f, cameraOffset.Y + rotation.X, 0.0f) );
	node->setTarget( target->GetNodePosition() + aimVector * 50 );

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
		zoom = 3.0;

	//translation += cameraTranslation * delta;
}
