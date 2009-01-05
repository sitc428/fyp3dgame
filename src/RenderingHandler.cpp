#include "RenderingHandler.hpp"

void RenderingHandler::operator()()
{
	while(_goc->deviceRunning())
	{
		boost::mutex::scoped_lock lock(gl_mutex);

		_goc->VideoDriver()->beginScene(true, true, irr::video::SColor(255,128,128,128));
		_goc->SceneManager()->drawAll();
		_goc->VideoDriver()->endScene();
	}
}