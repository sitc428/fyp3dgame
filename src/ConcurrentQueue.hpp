#ifndef __CONCURRENT_QUEUE_HPP__
#define __CONCURRENT_QUEUE_HPP__

#include <boost/thread.hpp>
#include <queue>

template<typename Data> class ConcurrentQueue
{
private:
	std::queue<Data> _queue;
	mutable boost::mutex _mutex;
	boost::condition_variable _conditionVariable;
public:
	void push(Data const& data);
	bool empty() const;
	bool try_pop(Data& popped_value);
	void wait_and_pop(Data& popped_value);
};

#endif //! __CONCURRENT_QUEUE_HPP__
