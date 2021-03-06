// ConvexHull.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ConvexHull.h"

const int N = 300; // number of lines
const int W = 1400;
const int H = 800;

Visualize visualizer(W, H, 1);

int main(int, char**)
{
	std::vector<cv::Point> points;
	std::vector<HULL> hulls;

	//std::cout << orientation(cv::Point(3, 3), cv::Point(10, 10), cv::Point(6, 7)) << std::endl;

	for (int i = 0; i < N; i++)
	{
		cv::Point p1 = cv::Point(rand() % W, rand() % H);
		points.push_back(p1);
	}

	std::sort(points.begin(), points.end(), Point2fLessThan());

	visualizer.drawPoints(points);
	visualizer.visualize();

	HULL convexHull;
	dac(points, convexHull);

	visualizer.drawHull(convexHull, true);
	visualizer.visualize();

	cv::waitKey();

	return 0;
}

void dac(std::vector<cv::Point> points, HULL& hullOut) 
{
	HULL hull1;
	HULL hull2;

	if (points.size() <= 3) {
		if (points.size() < 3) {
			hullOut.push_back(points[0]);
			hullOut.push_back(points[1]);
		}
		else {
			hullOut.push_back(points[0]);

			if (orientation(points[0], points[1], points[2]) < 0) {
				hullOut.push_back(points[2]);
				hullOut.push_back(points[1]);
			} else {
				hullOut.push_back(points[1]);
				hullOut.push_back(points[2]);
			}
		}
		//visualizer.drawHull(hullOut);
		//visualizer.visualize();
		return;
	}

	dac(std::vector<cv::Point>(points.begin(), points.begin() + points.size() / 2), hull1);
	dac(std::vector<cv::Point>(points.begin() + points.size() / 2, points.end()), hull2);

	hullOut = joinHulls(hull1, hull2);
}

HULL joinHulls(HULL& left, HULL& right) 
{
	int lt, rt, lb, rb; // left/right hull, top/bottom index of point in hull
	findTopBounds(left, right, lt, rt);
	findBottomBounds(left, right, lb, rb);

	HULL j;

	//visualizer.clearHulls();

	int i = 0;
	do {
		//cv::circle(visualizer.matHulls, left[i], 3, cv::Vec3f(0, 0, 1), 2);
		//visualizer.visualize();
		j.push_back(left[i]);
		i = (++i) % left.size();
	} while (i != (lt + 1) % left.size());

	i = rt;
	do {
		//cv::circle(visualizer.matHulls, right[i], 3, cv::Vec3f(1, 0, 0), 2);
		//visualizer.visualize();
		j.push_back(right[i]);
		i = (++i) % right.size();
	} while (i != (rb + 1) % right.size());

	if (lb != lt && lb != 0) {
		i = lb;
		do {
			//cv::circle(visualizer.matHulls, left[i], 3, cv::Vec3f(0, 1, 0), 2);
			//visualizer.visualize();
			j.push_back(left[i]);
		} while ((++i) % left.size() != 0);
	}

	//visualizer.clearHulls();
	//visualizer.drawHull(j);
	//visualizer.visualize();

	return j;
}

void findTopBounds(HULL& left, HULL& right, int& indexLeft, int& indexRight)
{
	int il = rightMostIndex(left); // (most right) index of point in left hull 
	int ir = leftMostIndex(right); // (most left) index of point in right hull 

	bool changed = true;
	while (changed) {
		changed = false;
		while (orientation(left[il], right[ir], left[(il - 1 + left.size()) % left.size()]) < 0) {
			il = (il - 1 + left.size()) % left.size();
			changed = true;
		}

		while (orientation(left[il], right[ir], right[(ir + 1) % right.size()]) < 0) {
			ir = (ir + 1) % right.size();
			changed = true;
		}
	}

	indexLeft = il;
	indexRight = ir;
}

void findBottomBounds(HULL& left, HULL& right, int& indexLeft, int& indexRight)
{
	int il = rightMostIndex(left); // (most right) index of point in left hull 
	int ir = leftMostIndex(right); // (most left) index of point in right hull 


	bool changed = true;
	while (changed) {
		changed = false;
		while (orientation(left[il], right[ir], left[(il + 1) % left.size()]) > 0) {
			il = (il + 1) % left.size();
			changed = true;
		}

		while (orientation(left[il], right[ir], right[(ir - 1 + right.size()) % right.size()]) > 0) {
			ir = (ir - 1 + right.size()) % right.size();
			changed = true;
		}
	}
	indexLeft = il;
	indexRight = ir;
}

int orientation(cv::Point lineStart, cv::Point lineEnd, cv::Point point)
{
	auto dirLine = lineEnd - lineStart;
	auto dirPoint = point - lineStart;
	cv::Vec3f line(dirLine.x, dirLine.y, 0);
	cv::Vec3f dir(dirPoint.x, dirPoint.y, 0);

	return (int)line.cross(dir)[2]; // returns local side of the point (above / below)
}

int leftMostIndex(HULL& hull) 
{
	return 0;
}

int rightMostIndex(HULL& hull) 
{
	int maxIndex = 0;
	for (size_t i = 0; i < hull.size(); i++) {
		if (hull[i].x > hull[maxIndex].x) {
			maxIndex = i;
		}
	}

	return maxIndex;
}