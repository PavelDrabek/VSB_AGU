#pragma once

#define HULL std::vector<cv::Point>

struct Point2fLessThan {
	bool operator() (const cv::Point2f& p1, const cv::Point2f& p2) {
		if (p1.x == p2.x) {
			return p1.y < p2.y;
		}

		return (p1.x < p2.x);
	}
};

void dac(std::vector<cv::Point> points, HULL & hullOut);
HULL joinHulls(HULL& h1, HULL& h2);

void findTopBounds(HULL & left, HULL & right, int & indexLeft, int & indexRight);

void findBottomBounds(HULL & left, HULL & right, int & indexLeft, int & indexRight);

int orientation(cv::Point lineStart, cv::Point lineEnd, cv::Point point);

int leftMostIndex(HULL & hull);

int rightMostIndex(HULL & hull);


