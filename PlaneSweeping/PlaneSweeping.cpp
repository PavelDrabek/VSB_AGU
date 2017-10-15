// PlaneSweeping.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <typeinfo>
#include "PlaneSweeping.h"

void LineIntersections(std::vector<Segment*> &segments, std::vector<EventPoint> &intersections, Visualizer& visualizer)
{
	PriorityQueue<EventPoint> e;
	std::vector<EventPoint> t;
	Dictionary a;

	for (int i = 0; i < segments.size(); i++)
	{
		Segment* s = segments.at(i);
		e.insert(EventPoint(s->line.p1, s, EventType::Start));
		e.insert(EventPoint(s->line.p2, s, EventType::End));
		//std::cout << "Address: " << s->point.x << std::endl;
	}

	visualizer.redraw();

	while (!e.isEmpty()) 
	{
		EventPoint p = e.min();
		visualizer.setPoint(p);

		if (p.isLeft()) 
		{
			Segment* s = p.s1;
			a.insert(s);
			Segment* s1 = a.above(s);
			Segment* s2 = a.below(s);
			if (s1 != nullptr) {
				cv::Point x = s->line.intersect(s1->line);
				if (x != POINT_INVALID) {
					t.push_back(EventPoint(x, s1, s));
				}
			}
			if (s2 != nullptr) {
				cv::Point x = s->line.intersect(s2->line);
				if (x != POINT_INVALID) {
					t.push_back(EventPoint(x, s, s2));
				}
			}
		}
		else if (p.isRight()) 
		{
			Segment* s = p.s1;
			Segment* s1 = a.above(s);
			Segment* s2 = a.below(s);
			if (s1 != nullptr && s2 != nullptr) {
				cv::Point x = s1->line.intersect(s2->line);
				if (x != POINT_INVALID) {
					t.push_back(EventPoint(x, s1, s2));
				}
			}
			a.remove(s);
		}
		else /* p is intersection */
		{
			Segment* s3 = a.above(p.s1);
			Segment* s4 = a.below(p.s2);
			if (s3 != nullptr) {
				cv::Point x = s3->line.intersect(p.s2->line);
				if (x != POINT_INVALID) {
					t.push_back(EventPoint(x, s3, p.s2));
				}
			}
			if (s4 != nullptr) {
				cv::Point x = p.s1->line.intersect(s4->line);
				if (x != POINT_INVALID) {
					t.push_back(EventPoint(x, p.s1, s4));
				}
			}
			std::cout << "swap" << std::endl;
			visualizer.swap(p.s1, p.s2);
			a.swap(p.s1, p.s2);
		}

		visualizer.draw(a);

		while (!t.empty()) {
			EventPoint x = t.at(0);
			t.erase(t.begin());
			if (!e.member(x)) {
				intersections.push_back(x);
				e.insert(x);
			}
		}

		visualizer.drawIntersections(intersections);
		visualizer.redraw();
	}
}

int main()
{
	const int N = 10; // number of lines
	const int W = 700;
	const int H = 400;

	cv::Point points[2 * N];
	std::vector<Segment*> segments;
	std::vector<EventPoint> intersections;

	for (int i = 0; i < N; i++)
	{
		cv::Point p1 = cv::Point(rand() % W, rand() % H);
		cv::Point p2 = cv::Point(rand() % W, rand() % H);

		if (p1.x > p2.x) {
			cv::Point tmp = p1;
			p1 = p2;
			p2 = tmp;
		}

		points[i * 2] = p1;
		points[i * 2 + 1] = p2;
		segments.push_back(new Segment(p1, p2, p1));
	}

	Visualizer visualizer(W, H, segments);

	LineIntersections(segments, intersections, visualizer);

	cv::waitKey();
    return 0;
}

