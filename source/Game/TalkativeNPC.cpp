#include "GameEngine.hpp"
#include "GameHUD.hpp"
#include "GameWorld.hpp"
#include "InputEventReceiver.hpp"
#include "TalkativeNPC.hpp"

TalkativeNPC::TalkativeNPC( GameEngine& gameEngine, GameWorld& gameWorld, const irr::c8* mesh, irr::core::array<irr::core::stringw>& dialogs, irr::video::ITexture* header,irr::f32 acceptableDistance, const irr::core::vector3df defaultPosition, const irr::core::vector3df defaultRotation, const irr::core::vector3df defaultScale)
	: InteractiveActor(gameEngine, gameWorld),
	_header(header),
	acceptable_Distance(acceptableDistance)
{
	irr::scene::ISceneManager& smgr = world.GetSceneManager();
	node = smgr.addAnimatedMeshSceneNode(smgr.getMesh(mesh), smgr.getRootSceneNode());
	node->setPosition(defaultPosition);
	node->setRotation(defaultRotation);
	node->setScale(defaultScale);

	irr::scene::ITriangleSelector* meshTriangleSelector = smgr.createOctTreeTriangleSelector( ((irr::scene::IAnimatedMeshSceneNode*)node)->getMesh(), node );
	node->setTriangleSelector( meshTriangleSelector );
	world.GetLevelTriangleSelector().addTriangleSelector( meshTriangleSelector );
	meshTriangleSelector->drop();
	meshTriangleSelector = NULL;

	int noDialog = dialogs.size();
	for(int i = 0; i < noDialog; ++i)
	{
		_dialogs.push_back(dialogs[i]);
	}

	this->RecreateCollisionResponseAnimator();
}

TalkativeNPC::~TalkativeNPC()
{
}

void TalkativeNPC::RecreateCollisionResponseAnimator()
{
	// drop the current collision response animator
	if( collisionAnimator )  // soft fail which allows us to call RecreateCollisionResponseAnimator to first initialize the non-existing animator
	{
		node->removeAnimator( collisionAnimator );
		collisionAnimator->drop();
		collisionAnimator = NULL;
	}

	// setup torso collision with the world
	irr::core::aabbox3df box = node->getMesh()->getBoundingBox();
	irr::core::vector3df radius = box.MaxEdge - box.getCenter();

	collisionAnimator = world.GetSceneManager().createCollisionResponseAnimator(
		&world.GetLevelTriangleSelector(), node, radius,
		irr::core::vector3df(0,-.08f,0), // gravity
		irr::core::vector3df(0, 0, 0), // ellipsoid translation
		0.0001f); // sliding value

	node->addAnimator(collisionAnimator);
}

void TalkativeNPC::interaction(irr::f32 delta)
{
	static int state = 0;
	static int talking = 0;
	static int currentline = 1;
	static double timeElapsed = 0;
	
	if(state == 0)
	{
		if(talking < _dialogs.size())
		{
			if(currentline <= _dialogs[talking].size())
			{
				if(timeElapsed > 0.05)
				{
					irr::core::stringw temp  = _dialogs[talking].subString(0, currentline);
					world.GetGameHUD()->GetConversation(temp, _header);
					++currentline;
					timeElapsed = 0;
				}
			}
			else
			{
				++talking;
				state = 1;
				currentline = 1;
			}
		}
		else
		{
			world.GetGameHUD()->GetConversation("");
			timeElapsed = 0;
			finishAction();
			talking = 0;
		}
	}
	else if(state == 1)
	{
		InputEventReceiver& receiver = GEngine.GetReceiver();

		if(receiver.keyReleased(irr::KEY_KEY_V))
		{
			state = 0;
		}
	}

	timeElapsed += delta;
}

irr::f32 TalkativeNPC::acceptableDistance()
{
	return acceptable_Distance;
}
