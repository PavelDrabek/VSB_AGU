#include "stdafx.h"
#include "Dictionary.h"


Dictionary::Dictionary()
{
}


Dictionary::~Dictionary()
{
}

void Dictionary::insert(Segment * s)
{
	queue.insert(s);
}

void Dictionary::remove(Segment * s)
{
	auto f = queue.find(s);
	if (f != queue.end()) {
		queue.erase(f);
	}
}

Segment * Dictionary::above(Segment * s)
{
	auto f = queue.upper_bound(s);

	if (f != queue.end()) {
		return *f;
	}
	return nullptr;
}

Segment * Dictionary::below(Segment * s)
{
	auto f = queue.lower_bound(s);
	auto b = queue.begin();


	if (f != b) {
		return *(--f);
	}
	return nullptr;
}

void Dictionary::swap(Segment * s1, Segment * s2, cv::Point p)
{
 	this->remove(s1);
	this->remove(s2);

	s1->point = cv::Point(p.x, p.y + 1);
	s2->point = cv::Point(p.x, p.y);

	this->insert(s1);
	this->insert(s2);
}
