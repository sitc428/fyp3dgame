#ifndef __FONT_MANAGER_HPP__
#define __FONT_MANAGER_HPP__

#include <irrlicht/irrlicht.h>

#include <string>
#include <map>

namespace irr
{
	namespace gui
	{
		class CGUITTFace;
		class CGUITTFont;
	}
}

class FontManager
{
public:
	FontManager(irr::video::IVideoDriver*);
	~FontManager();

	irr::gui::CGUITTFont* getFont(std::string, int = 24);

private:

	irr::gui::CGUITTFont* createNewFont(std::string, int);

	std::map< std::string, irr::gui::CGUITTFace* > _faces; // face cache ( ttf files )
	std::map< std::pair<std::string, int>, irr::gui::CGUITTFont* > _fonts; // the font

	irr::video::IVideoDriver* driver;
};

#endif // __FONT_MANAGER_HPP__
