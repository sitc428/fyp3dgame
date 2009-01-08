#include <irrlicht/irrlicht.h>
#include "ProgressCircle.hpp"

#include <iostream>

ProgressCircle::ProgressCircle(
	irr::scene::ISceneNode *parent,
	irr::scene::ISceneManager *smgr,
	irr::s32 id,
	irr::scene::ISceneCollisionManager* coll,
	irr::s32 width,
	irr::s32 height,
	const irr::core::vector3df & posistion,
	irr::video::SColor activeColor,
	irr::video::SColor inactiveColor,
	irr::video::SColor borderColor
) : irr::scene::ISceneNode(parent, smgr, id, posistion),
	_box(
		irr::core::vector3d<irr::f32>(-width / 2.0, -height / 2.0, -1.0),
		irr::core::vector3d<irr::f32>(width / 2.0, height / 2.0, 1.0)
	),
	_coll(coll),
	_activeColor(activeColor),
	_inactiveColor(inactiveColor),
	_borderColor(borderColor),
	_dimension(width, height),
	_drawBorder(true),
	_isVisible(true),
	_percentage(100)
{
	setAutomaticCulling(irr::scene::E_CULLING_TYPE::EAC_OFF);
}

ProgressCircle::~ProgressCircle()
{
}

void ProgressCircle::OnRegisterSceneNode()
{
	if (_isVisible)
		SceneManager->registerNodeForRendering(this, irr::scene::ESNRP_SOLID);

	irr::scene::ISceneNode::OnRegisterSceneNode();
}

void ProgressCircle::render()
{
	if(!_coll)
		return;

	if(!_isVisible)
		return;

	irr::video::IVideoDriver* driver = SceneManager->getVideoDriver();
	irr::scene::ICameraSceneNode* camera = SceneManager->getActiveCamera();

	if (!camera || !driver)
		return;

	irr::core::position2d<irr::s32> pos = _coll->getScreenCoordinatesFrom3DPosition(getAbsolutePosition(), SceneManager->getActiveCamera());

	irr::s32 halfWidth = _dimension.Width / 2;
	irr::core::rect<irr::s32> absoluteRect(pos, _dimension);
	absoluteRect.UpperLeftCorner.X -= halfWidth;
	absoluteRect.LowerRightCorner.X -= halfWidth;

	irr::core::rect<irr::s32> barRect = absoluteRect;

	if( _drawBorder )
	{
		driver->draw2DRectangle(_borderColor, absoluteRect, &absoluteRect);
		barRect.UpperLeftCorner.X += 1;
		barRect.UpperLeftCorner.Y += 1;
		barRect.LowerRightCorner.X -= 1;
		barRect.LowerRightCorner.Y -= 1;
	}
	
	// draw inactive part
	driver->draw2DRectangle(_inactiveColor, barRect, &barRect );

	/*MaxNum = (BarRect.LowerRightCorner.X - BarRect.UpperLeftCorner.X)- 1;
	s32 PercentNum = (s32)((m_s32Percent * MaxNum)/ 100);*/

	// draw progress part 
	//core::rect<s32> LoadRect = BarRect;
	barRect.LowerRightCorner.X = barRect.UpperLeftCorner.X + ((barRect.LowerRightCorner.X - barRect.UpperLeftCorner.X) * _percentage) / 100;
	//driver->draw2DRectangle(_activeColor, barRect, &barRect);

	/*// draw empty part
	LoadRect.UpperLeftCorner.X = BarRect.UpperLeftCorner.X + PercentNum;
	LoadRect.LowerRightCorner.X = BarRect.LowerRightCorner.X;
	driver->draw2DRectangle( BkgColor,LoadRect,&LoadRect );*/
}

const irr::core::aabbox3d<irr::f32> & ProgressCircle::getBoundingBox() const 
{
	return _box;
}

irr::s32 ProgressCircle::getMaterialCount()
{
	return 0;
}

void ProgressCircle::setProgress(irr::s32 percentage)
{
	if(percentage < 0)
		percentage = 0;

	if(percentage > 100)
		percentage = 100;
	
	_percentage = percentage;
}
/*
//! sets the color of the progress 
void ProgressCircle::setProgressColor(video::SColor color)
{
BarColor = color;
}

//! sets the color of the progress bar background 
void ProgressCircle::setBackgroundColor(video::SColor color)
{
BkgColor = color;
}

//! sets the color of the progress bar border 
void ProgressCircle::setBorderColor(video::SColor color)
{
borderColor = color;
}*/
