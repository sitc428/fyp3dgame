#ifndef __RENDERING_HANDLER_HPP__
#define __RENDERING_HANDLER_HPP__

#include <boost/thread.hpp>
#include "GameObjectCollection.hpp"
//#include <iostream>

class RenderingHandler
{
public:
	RenderingHandler(GameObjectCollection* goc)
	{
		_goc = goc;
		lastFPS = 0;
	};

	~RenderingHandler() {};

	void operator()()
	{
		while(_goc->deviceRunning())
		{
			boost::thread::scope_lock scope_lock(boost::mutex m);
			_goc->VideoDriver()->beginScene(true, true, irr::video::SColor(255,128,128,128));
			//_goc->SceneManager()->drawAll();
			_goc->VideoDriver()->endScene();

			/*int fps = _goc->VideoDriver()->getFPS();

			if(lastFPS != fps)
			{
				irr::core::stringw str = L"FYP - v0.1 r54 [FPS:";
				str += fps;
				str += "]";

				_goc->Device()->setWindowCaption(str.c_str());
				lastFPS = fps;
			}

			//boost::this_thread::sleep(boost::posix_time::milliseconds(1000));*/
		}
	};
private:
	GameObjectCollection* _goc;
	int lastFPS;
};

#endif //! __RENDERING_HANDLER_HPP__