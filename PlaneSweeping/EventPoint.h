#pragma once

enum EventType {
	Start = 0,
	End = 1,
	Intersect = 2
};

class EventPoint
{
public:
	EventPoint(const cv::Point &point, Segment *s1, EventType type) : point(point), s1(s1), s2(nullptr), type(type) {}
	EventPoint(const cv::Point &point, Segment *s1, Segment *s2) : point(point), s1(s1), s2(s2), type(EventType::Intersect) {}
	~EventPoint();

	cv::Point point;
	Segment* s1;
	Segment* s2;
	EventType type;

	bool isLeft() { return type == EventType::Start; }
	bool isRight() { return type == EventType::End; }

	bool operator==(const EventPoint &rhs) const;
	bool operator<(const EventPoint &rhs) const;
	bool operator>(const EventPoint &rhs) const;
	bool operator<=(const EventPoint &rhs) const;
	bool operator>=(const EventPoint &rhs) const;
};

