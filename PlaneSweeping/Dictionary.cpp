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
	if (f != queue.end()) {
		return *f;
	}
	return nullptr;
}

void Dictionary::swap(Segment * s1, Segment * s2)
{
	this->remove(s1);
	this->remove(s2);

	cv::Point tmp = s1->point;
	s1->point = s2->point;
	s2->point = tmp;

	//std::swap<cv::Point>(s1->point, s2->point);

	this->insert(s1);
	this->insert(s2);
}
