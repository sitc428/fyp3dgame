#ifndef __SHADER_FACTORY_HPP__
#define __SHADER_FACTORY_HPP__

#include <irrlicht/irrlicht.h>

#include <map>
	
class GameEngine;
class Shader;

class ShaderFactory
{
public:
	ShaderFactory( GameEngine& );
	~ShaderFactory();

	bool ShaderAvailable() const { return shaderAvailable; }

	Shader* createShader( irr::core::stringc, irr::core::stringc, irr::u32, irr::video::E_MATERIAL_TYPE);

private:
	bool shaderAvailable;
	irr::video::IGPUProgrammingServices* GPU;

	std::map< irr::core::stringc, Shader* > shaderPool;

	GameEngine& GEngine;
};

#endif // __SHADER_FACTORY_HPP__
