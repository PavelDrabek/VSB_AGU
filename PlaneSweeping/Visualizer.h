#pragma once
class Visualizer
{
	void drawLine(Line& line);

public:
	Visualizer(const int W, const int H, std::vector<Segment*>& segments);

	int W, H;

	cv::Mat matStatic;
	cv::Mat matLines;
	cv::Mat matProgress;

	cv::Point point;

	void redraw();
	void drawIntersections(std::vector<EventPoint> internsections);
	void draw(Dictionary dict);
	void setPoint(EventPoint ep);
	void swap(Segment* s1, Segment* s2);
	void drawLine(cv::Mat& m, Line l, cv::Scalar c);
};

