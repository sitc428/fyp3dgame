/*
 *  ParticleSystemEngine.cpp
 *  FYP
 *
 *  Created by Mr.JJ on 09å¹?????
 *  Copyright 2009 HKUST. All rights reserved.
 *
 */

#include "ParticleManager.hpp"

ParticleManager::ParticleManager(irr::scene::ISceneManager* _smgr, irr::core::vector3df _position, irr::core::vector3df _scale, irr::core::aabbox3df _aabbox)
	: ps(NULL),
	smgr(_smgr),
	position(_position),
	scale(_scale),
	aabbox(_aabbox)
{
	ps = smgr->addParticleSystemSceneNode(false);
	ps->setPosition(position);
	ps->setScale(scale);
	ps->setParticleSize(irr::core::dimension2d<irr::f32>(20.0f, 20.0f));
}

ParticleManager::~ParticleManager()
{
}

void ParticleManager::CreateBoxEmitter(
	irr::core::vector3df _direction,
	irr::u32 _minParticlesPerSecond,
	irr::u32 _maxParticlesPerSecond,
	irr::u32 _lifeTimeMin,
	irr::u32 _lifeTimeMax,
	irr::video::ITexture* _texture)
{
	direction = _direction;
	minParticlesPerSecond = _minParticlesPerSecond;
	maxParticlesPerSecond = _maxParticlesPerSecond;
	lifeTimeMin = _lifeTimeMin;
	lifeTimeMax = _lifeTimeMax;
	texture = _texture;

	em = ps->createBoxEmitter(
		irr::core::aabbox3d<irr::f32>(-7,0,-7,7,1,7),
		direction,
		minParticlesPerSecond,maxParticlesPerSecond,
		irr::video::SColor(0,255,255,255), irr::video::SColor(0,255,255,255),
		lifeTimeMin,lifeTimeMax
	);
	
	ps->setEmitter(em);
	em->drop();
	
	paf = ps->createFadeOutParticleAffector();
	
	ps->addAffector(paf);
	paf->drop();
	
	ps->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	ps->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
	ps->setMaterialTexture(0,texture);
	ps->setMaterialType(irr::video::EMT_TRANSPARENT_VERTEX_ALPHA);
}

void ParticleManager::CreateMeshEmitter(
	irr::scene::IMesh * mesh,
	irr::core::vector3df _direction,
	irr::u32 _minParticlesPerSecond,
	irr::u32 _maxParticlesPerSecond,
	irr::u32 _lifeTimeMin,
	irr::u32 _lifeTimeMax,
	irr::video::ITexture* _texture)
{
	direction = _direction;
	minParticlesPerSecond = _minParticlesPerSecond;
	maxParticlesPerSecond = _maxParticlesPerSecond;
	lifeTimeMin = _lifeTimeMin;
	lifeTimeMax = _lifeTimeMax;
	texture = _texture;

	em = ps->createMeshEmitter(mesh,true,
		direction,100.0f,-1,false,minParticlesPerSecond ,maxParticlesPerSecond,
		irr::video::SColor(0,255,255,255), irr::video::SColor(0,255,255,255),
		lifeTimeMin,lifeTimeMax
	);
	
	ps->setEmitter(em);
	em->drop();
	
	paf = ps->createFadeOutParticleAffector();
	
	ps->addAffector(paf);
	paf->drop();
	
	ps->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	ps->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
	ps->setMaterialTexture(0,texture);
	ps->setMaterialType(irr::video::EMT_TRANSPARENT_VERTEX_ALPHA);
}
