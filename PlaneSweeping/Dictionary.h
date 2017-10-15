#pragma once
class Dictionary
{
public:
	Dictionary();
	~Dictionary();

	std::set<Segment*> queue;

	void insert(Segment* s);
	void remove(Segment* s);
	Segment* above(Segment* s);
	Segment* below(Segment* s);
	void swap(Segment *s1, Segment *s2);
};

