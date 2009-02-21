#include "ParticleManager.h"
#include "GameEngine.h"
#include "Check.h"

using namespace irr::core;
using namespace irr::video;

static const irr::c8*		SNOW_EXPLOSION_TEXTURE = "../art/sfx/Particles/smoke.bmp";
static const irr::c8*		DYNAMITE_EXPLOSION_TEXTURE = "../art/sfx/Particles/SparkTex.tga";
static const irr::c8*		PARTICLE_WHITE_TEXTURE = "../art/sfx/Particles/snowflake.png";

extern GameEngine* GEngine;

// constructor
ParticleManager::ParticleManager( ISceneManager& sceneManager )
	: smgr(sceneManager)
	, SnowExplosionTexture(NULL)
	, DynamiteExplosionTexture(NULL)
	, ParticleWhiteTexture(NULL)
{
	// load all the particle effects resources
	SnowExplosionTexture = GEngine->GetDriver().getTexture( SNOW_EXPLOSION_TEXTURE );
	check(SnowExplosionTexture);

	DynamiteExplosionTexture = GEngine->GetDriver().getTexture( DYNAMITE_EXPLOSION_TEXTURE );
	check(DynamiteExplosionTexture);

	ParticleWhiteTexture = GEngine->GetDriver().getTexture( PARTICLE_WHITE_TEXTURE );
	check(ParticleWhiteTexture);
}

