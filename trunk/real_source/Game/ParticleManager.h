#ifndef ParticleManager_h
#define ParticleManager_h

#include <irrlicht/irrlicht.h>

/**
 * Class which provides methods for spawning various particle effects in the game
 */
class ParticleManager
{
	public:

		// constructor
		explicit ParticleManager( irr::scene::ISceneManager& sceneManager );
		// destructor
		~ParticleManager();
		/*
		// creates a snowball explosion particle emmiter and sets it for the owningNode, duration must be in milliseconds
		// returns the emitter which has been attached to the owning node
		irr::scene::IParticleEmitter* CreateSnowballExplosion( irr::scene::IParticleSystemSceneNode& owningNode, const irr::u32 duration );
		// creates a dynamite explosion particle emmiter and sets it for the owningNode, duration must be in milliseconds
		// returns the emitter which has been attached to the owning node
		irr::scene::IParticleEmitter* CreateDynamiteExplosion( irr::scene::IParticleSystemSceneNode& owningNode, const irr::u32 duration );
		// creates a snowplow snowblast particle emmiter and sets it for the owningNode
		// returns the emitter which has been attached to the owning node
		irr::scene::IParticleEmitter* CreateSnowplowSnowblast( irr::scene::IParticleSystemSceneNode& owningNode, const irr::core::vector3df& direction );
		// creates a spark particle emmiter and sets it for the owningNode
		// returns the emitter which has been attached to the owning node
		irr::scene::IParticleEmitter* CreateDynamiteSparkEmitter( irr::scene::IParticleSystemSceneNode& owningNode );
		// creates snow explosion particles
		void CreateSnowExplosion( const irr::core::vector3df& position, const irr::u32 duration );
		irr::scene::IParticleEmitter* CreateSnowmanDeathExplosion( irr::scene::IParticleSystemSceneNode& owningNode, const irr::u32 duration );
		*/
		// creates a falling snow particle emmiter and sets it for the owningNode
		// returns the emitter which has been attached to the owning node
		irr::scene::IParticleEmitter* CreateFallingSnowEmitter( irr::scene::IParticleSystemSceneNode& owningNode );
	private:

		irr::scene::ISceneManager& smgr; // scene manager from the engine
		irr::video::ITexture* SnowExplosionTexture;  // texture used for the snow explosion effect
		irr::video::ITexture* DynamiteExplosionTexture; // texture used for dynamite explosion effect
		irr::video::ITexture* ParticleWhiteTexture; // texture used for dynamite explosion effect
};

#endif //ParticleManager_h
