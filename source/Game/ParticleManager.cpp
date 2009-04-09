#include "ParticleManager.h"
#include "GameEngine.h"
#include "Check.h"

static const irr::c8* SNOW_EXPLOSION_TEXTURE = "media/StartupScreen/irrLogo.png";
static const irr::c8* DYNAMITE_EXPLOSION_TEXTURE = "media/StartupScreen/irrLogo.png";
static const irr::c8* PARTICLE_WHITE_TEXTURE = "media/StartupScreen/irrLogo.png";

extern GameEngine* GEngine;

// constructor
	ParticleManager::ParticleManager( irr::scene::ISceneManager& sceneManager )
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
irr::scene::IParticleEmitter* ParticleManager::CreateSnowballExplosion( irr::scene::IParticleSystemSceneNode& owningNode, const irr::u32 duration )
{
// create an emitter for the particle effect
irr::scene::IParticleEmitter* em = owningNode.createBoxEmitter(
irr::core::aabbox3d<irr::f32>(-2,-2,-2,2,2,2),
irr::core::vector3df(0.0f,0.02f,0.0f),
100,
150,
irr::video::SColor(0,255,255,255),
irr::video::SColor(0,255,255,255),
duration,
duration,
180
);

owningNode.setEmitter( em );
owningNode.setParticleSize( irr::core::dimension2d<irr::f32>(2.0f, 2.0f) );
owningNode.setMaterialFlag( irr::video::EMF_LIGHTING, false );
owningNode.setMaterialTexture( 0, SnowExplosionTexture );
owningNode.setMaterialType(EMT_TRANSPARENT_VERTEX_ALPHA);

return em;
}

// creates a dynamite explosion particle emmiter and sets it for the owningNode, duration must be in milliseconds
irr::scene::IParticleEmitter* ParticleManager::CreateDynamiteExplosion( irr::scene::IParticleSystemSceneNode& owningNode, const irr::u32 duration )
{
irr::scene::IParticleEmitter* em = owningNode.createPointEmitter(
irr::core::vector3df(0.0f,0.05f,0.0f), // direction
500,     // minParticlesPerSecond
700, // maxParticlesPerSecond
irr::video::SColor(255,255,255,255), // minStartColor
irr::video::SColor(255,255,255,255), // maxStartColor
500, // lifeTimeMin
1000, // lifeTimeMax
100 // maxAngleDegrees
);

owningNode.setEmitter( em );

owningNode.setParticleSize( irr::core::dimension2d<irr::f32>(2.0f, 2.0f) );
owningNode.setParticlesAreGlobal( false );
owningNode.setMaterialFlag( irr::video::EMF_LIGHTING, false );
owningNode.setMaterialTexture( 0, DynamiteExplosionTexture );
owningNode.setMaterialType( EMT_TRANSPARENT_ALPHA_CHANNEL );

scene::IParticleAffector* paf1 = owningNode.createFadeOutParticleAffector(
irr::video::SColor(190,30,30,0),  // targetColor
duration  // timeNeededToFadeOut
); 
owningNode.addAffector(paf1);
paf1->drop();

scene::IParticleAffector* paf2 = owningNode.createGravityAffector(
irr::core::vector3df(0,-0.03f,0), // gravity
duration // timeForceLost
); 
owningNode.addAffector(paf2);
paf2->drop();

return em;
}

// creates a snowplow snowblast particle emmiter and sets it for the owningNode
// return the emitter which has been attached to the owning node
irr::scene::IParticleEmitter* ParticleManager::CreateSnowplowSnowblast( irr::scene::IParticleSystemSceneNode& owningNode, const irr::core::vector3df& direction )
{
irr::scene::IParticleEmitter* em = owningNode.createPointEmitter(
direction, // direction
0, // minParticlesPerSecond, 0 because the owner is responsible for controlling the count
	0, // maxParticlesPerSecond, 0 because the owner is responsible for controlling the count
	irr::video::SColor(0,255,255,255), // minStartColor
	irr::video::SColor(0,255,255,255), // maxStartColor
	2000, // lifeTimeMin
	2000, // lifeTimeMax
	20 // maxAngleDegrees
	);

	owningNode.setEmitter( em );

	owningNode.setParticleSize( irr::core::dimension2d<irr::f32>(3.0f, 3.0f) );
	owningNode.setParticlesAreGlobal( false );
	owningNode.setMaterialFlag( irr::video::EMF_LIGHTING, false );
	owningNode.setMaterialTexture( 0, SnowExplosionTexture );
	owningNode.setMaterialType( EMT_TRANSPARENT_VERTEX_ALPHA );

	scene::IParticleAffector* paf2 = owningNode.createGravityAffector(
			irr::core::vector3df(0,-0.09f,0), // gravity
			2000     // timeForceLost
			); 
	owningNode.addAffector(paf2);
	paf2->drop();

	return em;
	}

