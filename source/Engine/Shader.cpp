/*
 *  shader.cpp
 *  FYP
 *
 *  Created by Mr.JJ on 09?????0??
 *  Copyright 2009 HKUST. All rights reserved.
 *
 */

#include "Shader.hpp"

// Shader material definitions

Shader::Shader( int numOfTexture )
	: baseMaterialRenderer(NULL),
	currentMaterial(NULL),
	NumOfTexture(numOfTexture),
	shaderMaterial(irr::video::EMT_SOLID)
{
	offset = 0;
	factor=0.01;
}

void Shader::OnSetConstants(irr::video::IMaterialRendererServices* services, irr::s32 userData)
{
	int tex[5] = {0, 1, 2, 3, 4};
	for(int i = 0; i < NumOfTexture; ++i)
	{
		if(i==0)
			services->setPixelShaderConstant("myTexture0", (irr::f32 *)(&(tex[i])), 1);
		else if(i == 1)
			services->setPixelShaderConstant("myTexture1", (irr::f32 *)(&(tex[i])), 1);
		else if(i == 2)
			services->setPixelShaderConstant("myTexture2", (irr::f32 *)(&(tex[i])), 1);
		else if(i == 3)
			services->setPixelShaderConstant("myTexture3", (irr::f32 *)(&(tex[i])), 1);
		else if(i == 4)
			services->setPixelShaderConstant("myTexture4", (irr::f32 *)(&(tex[i])), 1);
	}
	irr::core::vector3df pos = irr::core::vector3df(0.0f,9.0f,-7.0f);
	services->setVertexShaderConstant("Lightpos", reinterpret_cast<irr::f32*>(&pos), 3);
	if(offset>1.0) factor=-0.01;
	if(offset<=0.0) factor=0.01;
	offset+=factor;
	services->setVertexShaderConstant("offset", reinterpret_cast<irr::f32*>(&offset), 3);
}

void Shader::OnSetMaterial(irr::video::SMaterial &material, const irr::video::SMaterial &lastMaterial, bool resetAllRenderstates, irr::video::IMaterialRendererServices* services)
{
	// save current material for use by shader
	currentMaterial = &material;
	baseMaterialRenderer->OnSetMaterial( material, lastMaterial, resetAllRenderstates, services );
}

bool Shader::OnRender( irr::video::IMaterialRendererServices* services, irr::video::E_VERTEX_TYPE vtxtype )
{
	return baseMaterialRenderer->OnRender( services, vtxtype );
}

void Shader::OnUnsetMaterial()
{
	baseMaterialRenderer->OnUnsetMaterial();
}

void Shader::SetShaderMaterial( irr::s32 newShaderMaterial )
{
	shaderMaterial = newShaderMaterial;
}

irr::s32 Shader::GetShaderMaterial()
{
	return shaderMaterial;
}

void Shader::SetBaseMaterialRender( irr::video::IMaterialRenderer* newBMR)
{
	if( baseMaterialRenderer )
		baseMaterialRenderer->drop();

	baseMaterialRenderer = newBMR;
}

bool Shader::isTransparent()
{
	return baseMaterialRenderer->isTransparent();
}

irr::s32 Shader::getRenderCapability()
{
	return baseMaterialRenderer->getRenderCapability();
}

