#pragma once

#define POINT_INVALID cv::Point(-1, -1)

class Line
{
public:
	Line(cv::Point p1, cv::Point p2);
	Line();
	~Line();

	cv::Point p1;
	cv::Point p2;

	//cv::Vec2f dir();

	cv::Point intersect(const Line &line);
	bool hasIntersect(const Line &line);
};

