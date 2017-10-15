#pragma once

template<class T>
class PriorityQueue
{
public:
	std::set<T> queue;

	T min()
	{
		T t = *queue.begin();
		queue.erase(queue.begin());

		return t;
	}
	void insert(T ep)
	{
		queue.insert(ep);
	}
	bool member(T ep)
	{
		return queue.find(ep) != queue.end();
	}
	bool isEmpty() {
		return queue.empty();
	}
};

