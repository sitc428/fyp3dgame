/*
 *  shader.h
 *  FYP
 *
 *  Created by Mr.JJ on 09年4月10日.
 *  Copyright 2009 HKUST. All rights reserved.
 *
 */

#ifndef __Shader_h 
#define __Shader_h 

#include <irrlicht/irrlicht.h> 
#include <iostream>

using namespace irr; 

// Declare new materials externally for use by scene nodes 
extern s32 SHADER_MATERIAL_BASE; 
extern s32 SHADER_MATERIAL_STANDARD; 
extern s32 SHADER_MATERIAL_ANOTHER_EXAMPLE; 

class Shader : public video::IMaterialRenderer, public video::IShaderConstantSetCallBack 
{ 
public: 
    Shader(IrrlichtDevice *); 
    
    // if shaders were successfully created 
    bool areAvailable(); 
    
    void OnSetConstants(video::IMaterialRendererServices *, s32); 
    
    void OnSetMaterial(video::SMaterial &, const video::SMaterial &, bool, video::IMaterialRendererServices *); 
    bool OnRender(video::IMaterialRendererServices *, video::E_VERTEX_TYPE); 
    void OnUnsetMaterial(); 
    bool isTransparent(); 
    s32 getRenderCapability(); 
    
private: 
    video::IVideoDriver *driver; 
    video::IMaterialRenderer *baseMaterialRenderer; 
    video::SMaterial *currentMaterial; 
    bool shadersAvailable; 
}; 

#endif