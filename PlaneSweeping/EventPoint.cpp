#include "stdafx.h"
#include "EventPoint.h"

EventPoint::~EventPoint()
{
}

bool EventPoint::operator==(const EventPoint & rhs) const
{
	return point.x == rhs.point.x && point.y == rhs.point.y;
}

bool EventPoint::operator<(const EventPoint & rhs) const
{
	return point.x < rhs.point.x;
}

bool EventPoint::operator>(const EventPoint & rhs) const
{
	return rhs < *this;
}

bool EventPoint::operator<=(const EventPoint & rhs) const
{
	return !(rhs < *this);
}

bool EventPoint::operator>=(const EventPoint & rhs) const
{
	return !(*this < rhs);
}
