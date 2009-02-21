#ifndef ParticleManager_h
#define ParticleManager_h

#include <irrlicht/irrlicht.h>

using namespace irr;
using namespace irr::scene;
using namespace irr::core;
using namespace irr::video;

/**
* Class which provides methods for spawning various particle effects in the game
*/
class ParticleManager
{
public:

	// constructor
	explicit ParticleManager( ISceneManager& sceneManager );
	// destructor
	~ParticleManager();
/*
	// creates a snowball explosion particle emmiter and sets it for the owningNode, duration must be in milliseconds
	// returns the emitter which has been attached to the owning node
	IParticleEmitter* CreateSnowballExplosion( IParticleSystemSceneNode& owningNode, const u32 duration );
	// creates a dynamite explosion particle emmiter and sets it for the owningNode, duration must be in milliseconds
	// returns the emitter which has been attached to the owning node
	IParticleEmitter* CreateDynamiteExplosion( IParticleSystemSceneNode& owningNode, const u32 duration );
	// creates a snowplow snowblast particle emmiter and sets it for the owningNode
	// returns the emitter which has been attached to the owning node
	IParticleEmitter* CreateSnowplowSnowblast( IParticleSystemSceneNode& owningNode, const vector3df& direction );
	// creates a spark particle emmiter and sets it for the owningNode
	// returns the emitter which has been attached to the owning node
	IParticleEmitter* CreateDynamiteSparkEmitter( IParticleSystemSceneNode& owningNode );
	// creates snow explosion particles
	void CreateSnowExplosion( const vector3df& position, const u32 duration );
	IParticleEmitter* CreateSnowmanDeathExplosion( IParticleSystemSceneNode& owningNode, const u32 duration );
*/
	// creates a falling snow particle emmiter and sets it for the owningNode
	// returns the emitter which has been attached to the owning node
	IParticleEmitter* CreateFallingSnowEmitter( IParticleSystemSceneNode& owningNode );
private:
	
	ISceneManager&	smgr;	// scene manager from the engine
	ITexture*		SnowExplosionTexture;  // texture used for the snow explosion effect
	ITexture*		DynamiteExplosionTexture; // texture used for dynamite explosion effect
	ITexture*		ParticleWhiteTexture; // texture used for dynamite explosion effect
};

#endif //ParticleManager_h