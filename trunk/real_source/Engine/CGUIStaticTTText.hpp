#ifndef __C_GUI_STATIC_TRYETYPE_TEXT_HPP__
#define __C_GUI_STATIC_TRYETYPE_TEXT_HPP__

#include <irrlicht/irrlicht.h>

namespace irr
{
namespace gui
{
	class CGUITTFont;
	
	//class CGUIStaticTTText : public IGUIElement
	class CGUIStaticTTText : public IGUIStaticText
	{
		public:
			CGUIStaticTTText::CGUIStaticTTText(core::stringw text, CGUITTFont* font, core::rect<s32> pos, video::SColor color, IGUIEnvironment* env, IGUIElement* parent = 0, s32 id = -1);
			virtual ~CGUIStaticTTText();

			virtual void draw();
		private:
			CGUIStaticTTText();

			core::stringw _text;
			CGUITTFont* _font;
			core::rect<s32> _pos;
			video::SColor _color;
	};
}
}

#endif //__C_GUI_STATIC_TRYETYPE_TEXT_HPP__