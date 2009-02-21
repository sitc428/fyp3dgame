#include "DynamiteProjectile.h"
#include "Check.h"
#include "GameEngine.h"
#include <irrlicht/irrlicht.h>
#include "ExplosionEffect.h"
#include "GameWorld.h"  // for collision info
#include "CollisionHelper.h"
#include "ParticleManager.h"

#if _DEBUG
#define DEBUG_DRAW_DYNAMITE_EXPLOSION 1
#else
#define DEBUG_DRAW_DYNAMITE_EXPLOSION 0
#endif

extern GameEngine* GEngine;

// Parameters specifying default projectile parameters
static const irr::c8*		DYNAMITE_MODEL  = "../art/characters/Dynamite/Dynamite.ms3d";
static const irr::c8*		SPARK_JOINT_NAME = "Spark";
static const irr::c8*		defaultTexture = "../art/characters/Snowball/snowball.bmp";

static const vector3df		defaultPosition = vector3df(0,-50,0);
static const vector3df		defaultRotation = vector3df(0,0,0);
static const vector3df		defaultScale = vector3df(1.0f,1.0f,1.0f);

static const f32			gravityScaleFactor = 7.0f;
static const vector3df		projectileGravity = vector3df(0.0f, -9.8f, 0.0f) * gravityScaleFactor;

static const f32			TIME_TILL_EXPLOSION = 3.0f;  // how long after the launch we want the dynamite to explode
static const f32			ROTATION_PERIOD = 0.85f;
static const f32			DYNAMITE_DAMAGE = 1.f;
static const f32			DAMAGE_RADIUS = 40.f;	
static const f32			BONE_ATTACHMENT_MIN_DISTANCE = 3.f;

array<stringc> DynamiteProjectile::ATTACH_JOINTS;

// constructor
DynamiteProjectile::DynamiteProjectile( GameWorld& gameWorld,
										IVideoDriver& driver )
:	Actor(gameWorld)
,	node(NULL)
,	meshNode(NULL)
,	sparkEmitter(NULL)
,	state(state_DYNAMITE_IDLE)
,	launchStartPosition(vector3df(0.0f,0.0f,0.0f))
,	launchVelocity(vector3df(0.0f,0.0f,0.0f))
,	launchElapsedTime(0.0f)
,	explodeElapsedTime(0.0f)
{
	// construct a scene node which will represent this projectile
	ISceneManager& smgr = world.GetSceneManager();
	ISkinnedMesh* dynamiteMesh = dynamic_cast<ISkinnedMesh*>(smgr.getMesh( DYNAMITE_MODEL ));
	check( dynamiteMesh );

	// create empty outer scene node
	node = smgr.addEmptySceneNode();
	check(node);
	node->setPosition(defaultPosition);
	node->setRotation(defaultRotation);

	meshNode = smgr.addAnimatedMeshSceneNode( 
		dynamiteMesh,
		node,							// parent
		-1,								// ID of the node
		vector3df(0.0f,0.0f,0.0f),		// position
		vector3df(0.0f,0.0f,0.0f),		// rotation
		defaultScale					// scale
		);
	check(meshNode);

	meshNode->setMaterialFlag( video::EMF_LIGHTING, false );
	meshNode->setMaterialTexture(0, driver.getTexture( defaultTexture ));

	// obtain a pointer to the spark joint to be able to attach a particle effect to it
	IBoneSceneNode* sparkNode = meshNode->getJointNode( SPARK_JOINT_NAME );
	check(sparkNode);

	// create the particle effect node and attach it to the spark node
	IParticleSystemSceneNode* particleNode = smgr.addParticleSystemSceneNode( false, sparkNode );
	sparkEmitter = GEngine->GetParticleManager().CreateDynamiteSparkEmitter( *particleNode );

	// initialize the static member if necessary
	if( ATTACH_JOINTS.size() == 0 )
	{
		InitAttachJoints();
	}
}

