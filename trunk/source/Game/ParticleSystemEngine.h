/*
 *  ParticleSystemEngine.h
 *  FYP
 *
 *  Created by Mr.JJ on 09年4月8日.
 *  Copyright 2009 HKUST. All rights reserved.
 *
 */
#ifndef __C_PARTICLE_SYSTEM_ENGINE_H__
#define __C_PARTICLE_SYSTEM_ENGINE_H__



#include <irrlicht/irrlicht.h>

static const irr::video::E_MATERIAL_TYPE matrerialType= irr::video::EMT_TRANSPARENT_VERTEX_ALPHA;




class ParticleSystemEngine{
	
	public:
	ParticleSystemEngine(irr::scene::ISceneManager*, irr::core::vector3df, irr::core::vector3df, 
						 irr::core::aabbox3df, irr::core::vector3df,
						 irr::u32, irr::u32, irr::u32, irr::u32, irr::video::ITexture*);
	~ParticleSystemEngine();
	
	irr::scene::IParticleSystemSceneNode* GetParticleSystemNode();
	irr::scene::IParticleEmitter* GetEmitter();
	
	
	private:
	
	irr::scene::IParticleSystemSceneNode* ps;
	irr::scene::IParticleEmitter* em;
	irr::scene::IParticleAffector* paf;
	
	
	irr::core::vector3df position;
	irr::core::vector3df scale;
	irr::core::aabbox3df aabbox;
	irr::core::vector3df direction;
	irr::u32 minParticlesPerSecond;
	irr::u32 maxParticlesPerSecond;
	irr::u32 lifeTimeMin;
	irr::u32 lifeTimeMax;
	irr::video::ITexture *texture;
	
	irr::scene::ISceneManager* smgr;




};

#endif