// Copyright (C) 2002-2008 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "FloorDecalSceneNode.h"
#include <irrlicht/irrlicht.h>

namespace irr
{
	namespace scene
	{

		//! constructor
		CFloorDecalSceneNode::CFloorDecalSceneNode(irr::scene::ISceneNode* parent, irr::scene::ISceneManager* mgr, irr::s32 id,
				const irr::core::vector3df& position, const irr::core::dimension2d<irr::f32>& size,
				irr::video::SColor shade_top, irr::video::SColor shade_down)
			: IBillboardSceneNode(parent, mgr, id, position)
		{
#ifdef _DEBUG
			setDebugName("CFloorDecalSceneNode");
#endif

			setSize(size);

			indices[0] = 0;
			indices[1] = 2;
			indices[2] = 1;
			indices[3] = 0;
			indices[4] = 3;
			indices[5] = 2;

			vertices[0].TCoords.set(1.0f, 1.0f);
			vertices[0].Color = shade_down;

			vertices[1].TCoords.set(1.0f, 0.0f);
			vertices[1].Color = shade_top;

			vertices[2].TCoords.set(0.0f, 0.0f);
			vertices[2].Color = shade_top;

			vertices[3].TCoords.set(0.0f, 1.0f);
			vertices[3].Color = shade_down;
		}


		//! pre render event
		void CFloorDecalSceneNode::OnRegisterSceneNode()
		{
			if (IsVisible)
			{
				SceneManager->registerNodeForRendering(this);
				irr::scene::ISceneNode::OnRegisterSceneNode();
			}
		}


		//! render
		void CFloorDecalSceneNode::render()
		{
			irr::video::IVideoDriver* driver = SceneManager->getVideoDriver();
			if( !driver )
			{
				return;
			}
			// this scene node always faces up
			irr::core::vector3df normal = irr::core::vector3df(0.f,1.f,0.f);
			irr::core::vector3df pos = getAbsolutePosition();

			// find node's absolute Y rotation
			irr::core::vector3df absRotation = RelativeRotation;
			irr::scene::ISceneNode* parent = Parent;
			while( parent )
			{
				absRotation += parent->getRotation();
				parent = parent->getParent();
			}

			// rotate aim vector
			irr::core::vector3df forwardVector = irr::core::vector3df( 1.f, 0.f, 0.f );
			forwardVector.rotateXZBy( -absRotation.Y, irr::core::vector3df( 0, 0, 0 ) );
			irr::core::vector3df rightVector = forwardVector.crossProduct(irr::core::vector3df(0,1,0));

			forwardVector *= 0.5f * Size.Height;
			rightVector *= 0.5f * Size.Width;

			for (irr::s32 i=0; i<4; ++i)
				vertices[i].Normal = normal;

			vertices[0].Pos = pos + forwardVector + rightVector;
			vertices[1].Pos = pos - forwardVector + rightVector;
			vertices[2].Pos = pos - forwardVector - rightVector;
			vertices[3].Pos = pos + forwardVector - rightVector;

			// draw
			if ( DebugDataVisible & scene::EDS_BBOX )
			{
				driver->setTransform(irr::video::ETS_WORLD, AbsoluteTransformation);
				irr::video::SMaterial m;
				m.Lighting = false;
				driver->setMaterial(m);
				driver->draw3DBox(BBox, irr::video::SColor(0,208,195,152));
			}

			core::matrix4 mat;
			driver->setTransform(irr::video::ETS_WORLD, mat);

			driver->setMaterial(Material);

			driver->drawIndexedTriangleList(vertices, 4, indices, 2);
		}


		//! returns the axis aligned bounding box of this node
		const irr::core::aabbox3d<irr::f32>& CFloorDecalSceneNode::getBoundingBox() const
		{
			return BBox;
		}


		//! sets the size of the billboard
		void CFloorDecalSceneNode::setSize(const irr::core::dimension2d<irr::f32>& size)
		{
			Size = size;

			if (Size.Width == 0.0f)
				Size.Width = 1.0f;

			if (Size.Height == 0.0f )
				Size.Height = 1.0f;

			irr::f32 avg = (size.Width + size.Height)/6;
			BBox.MinEdge.set(-avg,-avg,-avg);
			BBox.MaxEdge.set(avg,avg,avg);
		}


		irr::video::SMaterial& CFloorDecalSceneNode::getMaterial(irr::u32 i)
		{
			return Material;
		}


		//! returns amount of materials used by this scene node.
		irr::u32 CFloorDecalSceneNode::getMaterialCount() const
		{
			return 1;
		}


		//! gets the size of the billboard
		const irr::core::dimension2d<irr::f32>& CFloorDecalSceneNode::getSize() const
		{
			return Size;
		}


		//! Writes attributes of the scene node.
		void CFloorDecalSceneNode::serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options) const
		{
			IBillboardSceneNode::serializeAttributes(out, options);

			out->addFloat("Width", Size.Width);
			out->addFloat("Height", Size.Height);
			out->addColor ("Shade_Top", vertices[1].Color );
			out->addColor ("Shade_Down", vertices[0].Color );
		}


		//! Reads attributes of the scene node.
		void CFloorDecalSceneNode::deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options)
		{
			IBillboardSceneNode::deserializeAttributes(in, options);

			Size.Width = in->getAttributeAsFloat("Width");
			Size.Height = in->getAttributeAsFloat("Height");
			vertices[1].Color = in->getAttributeAsColor ( "Shade_Top" );
			vertices[0].Color = in->getAttributeAsColor ( "Shade_Down" );

			setSize(Size);
		}


		//! Set the color of all vertices of the billboard
		//! \param overallColor: the color to set
		void CFloorDecalSceneNode::setColor(const irr::video::SColor & overallColor)
		{
			for(irr::u32 vertex = 0; vertex < 4; ++vertex)
				vertices[vertex].Color = overallColor;
		}


		//! Set the color of the top and bottom vertices of the billboard
		//! \param topColor: the color to set the top vertices
		//! \param bottomColor: the color to set the bottom vertices
		void CFloorDecalSceneNode::setColor(const irr::video::SColor & topColor, const irr::video::SColor & bottomColor)
		{
			vertices[0].Color = bottomColor;
			vertices[1].Color = topColor;
			vertices[2].Color = topColor;
			vertices[3].Color = bottomColor;
		}


		//! Gets the color of the top and bottom vertices of the billboard
		//! \param[out] topColor: stores the color of the top vertices
		//! \param[out] bottomColor: stores the color of the bottom vertices
		void CFloorDecalSceneNode::getColor(irr::video::SColor & topColor, irr::video::SColor & bottomColor) const
		{
			bottomColor = vertices[0].Color;
			topColor = vertices[1].Color;
		}


		//! Creates a clone of this scene node and its children.
		irr::scene::ISceneNode* CFloorDecalSceneNode::clone(irr::scene::ISceneNode* newParent, irr::scene::ISceneManager* newManager)
		{
			if (!newParent)
				newParent = Parent;
			if (!newManager)
				newManager = SceneManager;

			CFloorDecalSceneNode* nb = new CFloorDecalSceneNode(newParent, 
					newManager, ID, RelativeTranslation, Size);

			nb->cloneMembers(this, newManager);
			nb->Material = Material;

			nb->drop();
			return nb;
		}


	} // end namespace scene
} // end namespace irr

