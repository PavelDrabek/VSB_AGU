#pragma once
class Visualize
{
public:
	Visualize(int W, int H);
	Visualize(int W, int H, int waitMs);
	~Visualize();

	int W, H;
	int waitMs = 0;

	cv::Mat matPoints;
	cv::Mat matHulls;

	void clearHulls();
	void clearPoints();

	void drawPoints(std::vector<cv::Point>& points);
	void drawHull(std::vector<cv::Point>& hull, bool final = false);
	void drawHulls(std::vector<std::vector<cv::Point>>& hulls);
	void visualize();
};

