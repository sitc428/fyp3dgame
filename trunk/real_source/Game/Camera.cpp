#include "Camera.h"
#include "Check.h"
#include "GameEngine.h"
#include "GameWorld.h"
#include "Player.h"
#include <irrlicht/irrlicht.h>

// Parameters specifying default parameters
static const irr::core::vector3df defaultPosition = irr::core::vector3df(40,60,45);
static const irr::core::vector3df defaultRotation = irr::core::vector3df(0,-90,0);
static const irr::core::vector3df cameraOffset = irr::core::vector3df(0, 18.0f, 26.0f);

// constructor
Camera::Camera( GameWorld& gameWorld,
		irr::video::IVideoDriver& driver,
		irr::scene::ITriangleSelector& levelSelector,
		Player& player )
	: Actor(gameWorld)
	,   node(NULL)
	, levelTriangleSelector(levelSelector)
	, target(&player)
	  , lastSelectedSceneNode(NULL)
{
	node = world.GetSceneManager().addCameraSceneNode( 0, defaultPosition, target->GetNodePosition());
	check( node ); 

	node->setPosition( defaultPosition );
	node->setRotation( defaultRotation );

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
	// **WIP** - hide any obstruction betweeen camera and player
	/* line3d<irr::f32> ray;
	   ray.end = target.GetPosition();
	   ray.start = node->getAbsolutePosition();
	   ray.start.Y = ray.end.Y;

	   irr::scene::ISceneNode* selectedSceneNode = world.GetSceneManager().getSceneCollisionManager()->getSceneNodeFromRayBB(ray);

	   if( selectedSceneNode )
	   {
	   if( selectedSceneNode->getID() != 999 )
	   {
	   selectedSceneNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	   }

	// if( lastSelectedSceneNode )
	// lastSelectedSceneNode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
	// lastSelectedSceneNode = selectedSceneNode;
	// }

	}
	*/
Player* player = (Player *)target;
irr::core::vector3df rotation = player->GetRotation();

irr::core::vector3df aimVector = target->GetAimVector();
irr::core::vector3df position = target->GetNodePosition();
position -= target->GetAimVector() * cameraOffset.Z;
position.Y += cameraOffset.Y - rotation.X;

// update camera position
node->setPosition( position );



// update target position
node->setTarget( target->GetNodePosition() + irr::core::vector3df(0.0f, cameraOffset.Y + rotation.X, 0.0f) );
}
