#ifndef __C_FLOORDECAL_SCENE_NODE_HPP__
#define __C_FLOORDECAL_SCENE_NODE_HPP__

#include <irrlicht/irrlicht.h>

namespace irr
{
	namespace scene
	{

		//! Scene node which is a billboard. A billboard is like a 3d sprite: A 2d element,
		//! which always looks to the camera. 
		class CFloorDecalSceneNode : public IBillboardSceneNode
		{
			public:

				//! constructor
				CFloorDecalSceneNode(irr::scene::ISceneNode* parent, irr::scene::ISceneManager* mgr, irr::s32 id, 
						const irr::core::vector3df& position, const irr::core::dimension2d<irr::f32>& size,
						irr::video::SColor shade_top=irr::video::SColor(0xFFFFFFFF),irr::video::SColor shade_down=irr::video::SColor(0xFFFFFFFF));

				//! pre render event
				virtual void OnRegisterSceneNode();

				//! render
				virtual void render();

				//! returns the axis aligned bounding box of this node
				virtual const irr::core::aabbox3d<irr::f32>& getBoundingBox() const;

				//! sets the size of the billboard
				virtual void setSize(const irr::core::dimension2d<irr::f32>& size);

				//! gets the size of the billboard
				virtual const irr::core::dimension2d<irr::f32>& getSize() const;

				virtual irr::video::SMaterial& getMaterial(irr::u32 i);

				//! returns amount of materials used by this scene node.
				virtual irr::u32 getMaterialCount() const;

				//! Set the color of all vertices of the billboard
				//! \param overallColor: the color to set
				virtual void setColor(const irr::video::SColor & overallColor);

				//! Set the color of the top and bottom vertices of the billboard
				//! \param topColor: the color to set the top vertices
				//! \param bottomColor: the color to set the bottom vertices
				virtual void setColor(const irr::video::SColor & topColor, const irr::video::SColor & bottomColor);

				//! Gets the color of the top and bottom vertices of the billboard
				//! \param[out] topColor: stores the color of the top vertices
				//! \param[out] bottomColor: stores the color of the bottom vertices
				virtual void getColor(irr::video::SColor& topColor, irr::video::SColor& bottomColor) const;

				//! Writes attributes of the scene node.
				virtual void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options=0) const;

				//! Reads attributes of the scene node.
				virtual void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options=0);

				//! Returns type of the scene node
				virtual ESCENE_NODE_TYPE getType() const { return ESNT_BILLBOARD; }

				//! Creates a clone of this scene node and its children.
				virtual irr::scene::ISceneNode* clone(irr::scene::ISceneNode* newParent=0, irr::scene::ISceneManager* newManager=0);

			private:

				irr::core::dimension2d<irr::f32> Size;
				irr::core::aabbox3d<irr::f32> BBox;
				irr::video::SMaterial Material;

				irr::video::S3DVertex vertices[4];
				u16 indices[6];
		};


	} // end namespace scene
} // end namespace irr

#endif

