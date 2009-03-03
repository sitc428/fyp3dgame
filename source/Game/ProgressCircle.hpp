#ifndef __PROGRESS_CIRCLE_HPP__
#define __PROGRESS_CIRCLE_HPP__

#include <irrlicht/irrlicht.h>

class ProgressCircle : public irr::scene::ISceneNode 
{ 
public:
	ProgressCircle(
		irr::scene::ISceneNode* parent,
		irr::scene::ISceneManager *smgr,
		irr::s32 id,
		irr::scene::ISceneCollisionManager* coll,
		irr::s32 width = 100,
		irr::s32 height = 10,
		irr::s32 precentage = 100,
		const irr::core::vector3df & position = irr::core::vector3df(0, 0, 0),
		irr::video::SColor activeColor = irr::video::SColor(255, 200, 0, 0),
		irr::video::SColor inactiveColor = irr::video::SColor(128, 200, 64, 64),
		irr::video::SColor boarderColor = irr::video::SColor(200, 64, 64, 64)
	);

	virtual ~ProgressCircle();
	virtual void OnRegisterSceneNode();
	virtual void render();
	virtual const irr::core::aabbox3d<irr::f32> & getBoundingBox() const;
	virtual irr::s32 getMaterialCount();
	virtual void setProgress(irr::s32 percentage);

	/*virtual void setProgressColor(irr::video::SColor color);
	virtual void setBackgroundColor(video::SColor color);
	virtual void setBorderColor(video::SColor color);*/

private:
	ProgressCircle();
	ProgressCircle(const ProgressCircle & );
	
	irr::core::aabbox3d<irr::f32> _box;
	irr::video::SColor _activeColor;
	irr::video::SColor _inactiveColor;
	irr::video::SColor _borderColor;
	irr::scene::ISceneCollisionManager *_coll;
	irr::core::dimension2d<irr::s32> _dimension;
	bool _drawBorder;
	bool _isVisible;
	irr::s32 _percentage;
};

#endif //! __PROGRESS_CIRCLE_HPP__
 