// creates a spark particle emmiter and sets it for the owningNode
// returns the emitter which has been attached to the owning node
irr::scene::IParticleEmitter* ParticleManager::CreateDynamiteSparkEmitter( irr::scene::IParticleSystemSceneNode& owningNode )
{
	irr::scene::IParticleEmitter* em = owningNode.createPointEmitter(
			irr::core::vector3df(0.0f,0.02f,0.0f), // direction
			100, // minParticlesPerSecond
			100, // maxParticlesPerSecond
			irr::video::SColor(0,255,255,255), // minStartColor
			irr::video::SColor(0,255,255,255), // maxStartColor
			200, // lifeTimeMin
			200, // lifeTimeMax
			180 // maxAngleDegrees
			);

	owningNode.setEmitter( em );

	owningNode.setParticleSize( irr::core::dimension2d<irr::f32>(1.0f, 1.0f) );
	owningNode.setParticlesAreGlobal( true );
	owningNode.setMaterialFlag( irr::video::EMF_LIGHTING, false );
	owningNode.setMaterialTexture( 0, SnowExplosionTexture );
	owningNode.setMaterialType( EMT_TRANSPARENT_VERTEX_ALPHA );

	return em;
}

// creates a falling snow particle emmiter and sets it for the owningNode
// returns the emitter which has been attached to the owning node

// creates snow explosion particles
void ParticleManager::CreateSnowExplosion( const irr::core::vector3df& position, const irr::u32 duration )
{
	// create smoke particle system
	irr::scene::IParticleSystemSceneNode* pas = 0;
	pas = smgr.addParticleSystemSceneNode( false, 0, -1, position );
	pas->setParticleSize( irr::core::dimension2d<irr::f32>(2.0f, 2.0f) );

	irr::scene::IParticleEmitter* em = pas->createBoxEmitter(
			irr::core::aabbox3d<irr::f32>(-10,-10,-10,15,20,15),
			irr::core::vector3df(0.0f,0.02f,0.0f),
			150,
			200,
			irr::video::SColor(0,255,255,255),
			irr::video::SColor(0,255,255,255),
			duration,
			duration,
			180
			);

	pas->setEmitter( em );
	em->drop();

	pas->setMaterialFlag( irr::video::EMF_LIGHTING, false );
	pas->setMaterialTexture( 0, SnowExplosionTexture );
	pas->setMaterialType(EMT_TRANSPARENT_VERTEX_ALPHA);

	scene::IParticleAffector* paf = pas->createGravityAffector(
			irr::core::vector3df(0,-0.03f,0), // gravity
			duration     // timeForceLost
			); 
	pas->addAffector(paf);
	paf->drop();

	irr::scene::ISceneNodeAnimator* anim = smgr.createDeleteAnimator( duration -400);
	pas->addAnimator( anim );
	anim->drop();
}

irr::scene::IParticleEmitter* ParticleManager::CreateSnowmanDeathExplosion( irr::scene::IParticleSystemSceneNode& owningNode, const irr::u32 duration )
{
	irr::scene::IParticleEmitter* em2 = owningNode.createPointEmitter(
			irr::core::vector3df(0.0f,0.07f,0.0f), // direction
			500, // minParticlesPerSecond
			600, // maxParticlesPerSecond
			irr::video::SColor(0,255,255,255), // minStartColor
			irr::video::SColor(0,255,255,255), // maxStartColor
			duration, // lifeTimeMin
			duration, // lifeTimeMax
			50 // maxAngleDegrees
			);

	owningNode.setEmitter( em2 );
	owningNode.setParticleSize( irr::core::dimension2d<irr::f32>(3.0f, 3.0f) );
	owningNode.setParticlesAreGlobal( true );
	owningNode.setMaterialFlag( irr::video::EMF_LIGHTING, false );
	owningNode.setMaterialTexture( 0, SnowExplosionTexture );
	owningNode.setMaterialType( EMT_TRANSPARENT_VERTEX_ALPHA );

	scene::IParticleAffector* paf = owningNode.createGravityAffector(
			irr::core::vector3df(0,-0.25f,0), // gravity
			duration     // timeForceLost
			); 
	owningNode.addAffector(paf);
	paf->drop();

	return em2;
}

irr::scene::IParticleEmitter* ParticleManager::CreateFallingSnowEmitter( irr::scene::IParticleSystemSceneNode& owningNode )
{
	owningNode.setPosition(irr::core::vector3df(0.f,200.f,0.f));
	owningNode.setParticleSize( irr::core::dimension2d<irr::f32>(2.0f, 2.0f) );

	irr::scene::IParticleEmitter* em = owningNode.createBoxEmitter(
			irr::core::aabbox3d<irr::f32>(-600,0,-400,400,20,400),
			irr::core::vector3df(0.0f,-0.01f,0.0f),
			180,
			200,
			irr::video::SColor(0,255,255,255),
			irr::video::SColor(0,255,255,255),
			21000,
			21000,
			0
			);

	owningNode.setEmitter( em );
	em->drop();

	owningNode.setMaterialFlag( irr::video::EMF_LIGHTING, false );
	owningNode.setMaterialTexture( 0, ParticleWhiteTexture );
	owningNode.setMaterialType( irr::video::EMT_TRANSPARENT_ADD_COLOR );

	return em;
}
 	*/
