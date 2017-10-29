#include "stdafx.h"
#include "Visualize.h"


Visualize::Visualize(int W, int H)
{
	this->W = W;
	this->H = H;

	clearPoints();
	clearHulls();
}

Visualize::Visualize(int W, int H, int waitMs) : Visualize(W, H)
{
	this->waitMs = waitMs;
}

Visualize::~Visualize()
{
}

void Visualize::clearPoints()
{
	matPoints = cv::Mat(H, W, CV_32FC3);
}

void Visualize::clearHulls()
{
	matHulls = cv::Mat(H, W, CV_32FC3);
}

void Visualize::drawPoints(std::vector<cv::Point>& points)
{
	for (size_t i = 0; i < points.size(); i++)
	{
		cv::circle(matPoints, points[i], 3, cv::Vec3f(0, 1, 1), -1);
	}
}

void Visualize::drawHull(std::vector<cv::Point>& hull, bool final)
{
	int size = hull.size();
	//cv::circle(matPoints, hull[0], 5, cv::Vec3f(0, 0, 1), 2);
	//cv::circle(matPoints, hull[1], 5, cv::Vec3f(0, 1, 1), 2);
	auto color = final ? cv::Vec3f(1, 0, 1) : cv::Vec3f(1, 1, 0);
	for (size_t i = 0; i < size; i++)
	{
		cv::line(matHulls, hull[i], hull[(i+1) % size], color);
	}
}

void Visualize::drawHulls(std::vector<std::vector<cv::Point>>& hulls)
{
	int size = hulls.size();
	for (size_t i = 0; i < size; i++)
	{
		drawHull(hulls[i]);
	}
}

void Visualize::visualize()
{
	cv::Mat mat = cv::Mat(H, W, CV_32FC3);

	cv::add(matPoints, matHulls, mat);

	//cv::circle(mat, cv::Point(10, 10), 3, cv::Vec3f(1, 1, 1), -1);

	cv::imshow("mat", mat);
	cv::waitKey(waitMs);
}
