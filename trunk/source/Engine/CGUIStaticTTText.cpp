#include "CGUIStaticTTText.hpp"
#include "CGUITTFont.hpp"

namespace irr
{
namespace gui
{

CGUIStaticTTText::CGUIStaticTTText(core::stringw text, CGUITTFont* font, core::rect<s32> pos, video::SColor color, IGUIEnvironment* env, IGUIElement* parent, s32 id)
	//:IGUIElement(EGUIET_ELEMENT, env, parent, id, pos),
	:IGUIStaticText(env, parent, id, pos),
	_text(text),
	_font(font),
	_pos(pos),
	_color(color)
{
}

CGUIStaticTTText::~CGUIStaticTTText()
{
	_font->drop();
}

void CGUIStaticTTText::draw()
{
	_font->draw(_text.c_str(), _pos, _color);
}

}
}