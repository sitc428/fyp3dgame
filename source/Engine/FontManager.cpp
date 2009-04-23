#include <algorithm>
#include <fstream>

#include "CGUITTFont.hpp"
#include "FontManager.hpp"
#include "Tokenizer.hpp"

FontManager::FontManager(irr::video::IVideoDriver* videoDriver)
	: driver(videoDriver)
{
	std::ifstream fontConfig("font.rxw");

	while(!fontConfig.eof())
	{
		std::string fontData = "";
		fontConfig >> fontData;

		Tokenizer tokenizer(fontData, ",");

		std::string fontName = tokenizer.getNextToken();
		std::string fontPath = tokenizer.getNextToken();

		_faces.insert( std::make_pair(fontName, new irr::gui::CGUITTFace()) );
		_faces[fontName]->load(fontPath.c_str());

		createNewFont(fontName, 8);
		createNewFont(fontName, 16);
		createNewFont(fontName, 24);
	}

	fontConfig.close();
}

FontManager::~FontManager()
{
	for(
		std::map< std::pair<std::string, int>, irr::gui::CGUITTFont* >::iterator i = _fonts.begin();
		i != _fonts.end();
		++i
	)
	{
		delete (*i).second;
	}

	_fonts.clear();

	for(
		std::map< std::string, irr::gui::CGUITTFace* >::iterator i = _faces.begin();
		i != _faces.end();
		++i
	)
	{
		delete (*i).second;
	}

	_faces.clear();
}

irr::gui::CGUITTFont* FontManager::getFont(std::string fontName, int fontSize)
{
	if(_fonts[std::make_pair(fontName, fontSize)])
	{
		return _fonts[std::make_pair(fontName, fontSize)];
	}
	else
	{
		return createNewFont(fontName, fontSize);
	}
}

irr::gui::CGUITTFont* FontManager::createNewFont(std::string fontName, int fontSize)
{
	if( !_faces[fontName] )
		return NULL;

	irr::gui::CGUITTFont* font = new irr::gui::CGUITTFont( driver );

	if( !font )
		return NULL;

	if( font->attach( _faces[fontName], fontSize ) )
	{
		font->TransParency = font->AntiAlias = true;
		_fonts.insert( std::make_pair( std::make_pair(fontName, fontSize), font ) );
	}
	else
		return NULL;

	return font;
}
