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

Shader::Shader( int numOfTexture, irr::core::vector3df* camPosition )
	: baseMaterialRenderer(NULL),
	currentMaterial(NULL),
	NumOfTexture(numOfTexture),
	shaderMaterial(irr::video::EMT_SOLID), 
	camPos(camPosition)
{
	offset = 0;
	factor=0.01;

	mtimer = new boost::timer();
	/*
	if(nodeType=="field"){
			SHADER_MATERIAL_BASE = driver->addMaterialRenderer(this, "SHADER_MATERIAL_BASE");
			SHADER_MATERIAL_STANDARD =  gpu->addHighLevelShaderMaterialFromFiles(
					vert_path, "main", video::EVST_VS_1_1,
					frag_path, "main", video::EPST_PS_1_1,
					this, type, 0);


		}else{
			SHADER_MATERIAL_BASE = gpu->addHighLevelShaderMaterialFromFiles(
					vert_path, "main", video::EVST_VS_1_1,
					frag_path, "main", video::EPST_PS_1_1,
					this, type, 0);

			SHADER_MATERIAL_STANDARD = driver->addMaterialRenderer(this, "SHADER_MATERIAL_STANDARD");
		}
		SHADER_MATERIAL_ANOTHER_EXAMPLE = driver->addMaterialRenderer(this, "SHADER MATERIAL EXAMPLE");
	}
	else
	{
		printf("Warning: Shaders disabled because of missing driver/hardware support.\n");
	}
	*/
	//baseMaterialRenderer = driver->getMaterialRenderer( shaderMaterial );

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

	if(mtimer->elapsed() > 120.0)
		mtimer->restart();
	float tim = mtimer->elapsed();
	services->setVertexShaderConstant("time_0_X", reinterpret_cast<irr::f32*>(&tim), 3);
	
	if(camPos){
		services->setVertexShaderConstant("view_inverse_matrix", reinterpret_cast<irr::f32*>(camPos), 3);
	}
	/*
	   if (!currentMaterial)
	   {
	   printf("Shader::OnSetConstants: Error: no currentMaterial.\n");
	   return;
	   }

	// Now send different parameters to shader based on state of currentMaterial.

	if (currentMaterial->MaterialType == SHADER_MATERIAL_STANDARD)
	{
	// Use Texture?
	//  f32 useTexture0 = currentMaterial->Textures[0] ? 1.0 : 0.0;
	//    services->setPixelShaderConstant("UseTexture0", &useTexture0, 1);

	// Set Texture 0
	video::ITexture* myTexture2 = driver->getTexture("../../media/shade_line.jpg");
	int tex0 = 0;
	services->setPixelShaderConstant("myTexture", (f32 *)(&tex0), 1);
	int tex1 = 1;
	services->setPixelShaderConstant("myTexture2", (f32 *)(&tex1), 1);

	/*   // Hemisphere Lighting

	f32 sunPos[3] = {0.0,100.0,0.0};
	f32 skyCol[3] = {0xee/256.0, 0xee/256.0, 0x88/256.0};
	f32 groundCol[3] = {0x55/256.0, 0x55/256.0, 0x77/256.0};
	services->setVertexShaderConstant("SunPos", sunPos, 3);
	services->setVertexShaderConstant("SkyCol", skyCol, 3);
	services->setVertexShaderConstant("GroundCol", groundCol, 3);


	}
	else if (currentMaterial->MaterialType == SHADER_MATERIAL_ANOTHER_EXAMPLE)
	{
	printf("Shader: Example material used!! :O\n");
	}
	else
	{
	printf("Shader::OnSetConstants: Error: Undefined material!\n");
	}
	*/

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

