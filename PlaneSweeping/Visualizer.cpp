#include "stdafx.h"
#include "Visualizer.h"


void Visualizer::drawLine(Line & line)
{
	//cv::circle(matStatic, line.p1, 3, cv::Scalar(0, 0, 1), -1);
	//cv::circle(matStatic, line.p2, 3, cv::Scalar(0, 1, 0), -1);
	cv::line(matStatic, line.p1, line.p2, cv::Scalar(1, 1, 1), 1);
}

void Visualizer::drawLine(cv::Mat& m, Line l, cv::Scalar c)
{
	cv::line(m, l.p1, l.p2, c, 2);
}

void Visualizer::drawPoint(cv::Mat& m, cv::Point p, cv::Scalar c, int radius)
{
	cv::circle(m, p, radius, c, -1);
}

void Visualizer::drawPoint(cv::Point p, cv::Scalar c, int radius)
{
	drawPoint(matLines, p, c, radius);
}

void Visualizer::drawSegment(Segment * s1, cv::Scalar c, cv::Scalar pointColor)
{
	drawLine(matLines, s1->line, c);
	if (pointColor == blue()) {
		drawPoint(s1->line.p2, pointColor, 6);
	}
	else {
		drawPoint(s1->point, pointColor, 6);
	}
}

Visualizer::Visualizer(const int W, const int H, std::vector<Segment*>& segments)
{
	this->W = W;
	this->H = H;

	matStatic = cv::Mat(H, W, CV_32FC3);
	matLines = cv::Mat(H, W, CV_32FC3);
	matProgress = cv::Mat(H, W, CV_32FC3);

	for (int i = 0; i < segments.size(); i++)
	{
		Segment* s = segments.at(i);
		drawLine(s->line);
		cv::putText(matStatic, s->name, s->line.p1 + cv::Point(-20, 10), 1, 2, Visualizer::white());
	}
}

void Visualizer::redraw()
{
	matProgress = cv::Mat(H, W, CV_32FC3);
	
	cv::add(matProgress, matStatic, matProgress);
	cv::add(matProgress, matLines, matProgress);
	cv::imshow("Plane sweeping", matProgress);

	cv::waitKey();
}

void Visualizer::clear()
{
	matLines = cv::Mat(H, W, CV_32FC3);
}

void Visualizer::drawIntersections(std::vector<EventPoint> internsections)
{
	for (int i = 0; i < internsections.size(); i++)
	{
		//cv::circle(matLines, internsections.at(i).point, 4, cv::Scalar(1, 0, 0), -1);
		drawPoint(internsections.at(i).point, red(), 5);
	}
}

void Visualizer::draw(Dictionary e)
{
	for (std::set<Segment*>::iterator it = e.queue.begin(); it != e.queue.end(); ++it) {
		Segment* s = (*it);
		cv::circle(matLines, s->point, 2, cv::Scalar(1, 1, 0), -1);
	}
}

void Visualizer::setPoint(EventPoint ep)
{
	cv::Scalar color;
	if (ep.isLeft()) {
		color = cv::Scalar(1, 1, 1);
	}
	else if (ep.isRight()) {
		color = cv::Scalar(0, 1, 1);
	}
	else {
		color = cv::Scalar(0, 0, 1);
	}
	cv::line(matLines, cv::Point(ep.point.x, 0), cv::Point(ep.point.x, H), color, 1);
}

void Visualizer::swap(Segment * s1, Segment * s2)
{
	drawSegment(s1, red(), true);
	drawSegment(s2, green(), true);
}
