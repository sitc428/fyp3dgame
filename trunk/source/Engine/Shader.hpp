/*
 *  shader.h
 *  FYP
 *
 *  Created by Mr.JJ on 09?????0??
 *  Copyright 2009 HKUST. All rights reserved.
 *
 */

#ifndef __SHADER_HPP__
#define __SHADER_HPP__

#include <irrlicht/irrlicht.h> 
#include <boost/timer.hpp>

class Shader : public irr::video::IMaterialRenderer, public irr::video::IShaderConstantSetCallBack
{ 
public: 
	Shader( int , irr::core::vector3df* = NULL);
	void OnSetConstants( irr::video::IMaterialRendererServices*, irr::s32 );
	void OnSetMaterial( irr::video::SMaterial &, const irr::video::SMaterial &, bool, irr::video::IMaterialRendererServices* );
	bool OnRender( irr::video::IMaterialRendererServices*, irr::video::E_VERTEX_TYPE );
	void OnUnsetMaterial();

	void SetShaderMaterial( irr::s32 newShaderMaterial );
	irr::s32 GetShaderMaterial();
	
	void SetBaseMaterialRender( irr::video::IMaterialRenderer* );

	bool isTransparent();
	irr::s32 getRenderCapability();

private: 
	irr::video::IMaterialRenderer* baseMaterialRenderer; 
	irr::video::SMaterial* currentMaterial; 
	irr::u32 NumOfTexture;
	irr::s32 shaderMaterial;
	irr::f32 offset;
	irr::f32 factor;
	boost::timer* mtimer;
	irr::core::vector3df* camPos;
}; 

#endif // SHADER_HPP__
