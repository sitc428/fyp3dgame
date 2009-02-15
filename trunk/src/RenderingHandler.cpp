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
		_goc->drawText(fpsString, irr::core::rect<irr::s32>(0, 0, 200, 40), _goc->getFont("font/kochi-gothic-subst.ttf", 16), irr::video::SColor(255, 255, 0, 0));
		_goc->guiEnv()->drawAll();

		if(_goc->isPaused())
		{
			_goc->videoDriver()->draw2DRectangle(irr::video::SColor(128, 64, 64, 64), irr::core::rect<irr::s32>(0, 0, 800, 600));
		}

		_goc->videoDriver()->endScene();

		if(!_goc->isPaused())
		{
			_goc->Update();
		}

		int fps = _goc->videoDriver()->getFPS();

		if(lastFPS != fps)
		{
			fpsString = L"FPS: ";
			fpsString += fps;
			fpsString += L" Tri:";
			fpsString += _goc->videoDriver()->getPrimitiveCountDrawn();
			lastFPS = fps;
		}

		(*_goc->inputEvent())();

		_goc->inputEvent()->enable();
	}
}