DynamiteProjectile::~DynamiteProjectile()
{
	// clean up the node upon deletion
	world.GetSceneManager().addToDeletionQueue( node );
	world.GetSceneManager().addToDeletionQueue( meshNode );
	// clear out the reference to the spark emitter
	sparkEmitter->drop();
	sparkEmitter = NULL;
}

// returns the projectile to the default state
void DynamiteProjectile::ResetProjectile()
{
	node->setPosition( defaultPosition );
	node->updateAbsolutePosition();
	launchStartPosition = defaultPosition;
	launchVelocity = vector3df(0.0f,0.0f,0.0f);
	launchElapsedTime = 0.0f;
}

// updates the projectile every frame with the elapsed time since last frame
void DynamiteProjectile::Tick( f32 delta )
{
	switch (state)
	{	
		case state_DYNAMITE_IDLE:
		{
			// do nothing, the projectile is waiting to be launched
			break;
		}
		case state_DYNAMITE_MOVING:
		{
			// update the elapsed time since launch
			launchElapsedTime += delta;

			// compute the position of the projectile based on the elapsed time 
			// x(t) = x + v*t + 1/2gt^2
			vector3df newPosition = launchStartPosition + launchVelocity*launchElapsedTime + (f32)0.5 * projectileGravity * launchElapsedTime * launchElapsedTime;
			node->setPosition( newPosition );

			if( launchElapsedTime > TIME_TILL_EXPLOSION )
			{
				Explode();
				break;
			}

			// if we've been moving for more than 4 sec, just stop the projectile simulation
			if( launchElapsedTime > 4 )
			{
				ResetProjectile();
				state = state_DYNAMITE_IDLE;
			}
			
			// rotate the dynamite when moving
			Animate( delta );
			break;
		}
		case state_DYNAMITE_ATTACHED:
		{
			launchElapsedTime += delta;

			if( launchElapsedTime > TIME_TILL_EXPLOSION )
			{
				Explode();
				break;
			}
			break;
		}
		case state_DYNAMITE_EXPLODE:
		{
			// create an explosion effect
			CreateExplosionEffect();

			// put the mesh in its original default position
			ResetProjectile();

			// playing only once causes silent dynamite weirdness, im just gonna lower the volume for now...
			//if( !GEngine->GetSoundEngine().isCurrentlyPlaying( "../audio/sfx/explode1.mp3" ) )
/*			{
				// play explosion sound effect
			ISound* sound = GEngine->GetSoundEngine().play3D( "../audio/sfx/explode1.mp3", node->getAbsolutePosition(), false, false, true );
				sound->setVolume( 0.65f );
				sound->setMinDistance( 70.0f );
				sound->drop();

				// play snow splatter sound
				sound = GEngine->GetSoundEngine().play3D( "../audio/sfx/snowsplatter.mp3", node->getAbsolutePosition(), false, false, true );
				sound->setMinDistance( 70.0f );
				sound->setVolume( 0.65f );
				sound->drop();
			}
*/
			state = state_DYNAMITE_IDLE;
			break;
		}
		default:
		{
			// should not be here
			check(FALSE);
		}
	}
}

// animates the projectile, rotates it when thrown
void DynamiteProjectile::Animate( f32 delta )
{
	// rotation about the Z axis
	vector3df currRot = meshNode->getRotation();
	f32 rotDelta = 360 / ROTATION_PERIOD * delta;
	meshNode->setRotation( currRot + vector3df( 0.0f, 0.0f, -rotDelta ) );
}

// launches the projectile, using specified start location, direction, and speed
void DynamiteProjectile::Launch( const vector3df& startPos, const vector3df& startRot, const vector3df& direction, f32 speed )
{
	check(state == state_DYNAMITE_IDLE);

	// set the initial position
	node->setPosition( startPos );
	node->setRotation( startRot );
	node->updateAbsolutePosition();

	// set the launch info data
	launchStartPosition = startPos;
	launchVelocity = direction * speed;
	launchElapsedTime = 0.0f;

	// starnsition to the moving state
	state = state_DYNAMITE_MOVING;
}

