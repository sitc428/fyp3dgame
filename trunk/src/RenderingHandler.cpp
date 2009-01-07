#include "RenderingHandler.hpp"

void RenderingHandler::operator()()
{
	boost::thread handleInput(*(_goc->inputEvent()));
	while(_goc->deviceRunning())
	{
		if(!_goc->isActive())
		{
			_goc->idle();
			continue;
		}

		boost::mutex::scoped_lock lock(gl_mutex);
		
		_goc->inputEvent()->disable();

		_goc->videoDriver()->beginScene(true, true, irr::video::SColor(255,128,128,128));
		_goc->sceneManager()->drawAll();
		_goc->videoDriver()->endScene();

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

		_goc->inputEvent()->enable();
	}
}