#include "RenderingHandler.hpp"

void RenderingHandler::operator()()
{
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
		_goc->drawText();
		_goc->guiEnv()->drawAll();
		_goc->videoDriver()->endScene();

		(*_goc->inputEvent())();

		_goc->inputEvent()->enable();
	}
}