#include "stdafx.h"
#include "Line.h"


Line::Line(cv::Point p1, cv::Point p2)
{
	this->p1 = cv::Point(p1);
	this->p2 = cv::Point(p2);
}

Line::Line()
{
}

Line::~Line()
{
}

cv::Point Line::intersect(const Line &line) {
	float x1 = p1.x, x2 = p2.x, x3 = line.p1.x, x4 = line.p2.x;
	float y1 = p1.y, y2 = p2.y, y3 = line.p1.y, y4 = line.p2.y;

	float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	if (d == 0) return POINT_INVALID;

	// Get the x and y
	float pre = (x1 * y2 - y1 * x2), post = (x3 * y4 - y3 * x4);
	float x = (pre * (x3 - x4) - (x1 - x2) * post) / d;
	float y = (pre * (y3 - y4) - (y1 - y2) * post) / d;

	// Check if the x and y coordinates are within both lines
	if (x < std::min(x1, x2) || x > std::max(x1, x2) ||
		x < std::min(x3, x4) || x > std::max(x3, x4)) {
		return POINT_INVALID;
	}
	if (y < std::min(y1, y2) || y > std::max(y1, y2) ||
		y < std::min(y3, y4) || y > std::max(y3, y4)) {
		return POINT_INVALID;
	}

	return cv::Point(static_cast<int>(std::floor(x)), static_cast<int>(std::floor(y)));
}

bool Line::hasIntersect(const Line &line) {
	return this->intersect(line) != POINT_INVALID;
}

//cv::Vec2f Line::dir() {
//	return cv::Vec2f(
//		p2.x - p1.x,
//		p2.y - p1.y
//	);
//}