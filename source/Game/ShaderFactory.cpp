#include "GameEngine.hpp"
#include "Shader.hpp"
#include "ShaderFactory.hpp"

ShaderFactory::ShaderFactory( GameEngine& gameEngine)
	: GEngine(gameEngine)
{
	irr::video::IVideoDriver& driver = GEngine.GetDriver();

	shaderAvailable =
		driver.queryFeature(irr::video::EVDF_ARB_FRAGMENT_PROGRAM_1)
		&& driver.queryFeature(irr::video::EVDF_ARB_VERTEX_PROGRAM_1);
	
	if( shaderAvailable )
		GPU = driver.getGPUProgrammingServices();
}

Shader* ShaderFactory::createShader(irr::core::stringc vsFile, irr::core::stringc psFile, irr::u32 textureCount, irr::video::E_MATERIAL_TYPE type)
{
	if( !shaderAvailable )
		return NULL;
	
	Shader* shader = shaderPool[vsFile+psFile];

	if( shader )
		return shader;

	shader = new Shader( textureCount );

	shader->SetShaderMaterial( GPU->addHighLevelShaderMaterialFromFiles(
		vsFile.c_str(), "main", irr::video::EVST_VS_1_1,
		psFile.c_str(), "main", irr::video::EPST_PS_1_1,
		shader, type, 0)
	);

	irr::video::IVideoDriver& driver = GEngine.GetDriver();

	shader->SetBaseMaterialRender( driver.getMaterialRenderer( shader->GetShaderMaterial() ) );

	shaderPool[vsFile+psFile] = shader;

	return shader;
}

ShaderFactory::~ShaderFactory()
{
	for(std::map< irr::core::stringc, Shader* >::iterator i = shaderPool.begin();
		i != shaderPool.end();
		++i)
	{
		delete i->second;
	}

	shaderPool.clear();
}