// causes an explosion of the projectile
void DynamiteProjectile::Explode()
{
	check( state == state_DYNAMITE_MOVING ||  state == state_DYNAMITE_ATTACHED ); // explosions should only happen to moving projectiles
	// detach the node if it was attached
	if( state == state_DYNAMITE_ATTACHED )
	{
		//dynamite is also in the attached state when its on the ground, in which case it doesn't have an attachParent 
		if( attachActorParent )
		{
			attachActorParent->DetachActor(*this);
		}
	}

	// change the particle state, tick will perform the explosion on the next frame
	state = state_DYNAMITE_EXPLODE;

	// deal damage to any enemies or players within the blast radius
	const array<Actor*>& actors = world.GetActors();
	for( u32 i=0; i < actors.size(); ++i )
	{
		u32 actorMask = ACTOR_ENEMY | ACTOR_ENEMY_TWO | ACTOR_ENEMY_BOSS | ACTOR_DYNAMITE;
		if( (actors[i]->GetActorType() & actorMask) != 0
		&&	actors[i] != this )
		{
			if( CollisionHelper::CheckProximity( actors[i]->GetNode().getAbsolutePosition(), node->getAbsolutePosition(), DAMAGE_RADIUS ) )
			{
				actors[i]->ReceiveDamage( DYNAMITE_DAMAGE );
			}
		}
	}

#if DEBUG_DRAW_DYNAMITE_EXPLOSION
// add a spherenode for debug display purposes
ISceneNode* debugSphere = world.GetSceneManager().addSphereSceneNode( 
		DAMAGE_RADIUS,			// radius
		8,						// polyCount
		NULL,					// parent
		-1,						// ID of the node
		node->getAbsolutePosition(),	// position
		defaultRotation,		// rotation
		defaultScale			// scale
		);
	check(debugSphere);

	debugSphere->setMaterialFlag( video::EMF_WIREFRAME, true );
	debugSphere->setMaterialFlag( video::EMF_LIGHTING, false );

	scene::ISceneNodeAnimator* anim = world.GetSceneManager().createDeleteAnimator( 500 );
	debugSphere->addAnimator( anim );
	anim->drop();
#endif //DEBUG_DRAW_DYNAMITE_EXPLOSION

}

// whether collision checks should be done on this projectile
bool DynamiteProjectile::ShouldPerformCollisionCheck() const
{
	if( state == state_DYNAMITE_MOVING )
	{
		// only check for collisions when this projectile is moving
		return true;
	}

	return false;
}

