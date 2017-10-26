#pragma once
class Segment
{
public:
	Segment(cv::Point& start, cv::Point& end, cv::Point& point);
	~Segment();

	Line line;
	cv::Point point;
	std::string name;

	bool operator<(const Segment &rhs) const;
	bool operator>(const Segment &rhs) const;
	bool operator<=(const Segment &rhs) const;
	bool operator>=(const Segment &rhs) const;

	//bool operator(const Segment* lhs, const Segment* rhs) const;
};

