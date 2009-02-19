#include "ConcurrentQueue.hpp"

template<typename Data>
void ConcurrentQueue<Data>::push(Data const& data)
{
	boost::mutex::scoped_lock _lock(_mutex);
	_queue.push(data);
	_lock.unlock();
	_conditionVariable.notify_one();
}

template<typename Data>
bool ConcurrentQueue<Data>::empty() const
{
	boost::mutex::scoped_lock _lock(_mutex);
	return _queue.empty();
}

template<typename Data>
bool ConcurrentQueue<Data>::try_pop(Data& popped_value)
{
	boost::mutex::scoped_lock _lock(_mutex);
	if(_queue.empty())
	{
		return false;
	}

	popped_value=_queue.front();
	_queue.pop();
	return true;
}

template<typename Data>
void ConcurrentQueue<Data>::wait_and_pop(Data& popped_value)
{
	boost::mutex::scoped_lock _lock(_mutex);
	while(_queue.empty())
	{
		_conditionVariable.wait(_lock);
	}

	popped_value=_queue.front();
	_queue.pop();
}
