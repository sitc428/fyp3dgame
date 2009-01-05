#ifndef __RENDERING_HANDLER_HPP__
#define __RENDERING_HANDLER_HPP__

#include <boost/thread.hpp>
#include "GameObjectCollection.hpp"
//#include <iostream>

extern boost::mutex gl_mutex;

class RenderingHandler
{
public:

	RenderingHandler(GameObjectCollection* goc)
	{
		_goc = goc;
		lastFPS = 0;
	};

	~RenderingHandler() {};

	void operator()();

private:
	GameObjectCollection* _goc;
	int lastFPS;
};

#endif //! __RENDERING_HANDLER_HPP__