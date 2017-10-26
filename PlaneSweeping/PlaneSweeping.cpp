// PlaneSweeping.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <typeinfo>
#include "PlaneSweeping.h"

void print(Dictionary a) 
{
	std::cout << "   dict: ";
	for (std::set<Segment*>::iterator it = a.queue.begin(); it != a.queue.end(); ++it) {
		Segment* s = (*it);
		std::cout << s->name << "(" << s->point.y << "), ";
	}
	std::cout << std::endl;
}

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
		visualizer.clear();
		visualizer.setPoint(p);
		visualizer.drawSegment(p.s1, Visualizer::yellow());

		if (p.isLeft()) 
		{
			Segment* s = p.s1;
			a.insert(s);
			std::cout << "insert " << s->name << " (" << s->point.x << ", " << s->point.y << ")" << std::endl;
			print(a);
			Segment* s1 = a.above(s);
			Segment* s2 = a.below(s);
			if (s1 != nullptr) {
				visualizer.drawSegment(s1, Visualizer::green(), Visualizer::green());
				cv::Point x = s->line.intersect(s1->line);
				if (x != POINT_INVALID && x.x > p.point.x) {
					std::cout << "-add P (" << x.x << ", " << x.y << ") crossing " << s->name << " and " << s1->name << std::endl;
					t.push_back(EventPoint(x, s1, s));
				}
			}
			if (s2 != nullptr) {
				visualizer.drawSegment(s2, Visualizer::green(), Visualizer::blue());
				cv::Point x = s->line.intersect(s2->line);
				if (x != POINT_INVALID && x.x > p.point.x) {
					std::cout << "-add P (" << x.x << ", " << x.y << ") crossing " << s->name << " and " << s2->name << std::endl;
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
				visualizer.drawSegment(s1, Visualizer::blue(), Visualizer::green());
				visualizer.drawSegment(s2, Visualizer::blue(), Visualizer::blue());
				cv::Point x = s1->line.intersect(s2->line);
				if (x != POINT_INVALID && x.x > p.point.x) {
					std::cout << "-add P (" << x.x << ", " << x.y << ") crossing " << s1->name << " and " << s2->name << std::endl;
					t.push_back(EventPoint(x, s1, s2));
				}
			}
			a.remove(s);
			std::cout << "delete " << s->name << " (" << s->point.x << ", " << s->point.y << ")" << std::endl;
			print(a);
		}
		else /* p is intersection */
		{
			visualizer.drawSegment(p.s1, Visualizer::pink());
			visualizer.drawSegment(p.s2, Visualizer::pink());

			Segment* s3 = a.above(p.s1);
			Segment* s4 = a.below(p.s2);
			if (s3 != nullptr) {
				visualizer.drawSegment(s3, Visualizer::red(), Visualizer::green());
				cv::Point x = s3->line.intersect(p.s2->line);
				if (x != POINT_INVALID && x.x > p.point.x) {
					std::cout << "-add P (" << x.x << ", " << x.y << ") crossing " << s3->name << " and " << p.s2->name << std::endl;
					t.push_back(EventPoint(x, s3, p.s2));
				}
			}
			if (s4 != nullptr) {
				visualizer.drawSegment(s4, Visualizer::red(), Visualizer::blue());
				cv::Point x = p.s1->line.intersect(s4->line);
				if (x != POINT_INVALID && x.x > p.point.x) {
					std::cout << "-add P (" << x.x << ", " << x.y << ") crossing " << p.s1->name << " and " << s4->name << std::endl;
					t.push_back(EventPoint(x, p.s1, s4));
				}
			}
			std::cout << "swap " << p.s1->name << " <-> " << p.s2->name << " (" << p.s1->point.x << ", " << p.s1->point.y << ") <-> (" << p.s2->point.x << ", " << p.s2->point.y << ")" << std::endl;
			a.swap(p.s1, p.s2, p.point);
			print(a);
		}


		while (!t.empty()) {
			EventPoint x = t.at(0);
			t.erase(t.begin());
			if (!e.member(x)) {
				intersections.push_back(x);
				e.insert(x);
			}
			else {
				visualizer.drawPoint(x.point, Visualizer::white());
			}
		}

		visualizer.draw(a);
		visualizer.drawIntersections(intersections);
		visualizer.redraw();
	}
}

int main()
{
	const int N = 10; // number of lines
	const int W = 1400;
	const int H = 800;

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
		Segment* s = new Segment(p1, p2, p1);
		s->name = (char)('a' + i);
		segments.push_back(s);
	}

	Visualizer visualizer(W, H, segments);

	LineIntersections(segments, intersections, visualizer);

	cv::waitKey();
    return 0;
}

