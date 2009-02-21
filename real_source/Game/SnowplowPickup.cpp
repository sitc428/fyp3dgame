#include "SnowplowPickup.h"
#include "GameWorld.h"
#include "Player.h"
#include "PlayerOnSnowplow.h"
#include "CollisionHelper.h"
#include "GameEngine.h"
#include "math.h"

static const irr::c8*		SNOWPLOW_PICKUP_MODEL  = "../art/characters/Snowplow/NoKidPlow.ms3d";
static const vector3df		SNOWPLOW_PICKUP_SCALE =	vector3df(1.f,1.f,1.f);

static const f32	RESPAWN_TIME = 60;  // 60 seconds
static const f32	PICKUP_PROXIMITY = 8.0f;

static const f32    ROTATION_PERIOD = 5;
static const f32	VERT_TRANSLATION_DIST = 10;
static const f32	VERT_TRANSLATION_PERIOD = 5;
static const f32	PICKUP_RADIUS = 5.0f;
static const f32	SNOWPLOW_PICKUP_REPLENISH_AMOUNT = 20.f; 

extern GameEngine* GEngine;


// constructor
SnowplowPickup::SnowplowPickup( GameWorld& gameWorld,
								const vector3df& position, 
								irr::video::IVideoDriver& driver )
:	Actor(gameWorld)
,	node(NULL)
,	pickupState(state_SP_ACTIVE)
,	respawnTimer(0.0f)
,	basePosition(position)
,	vertTranslationPhase(0.0f)
{
	ISceneManager& smgr = world.GetSceneManager();
	// construct a scene node which will represent this pickup
	IMesh* pickupMesh = smgr.getMesh( SNOWPLOW_PICKUP_MODEL );
	check(pickupMesh);
	node = smgr.addMeshSceneNode(
		pickupMesh,					// mesh
		NULL,						// parent
		-1,							// ID of the node
		position,					// position
		vector3df(0.0f,0.0f,0.0f),	// rotation
		SNOWPLOW_PICKUP_SCALE		// scale
		);
	check(node);

	node->setMaterialFlag( video::EMF_LIGHTING, true );
}

SnowplowPickup::~SnowplowPickup()
{
	// clean up the node upon deletion
	world.GetSceneManager().addToDeletionQueue( node );
}

// called every frame to update player
void SnowplowPickup::Tick( f32 delta )
{
	switch (pickupState)
	{	
		case state_SP_ACTIVE:
		{
			// animates the pickup, rotates it and moves it up and down
			Animate( delta );
			break;
		}
		case state_SP_RESPAWNING:
		{
			// update the respawn timer
			respawnTimer -= delta;
			if( respawnTimer <= 0.0f )
			{
				pickupState = state_SP_ACTIVE;
				// make the node visible again
				node->setVisible( true );
			}
			break;
		}
		default:
		{
			// should not be here
			check(FALSE);
		}
	}
}

// animates the pickup, rotates it and moves it up and down
void SnowplowPickup::Animate( f32 delta )
{
	// rotation about the Y axis
	vector3df currRot = node->getRotation();
	f32 rotDelta = 360 / ROTATION_PERIOD * delta;
	node->setRotation( currRot + vector3df( 0.0f, rotDelta, 0.0f ) );

	// vertical translation
	f32 transDelta = 360 / VERT_TRANSLATION_PERIOD * delta;
	vertTranslationPhase += transDelta;
	// convert the phase to radians
	f32 rad = vertTranslationPhase * (f32)M_PI / 180;
	f32 vertTranslation = PICKUP_RADIUS + VERT_TRANSLATION_DIST * (1 + sin(rad))/2;
	node->setPosition( basePosition + vector3df( 0.0f, vertTranslation, 0.0f ) );
}


// whether collision checks should be done by this actor
bool SnowplowPickup::ShouldPerformCollisionCheck() const
{
	if( pickupState == state_SP_ACTIVE )
	{
		// only check for collisions when this pickup is active
		return true;
	}

	return false;

}
// performs collision checks between this actor and other objects in the world
void SnowplowPickup::DoCollisions( const CollisionInfo& collInfo )
{
	// check if the player collided with us
	for( u32 i=0; i < collInfo.Actors.size(); ++i )
	{
		if( collInfo.Actors[i]->GetActorType() == ACTOR_PLAYER 
		||	collInfo.Actors[i]->GetActorType() == ACTOR_PLAYER_ON_SNOWPLOW )
		{
			if( CollisionHelper::CheckProximity( collInfo.Actors[i]->GetNode().getAbsolutePosition(), basePosition, PICKUP_PROXIMITY ) )
			{
				Player* player = dynamic_cast<Player*>( collInfo.Actors[i] );
				check(player);
				// to avoid giving the turned off player additional snowplow time,
				// turned off player remains in the old location so collision check picks him up
				if( player->IsActive() )
				{
					player->AddSnowplowTime( SNOWPLOW_PICKUP_REPLENISH_AMOUNT );
					player->PlayRandomCheer();
					GEngine->ChangeMusic( "../audio/music/plowmusic.mp3" );
					DoPickup();
				}
			}
		}
	}
}

// performs a pickup, puts the object in the respawning state
void SnowplowPickup::DoPickup()
{
	pickupState = state_SP_RESPAWNING;
	respawnTimer = RESPAWN_TIME;
	// hide the node
	node->setVisible( false );
}