// performs collision handling with various objects in the world
void DynamiteProjectile::DoCollisions( const CollisionInfo& collInfo )
{
	check(attachActorParent == NULL);

	// get the bounding box for the projectile
	aabbox3d<f32> box = node->getTransformedBoundingBox();

	// create a slightly smaller bounding box
	vector3df middle = box.getCenter();
	vector3df diag = middle - box.MaxEdge;
	vector3df edge1 = vector3df(middle.X + diag.X/2, middle.Y + diag.Y/2, middle.Z + diag.Z/2);
	vector3df edge2 = vector3df(middle.X, middle.Y, middle.Z);
	aabbox3df preciseBox = aabbox3df(edge1, edge2);

	// check if we collided with the world, doing a simple Y check instead of bounding box check
	//if( CollisionHelper::CheckCollision( collInfo.LevelTriangleSelector, preciseBox/*box*/ ) )
	vector3df pos = node->getAbsolutePosition();
	if( node->getAbsolutePosition().Y <= 1.0f )
	{
		// play dynamite sticking sound
//		ISound* sound = GEngine->GetSoundEngine().play3D( "../audio/sfx/snowstick.mp3", node->getAbsolutePosition(), false, false, true );
//		sound->setMinDistance( 100.0f );
//		sound->drop();

		state = state_DYNAMITE_ATTACHED;
		return;
	}

	// check if we collided with any enemies
	for( u32 i=0; i < collInfo.Actors.size(); ++i )
	{
		if( collInfo.Actors[i]->GetActorType() == ACTOR_ENEMY
		||  collInfo.Actors[i]->GetActorType() == ACTOR_ENEMY_TWO
		||  collInfo.Actors[i]->GetActorType() == ACTOR_ENEMY_BOSS )
		{
			if( CollisionHelper::CheckCollision( collInfo.Actors[i]->GetNode().getTransformedBoundingBox(), box ) )
			{
				IAnimatedMeshSceneNode& meshNode = dynamic_cast<IAnimatedMeshSceneNode&>(collInfo.Actors[i]->GetNode());
				ISkinnedMesh& mesh = *dynamic_cast<ISkinnedMesh*>(meshNode.getMesh());
				array<ISkinnedMesh::SJoint*>& joints = mesh.getAllJoints();
				for( u32 j = 0; j < joints.size(); ++j )
				{
					const stringc& jointName = joints[j]->Name;

					// omitt joints that we're not supposed to attach to, i.e. hands and elbows of enemies
					if( ATTACH_JOINTS.linear_search( jointName ) == -1 )
					{
						continue;
					}

					// get the bone node corresponding to this joint
					IBoneSceneNode* jointNode = meshNode.getJointNode( jointName.c_str() );
					check(jointNode);

					f32 proximity = BONE_ATTACHMENT_MIN_DISTANCE;
					// add a little more to proximity for enemy two
					if( collInfo.Actors[i]->GetActorType() == ACTOR_ENEMY_TWO 
					&& (jointName == "BottomBall" || jointName == "MiddleBall") )
					{
						proximity += 2.5;
					}

					// add a little more to proximity for boss
					if( collInfo.Actors[i]->GetActorType() == ACTOR_ENEMY_BOSS  )
					{
						if(jointName == "BottomBall" )
						{
							proximity += 4;
						}
						else if(jointName == "MiddleBall")
						{
							proximity += 3;
						}
					}

					// check if we are within a proximity to this node
					if( CollisionHelper::CheckProximity(jointNode->getAbsolutePosition(),node->getAbsolutePosition(), proximity ) )
					{
						// play dynamite sticking sound
//						ISound* sound = GEngine->GetSoundEngine().play3D( "../audio/sfx/snowstick.mp3", node->getAbsolutePosition(), false, false, true );
//						sound->setMinDistance( 100.0f );
	//					sound->drop();

						// if we are then attach ourselves to this bone node
						collInfo.Actors[i]->AttachActor( *this, jointName.c_str() );
						check(attachActorParent == collInfo.Actors[i]);
						state = state_DYNAMITE_ATTACHED;
						break;
					}
				}
			}
		}
	}
}

// creates the explosion effect
void DynamiteProjectile::CreateExplosionEffect()
{
	// create the explosion effect
	ExplosionEffect* pEffect = world.GetFirstAvailableDynamiteExplosionEffect();
	if( pEffect )
	{
		pEffect->StartEffect(node->getAbsolutePosition());
	}
}

// called whenever a dynamite is affected by another dynamite explosion
void DynamiteProjectile::ReceiveDamage( f32 value )
{
	// don't do anything if the dynamite is already exploading
	if( state == state_DYNAMITE_EXPLODE )
	{
		return;
	}

	// otherwise explode
	Explode();
}

// called to setup the joints to exclude static member
void DynamiteProjectile::InitAttachJoints()
{
	ATTACH_JOINTS.push_back("BottomBall");
	ATTACH_JOINTS.push_back("MiddleBall");
	ATTACH_JOINTS.push_back("TopBall");
	ATTACH_JOINTS.push_back("SadHead");
	ATTACH_JOINTS.push_back("HappyHead");
}
	
