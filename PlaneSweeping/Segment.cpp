#include "stdafx.h"
#include "Segment.h"


Segment::Segment(cv::Point & start, cv::Point & end, cv::Point & point)
{
	this->line = Line(start, end);
	this->point = point;
}

Segment::~Segment()
{
}

bool Segment::operator<(const Segment &rhs) const {
	return this->point.y < rhs.point.y;
}

bool Segment::operator>(const Segment &rhs) const {
	return rhs < *this;
}

bool Segment::operator<=(const Segment &rhs) const {
	return !(rhs < *this);
}

bool Segment::operator>=(const Segment &rhs) const {
	return !(*this < rhs);
}

