#include "Camera.hpp"
#include "Check.hpp"
#include "GameEngine.hpp"
#include "GameWorld.hpp"
#include "Player.hpp"
#include "InputEventReceiver.hpp"
#include <irrlicht/irrlicht.h>

// Parameters specifying default parameters
static irr::core::vector3df cameraOffset = irr::core::vector3df(0.0f, 50.0f, 100.0f);

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
	node->setAutomaticCulling( irr::scene::EAC_OFF );
	node->setFarValue( 750 );
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

	// update camera position
	node->setPosition( position );

	// update target position
	//node->setTarget( target->GetNodePosition() + irr::core::vector3df(0.0f, cameraOffset.Y + rotation.X, 0.0f) );
	node->setTarget( target->GetNodePosition() + aimVector * 50 );

}

void Camera::DoInput( irr::f32 delta )
{
	InputEventReceiver& receiver = GEngine->GetReceiver();

	if( receiver.keyDown( irr::KEY_KEY_W) )
	{
		if(cameraOffset.Y < 80)
			cameraOffset.Y += 5;
	}
	else if( receiver.keyDown( irr::KEY_KEY_S) )
	{
		if(cameraOffset.Y > 20)
			cameraOffset.Y -= 5;
	}

	zoom = zoom - receiver.wheel() * delta;

	if( zoom < 0.5 )
		zoom = 0.5;
	if( zoom > 3.0 )
		zoom = 3.0;

	//translation += cameraTranslation * delta;
}
