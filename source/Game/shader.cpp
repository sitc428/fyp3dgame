/*
 *  shader.cpp
 *  FYP
 *
 *  Created by Mr.JJ on 09Âπ???0??
 *  Copyright 2009 HKUST. All rights reserved.
 *
 */

#include "Shader.hpp" 

// Shader material definitions 

s32 SHADER_MATERIAL_BASE = video::EMT_SOLID; 
s32 SHADER_MATERIAL_STANDARD = video::EMT_SOLID; 
s32 SHADER_MATERIAL_ANOTHER_EXAMPLE = video::EMT_SOLID; 

Shader::Shader(IrrlichtDevice *device, const c8* vert_path,  const c8* frag_path, int Num, video::E_MATERIAL_TYPE type, c8* nodetype) { 

	NumOfTexture  = Num;
	nodeType = nodetype;
	driver = device->getVideoDriver(); 
    currentMaterial = NULL; 
    
    // Initialise shaders 
    
	shadersAvailable = 
	driver->queryFeature(video::EVDF_ARB_FRAGMENT_PROGRAM_1) 
	&& driver->queryFeature(video::EVDF_ARB_VERTEX_PROGRAM_1); 
    
	if (shadersAvailable) 
	{ 
        video::IGPUProgrammingServices *gpu = driver->getGPUProgrammingServices(); 
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
    
    baseMaterialRenderer = driver->getMaterialRenderer(SHADER_MATERIAL_BASE);
} 



bool Shader::areAvailable()
{ 
    return shadersAvailable;
} 

void Shader::OnSetConstants(video::IMaterialRendererServices *services, s32 userData) 
{ 
	//std::cout<<"here/n";
	//video::ITexture* myTexture2 = driver->getTexture("../../media/shade_line.jpg");
//	int tex0 = 0; 
//	services->setPixelShaderConstant("myTexture0", (f32 *)(&tex0), 1); 
//	int tex1 = 1; 
//	services->setPixelShaderConstant("myTexture1", (f32 *)(&tex1), 1);
	int tex[5] = {0,1,2,3,4};
//	c8* num[5] = {"0","1", "2", "3", "4"};
	for(int i = 0;i<NumOfTexture;i++){
		if(i==0)
			services->setPixelShaderConstant("myTexture0", (f32 *)(&(tex[i])), 1);
		else if(i == 1)
			services->setPixelShaderConstant("myTexture1", (f32 *)(&(tex[i])), 1);
		else if(i == 2)
			services->setPixelShaderConstant("myTexture2", (f32 *)(&(tex[i])), 1);
		else if(i == 3)
			services->setPixelShaderConstant("myTexture3", (f32 *)(&(tex[i])), 1);
		else if(i == 4)
			services->setPixelShaderConstant("myTexture4", (f32 *)(&(tex[i])), 1);
	}
	irr::core::vector3df pos = irr::core::vector3df(0.0f,9.0f,-7.0f);
	
	services->setVertexShaderConstant("Lightpos", reinterpret_cast<f32*>(&pos), 3); 

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



void Shader::OnSetMaterial(video::SMaterial &material, const video::SMaterial &lastMaterial, 
						   bool resetAllRenderstates, video::IMaterialRendererServices *services) 
{ 
    // save current material for use by shader 
    currentMaterial = &material; 
    baseMaterialRenderer->OnSetMaterial(material, lastMaterial, resetAllRenderstates, services); 
} 

bool Shader::OnRender(video::IMaterialRendererServices *services, video::E_VERTEX_TYPE vtxtype) 
{ 
    return baseMaterialRenderer->OnRender(services, vtxtype); 
} 

void Shader::OnUnsetMaterial() 
{ 
    baseMaterialRenderer->OnUnsetMaterial(); 
} 

bool Shader::isTransparent() 
{ 
    return baseMaterialRenderer->isTransparent(); 
} 

s32 Shader::getRenderCapability() 
{ 
    return baseMaterialRenderer->getRenderCapability(); 
} 

