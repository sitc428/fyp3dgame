#include "RenderingHandler.hpp"

void RenderingHandler::operator()()
{
	irr::core::stringw fpsString = L"FPS: 0";

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
		_goc->drawText(fpsString);
		_goc->guiEnv()->drawAll();
		_goc->videoDriver()->endScene();

		_goc->Update();

		int fps = _goc->videoDriver()->getFPS();

		if(lastFPS != fps)
		{
			fpsString = L"FPS: ";
			fpsString += fps;
			lastFPS = fps;
		}

		(*_goc->inputEvent())();

		_goc->inputEvent()->enable();
	}
}