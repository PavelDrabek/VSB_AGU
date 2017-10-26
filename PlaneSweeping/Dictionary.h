#pragma once

struct SegmentComparator {
	bool operator()(const Segment *a, const Segment *b) const {
		return a->point.y < b->point.y;
	}
};

class Dictionary
{
public:
	Dictionary();
	~Dictionary();

	std::set<Segment*, SegmentComparator> queue;

	void insert(Segment* s);
	void remove(Segment* s);
	Segment* above(Segment* s);
	Segment* below(Segment* s);
	void swap(Segment *s1, Segment *s2, cv::Point p);
};

