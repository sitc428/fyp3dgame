#ifndef __C_GUI_TRUETYPE_FONT_HPP__
#define __C_GUI_TRUETYPE_FONT_HPP__

#include <ft2build.h>
#include <freetype/freetype.h>
#include <irrlicht/irrlicht.h>

namespace irr
{
	namespace gui
	{

		class CGUITTFace : public IReferenceCounted
		{
			public:
				static FT_Library library;    // handle to library
				FT_Face face;               // handle to face
				bool load(const irr::c8* filename);
		};

		class CGUITTGlyph : public IReferenceCounted
		{
			public:
				CGUITTGlyph();
				virtual ~CGUITTGlyph();

				bool cached;
				void cache(irr::u32 idx_, FT_Face face_, irr::video::IVideoDriver* driver_);

				irr::u32 size;
				irr::u32 top;
				irr::u32 left;
				irr::u32 texw;
				irr::u32 texh;
				irr::u32 imgw;
				irr::u32 imgh;
				irr::video::ITexture *tex;
				irr::u32 top16;
				irr::u32 left16;
				irr::u32 texw16;
				irr::u32 texh16;
				irr::u32 imgw16;
				irr::u32 imgh16;
				irr::video::ITexture *tex16;
				irr::s32 offset;
				irr::u8 *image;
		};

		class CGUITTFont : public IGUIFont
		{
			public:

				//! constructor
				CGUITTFont(irr::video::IVideoDriver* Driver);

				//! destructor
				virtual ~CGUITTFont();

				//! loads a truetype font file
				bool attach(CGUITTFace *Face,irr::u32 size);

				//! draws an text and clips it to the specified rectangle if wanted
				virtual void draw(const wchar_t* text, const core::rect<irr::s32>& position, irr::video::SColor color, bool hcenter=false, bool vcenter=false, const core::rect<irr::s32>* clip=0);

				//! returns the dimension of a text
				virtual irr::core::dimension2d<irr::s32> getDimension(const wchar_t* text) const;

				//! Calculates the index of the character in the text which is on a specific position.
				virtual irr::s32 getCharacterFromPos(const wchar_t* text, irr::s32 pixel_x) const;

				virtual void setKerningWidth (irr::s32 kerning);
				virtual void setKerningHeight (irr::s32 kerning);

				virtual irr::s32 getKerningWidth(const wchar_t* thisLetter=0, const wchar_t* previousLetter=0) const;
				virtual irr::s32 getKerningHeight() const;

				bool AntiAlias;
				bool TransParency;

			protected:
				void clearGlyphs();

			private:
				irr::s32 getWidthFromCharacter(wchar_t c) const;
				irr::u32 getGlyphByChar(wchar_t c) const;
				irr::video::IVideoDriver* Driver;
				irr::core::array< CGUITTGlyph* > Glyphs;
				CGUITTFace *tt_face;
		};

	} // end namespace gui
} // end namespace irr

#endif //__C_GUI_TRUETYPE_FONT_HPP__

