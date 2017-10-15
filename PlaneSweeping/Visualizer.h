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
	void clear();
	void drawIntersections(std::vector<EventPoint> internsections);
	void draw(Dictionary dict);
	void setPoint(EventPoint ep);
	void swap(Segment* s1, Segment* s2);
	void drawLine(cv::Mat& m, Line l, cv::Scalar c);
	void drawSegment(Segment* s1, cv::Scalar c, bool showPoint = false);
	void drawPoint(cv::Mat& m, cv::Point p, cv::Scalar c, int radius = 3);
	void drawPoint(cv::Point p, cv::Scalar c, int radius = 3);

	static cv::Scalar red() { return cv::Scalar(0, 0, 1); }
	static cv::Scalar green() { return cv::Scalar(0, 1, 0); }
	static cv::Scalar blue() { return cv::Scalar(1, 0, 0); }
	static cv::Scalar white() { return cv::Scalar(1, 1, 1); }
	static cv::Scalar yellow() { return cv::Scalar(0, 1, 1); }
	static cv::Scalar pink() { return cv::Scalar(204/255.0, 163/256.0, 236/255.0); }
};

