#include "RenderingHandler.hpp"

void RenderingHandler::operator()()
{
	while(_goc->deviceRunning())
	{
		boost::mutex::scoped_lock lock(gl_mutex);
		
		_goc->InputEvent()->disable();

		_goc->VideoDriver()->beginScene(true, true, irr::video::SColor(255,128,128,128));
		_goc->SceneManager()->drawAll();
		_goc->VideoDriver()->endScene();
		
		/*
		if(_goc->InputEvent()->keyPressed(irr::KEY_KEY_W))
		{
			std::cout<<"W"<<std::endl;

			irr::core::vector3df v1 = _player->getPosition();
			v1.Z += .05f;
			node->setPosition(v1);
			cam->setTarget(v1);
		}
		
		if(_goc->InputEvent()->mouseDown(InputEventHandler::LEFT))
		{
			std::cout<<"Mouse Down!"<<std::endl;
		}
		*/

		_goc->InputEvent()->enable();
	}
}