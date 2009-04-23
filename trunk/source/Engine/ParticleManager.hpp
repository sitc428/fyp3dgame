/*
 *  ParticleManager.hpp
 *  FYP
 *
 *  Created by Mr.JJ on 09å¹?????
 *  Copyright 2009 HKUST. All rights reserved.
 *
 */
#ifndef __PARTICLE_MANAGER_HPP__
#define __PARTICLE_MANAGER_HPP__

#include <irrlicht/irrlicht.h>

static const irr::video::E_MATERIAL_TYPE matrerialType= irr::video::EMT_TRANSPARENT_VERTEX_ALPHA;

class ParticleManager
{
public:
	ParticleManager(irr::scene::ISceneManager*, irr::core::vector3df, irr::core::vector3df, irr::core::aabbox3df);
	~ParticleManager();

	void CreateBoxEmitter(irr::core::vector3df, irr::u32, irr::u32, irr::u32, irr::u32, irr::video::ITexture*);
	void CreateMeshEmitter(irr::scene::IMesh * , irr::core::vector3df, irr::u32, irr::u32, irr::u32, irr::u32, irr::video::ITexture*);
	void CreateCylinderEmitter(const irr::core::vector3df , irr::f32 , irr::core::vector3df, 
							   irr::f32, irr::core::vector3df, 
							   irr::u32 , irr::u32 , 
							   irr::u32, irr::u32, irr::video::ITexture*);
	
	void CreateSmokeEmitter(irr::core::vector3df, irr::u32, irr::u32, irr::u32, irr::u32, irr::video::ITexture*);
	
	irr::scene::IParticleSystemSceneNode* GetParticleSystemNode();
	irr::scene::IParticleEmitter* GetEmitter();
	

	void resetEmitter()
	{
		ps->setEmitter(0);
	}
	
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

#endif // __PARTICLE_MANAGER_HPP__