ParticleManager::~ParticleManager()
{
	// clear all the particle effects resoruces
	GEngine->GetDriver().removeTexture( SnowExplosionTexture );
	SnowExplosionTexture = NULL;
	GEngine->GetDriver().removeTexture( DynamiteExplosionTexture );
	SnowExplosionTexture = NULL;
	GEngine->GetDriver().removeTexture( ParticleWhiteTexture );
	SnowExplosionTexture = NULL;
}
/*
// creates a snowball explosion particle emmiter and sets it for the owningNode, duration must be in milliseconds
IParticleEmitter* ParticleManager::CreateSnowballExplosion( IParticleSystemSceneNode& owningNode, const u32 duration )
{
	// create an emitter for the particle effect
	scene::IParticleEmitter* em = owningNode.createBoxEmitter(
		core::aabbox3d<f32>(-2,-2,-2,2,2,2),
		core::vector3df(0.0f,0.02f,0.0f),
		100,
		150,
		SColor(0,255,255,255),
		SColor(0,255,255,255),
		duration,
		duration,
		180
		);

	owningNode.setEmitter( em );
	owningNode.setParticleSize( dimension2d<f32>(2.0f, 2.0f) );
	owningNode.setMaterialFlag( EMF_LIGHTING, false );
	owningNode.setMaterialTexture( 0, SnowExplosionTexture );
	owningNode.setMaterialType(EMT_TRANSPARENT_VERTEX_ALPHA);

	return em;
}

// creates a dynamite explosion particle emmiter and sets it for the owningNode, duration must be in milliseconds
IParticleEmitter* ParticleManager::CreateDynamiteExplosion( IParticleSystemSceneNode& owningNode, const u32 duration )
{
	scene::IParticleEmitter* em = owningNode.createPointEmitter(
		vector3df(0.0f,0.05f,0.0f),		// direction
		500,						    // minParticlesPerSecond
		700,							// maxParticlesPerSecond
		video::SColor(255,255,255,255),	// minStartColor
		video::SColor(255,255,255,255),	// maxStartColor
		500,							// lifeTimeMin
		1000,							// lifeTimeMax
		100								// maxAngleDegrees
		);

	owningNode.setEmitter( em );

	owningNode.setParticleSize( dimension2d<f32>(2.0f, 2.0f) );
	owningNode.setParticlesAreGlobal( false );
	owningNode.setMaterialFlag( EMF_LIGHTING, false );
	owningNode.setMaterialTexture( 0, DynamiteExplosionTexture );
	owningNode.setMaterialType( EMT_TRANSPARENT_ALPHA_CHANNEL );

	scene::IParticleAffector* paf1 = owningNode.createFadeOutParticleAffector(
		video::SColor(190,30,30,0),  // targetColor
		duration					 // timeNeededToFadeOut
		);	
	owningNode.addAffector(paf1);
	paf1->drop();

	scene::IParticleAffector* paf2 = owningNode.createGravityAffector(
		vector3df(0,-0.03f,0),	// gravity
		duration				// timeForceLost
		);	
	owningNode.addAffector(paf2);
	paf2->drop();

	return em;
}

// creates a snowplow snowblast particle emmiter and sets it for the owningNode
// return the emitter which has been attached to the owning node
IParticleEmitter* ParticleManager::CreateSnowplowSnowblast( IParticleSystemSceneNode& owningNode, const vector3df& direction )
{
	IParticleEmitter* em = owningNode.createPointEmitter(
		direction,						// direction
		0,								// minParticlesPerSecond, 0 because the owner is responsible for controlling the count
		0,								// maxParticlesPerSecond, 0 because the owner is responsible for controlling the count
		video::SColor(0,255,255,255),	// minStartColor
		video::SColor(0,255,255,255),	// maxStartColor
		2000,							// lifeTimeMin
		2000,							// lifeTimeMax
		20								// maxAngleDegrees
		);

	owningNode.setEmitter( em );

	owningNode.setParticleSize( dimension2d<f32>(3.0f, 3.0f) );
	owningNode.setParticlesAreGlobal( false );
	owningNode.setMaterialFlag( EMF_LIGHTING, false );
	owningNode.setMaterialTexture( 0, SnowExplosionTexture );
	owningNode.setMaterialType( EMT_TRANSPARENT_VERTEX_ALPHA );

	scene::IParticleAffector* paf2 = owningNode.createGravityAffector(
		vector3df(0,-0.09f,0),	// gravity
		2000    				// timeForceLost
		);	
	owningNode.addAffector(paf2);
	paf2->drop();

	return em;
}

// creates a spark particle emmiter and sets it for the owningNode
// returns the emitter which has been attached to the owning node
IParticleEmitter* ParticleManager::CreateDynamiteSparkEmitter( IParticleSystemSceneNode& owningNode )
{
	IParticleEmitter* em = owningNode.createPointEmitter(
		vector3df(0.0f,0.02f,0.0f),		// direction
		100,							// minParticlesPerSecond
		100,							// maxParticlesPerSecond
		video::SColor(0,255,255,255),	// minStartColor
		video::SColor(0,255,255,255),	// maxStartColor
		200,							// lifeTimeMin
		200,							// lifeTimeMax
		180								// maxAngleDegrees
		);

	owningNode.setEmitter( em );

	owningNode.setParticleSize( dimension2d<f32>(1.0f, 1.0f) );
	owningNode.setParticlesAreGlobal( true );
	owningNode.setMaterialFlag( EMF_LIGHTING, false );
	owningNode.setMaterialTexture( 0, SnowExplosionTexture );
	owningNode.setMaterialType( EMT_TRANSPARENT_VERTEX_ALPHA );

	return em;
}

// creates a falling snow particle emmiter and sets it for the owningNode
// returns the emitter which has been attached to the owning node

// creates snow explosion particles
void ParticleManager::CreateSnowExplosion( const vector3df& position, const u32 duration )
{
	// create smoke particle system
	IParticleSystemSceneNode* pas = 0;
	pas = smgr.addParticleSystemSceneNode( false, 0, -1, position );
	pas->setParticleSize( dimension2d<f32>(2.0f, 2.0f) );

	scene::IParticleEmitter* em = pas->createBoxEmitter(
		core::aabbox3d<f32>(-10,-10,-10,15,20,15),
		core::vector3df(0.0f,0.02f,0.0f),
		150,
		200,
		SColor(0,255,255,255),
		SColor(0,255,255,255),
		duration,
		duration,
		180
		);

	pas->setEmitter( em );
	em->drop();

	pas->setMaterialFlag( EMF_LIGHTING, false );
	pas->setMaterialTexture( 0, SnowExplosionTexture );
	pas->setMaterialType(EMT_TRANSPARENT_VERTEX_ALPHA);

	scene::IParticleAffector* paf = pas->createGravityAffector(
		vector3df(0,-0.03f,0),	// gravity
		duration    			// timeForceLost
		);	
	pas->addAffector(paf);
	paf->drop();

	scene::ISceneNodeAnimator* anim = smgr.createDeleteAnimator( duration -400);
	pas->addAnimator( anim );
	anim->drop();
}

IParticleEmitter* ParticleManager::CreateSnowmanDeathExplosion( IParticleSystemSceneNode& owningNode, const u32 duration )
{
	IParticleEmitter* em2 = owningNode.createPointEmitter(
		vector3df(0.0f,0.07f,0.0f),		// direction
		500,							// minParticlesPerSecond
		600,							// maxParticlesPerSecond
		video::SColor(0,255,255,255),	// minStartColor
		video::SColor(0,255,255,255),	// maxStartColor
		duration,						// lifeTimeMin
		duration,						// lifeTimeMax
		50								// maxAngleDegrees
		);

	owningNode.setEmitter( em2 );
	owningNode.setParticleSize( dimension2d<f32>(3.0f, 3.0f) );
	owningNode.setParticlesAreGlobal( true );
	owningNode.setMaterialFlag( EMF_LIGHTING, false );
	owningNode.setMaterialTexture( 0, SnowExplosionTexture );
	owningNode.setMaterialType( EMT_TRANSPARENT_VERTEX_ALPHA );

	scene::IParticleAffector* paf = owningNode.createGravityAffector(
		vector3df(0,-0.25f,0),	// gravity
		duration    			// timeForceLost
		);	
	owningNode.addAffector(paf);
	paf->drop();

	return em2;
}
*/
IParticleEmitter* ParticleManager::CreateFallingSnowEmitter( IParticleSystemSceneNode& owningNode )
{
	owningNode.setPosition(vector3df(0.f,200.f,0.f));
	owningNode.setParticleSize( dimension2d<f32>(2.0f, 2.0f) );
	
	scene::IParticleEmitter* em = owningNode.createBoxEmitter(
															  core::aabbox3d<f32>(-600,0,-400,400,20,400),
															  core::vector3df(0.0f,-0.01f,0.0f),
															  180,
															  200,
															  SColor(0,255,255,255),
															  SColor(0,255,255,255),
															  21000,
															  21000,
															  0
															  );
	
	owningNode.setEmitter( em );
	em->drop();
	
	owningNode.setMaterialFlag( EMF_LIGHTING, false );
	owningNode.setMaterialTexture( 0, ParticleWhiteTexture );
	owningNode.setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
	
	return em;
}
