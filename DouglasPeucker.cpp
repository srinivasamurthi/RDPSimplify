#include "DouglasPeucker.h"


std::vector<RDP::Point2d> RDP::DouglasPeucker::Simplify(std::vector<Point2d>& pointList, float epsilon)
{
	std::vector<Point2d> resultList;

	// Find the point with the maximum distance
	float dmax = 0;
	int index = 0;
	for (int i = 1; i < pointList.size() - 1; ++i)
	{
		float d = perpendicularDistance(pointList[i], pointList[0], pointList[pointList.size() - 1]);
		if (d > dmax) {
			index = i;
			dmax = d;
		}
	}
	// If max distance is greater than epsilon, recursively simplify
	if (dmax > epsilon)
	{
		std::vector<Point2d> pre_part, next_part;
		for (int i = 0; i <= index; ++i)	pre_part.push_back(pointList[i]);
		for (int i = index; i < pointList.size(); ++i)	next_part.push_back(pointList[i]);
		// Recursive call
		std::vector<Point2d> resultList1 = Simplify(pre_part, epsilon);
		std::vector<Point2d> resultList2 = Simplify(next_part, epsilon);

		// combine
		resultList.insert(resultList.end(), resultList1.begin(), resultList1.end());
		resultList.insert(resultList.end(), resultList2.begin()+1, resultList2.end());
	}
	else
	{
		resultList.push_back(pointList[0]);
		resultList.push_back(pointList[pointList.size() - 1]);
	}
		
	return resultList;
}

std::vector<RDP::Point2d> RDP::DouglasPeucker::SimplifyTo(std::vector<Point2d>& pointList, size_t pointsCount)
{
	std::vector<Point2d> resultList;

	if (pointsCount < 3) {
		resultList.push_back(pointList[0]);
		resultList.push_back(pointList[pointList.size() - 1]);
	}
	else if(pointsCount >= pointList.size()){
		resultList.assign(pointList.begin(), pointList.end());
	}
	else {
		int max = std::numeric_limits<int>::max();
		const float step = maxDistance(pointList,perpendicularDistance).distance_ / max;
		float epsilon = step * binarySearch([&pointList, step, pointsCount](int i) {
			return Simplify(pointList, step * i).size() - pointsCount;
			});
		resultList = Simplify(pointList, epsilon);
	}
	return resultList;
}

float RDP::DouglasPeucker::perpendicularDistance(const Point2d& p, const Point2d& line_p1, const Point2d& line_p2)
{
	Point2d vec1 = Point2d(p.x_ - line_p1.x_, p.y_ - line_p1.y_);
	Point2d vec2 = Point2d(line_p2.x_ - line_p1.x_, line_p2.y_ - line_p1.y_);
	float d_vec2 = sqrt(vec2.x_*vec2.x_ + vec2.y_*vec2.y_);
	float cross_product = vec1.x_*vec2.y_ - vec2.x_*vec1.y_;
	float d = abs(cross_product / d_vec2);
	return d;
}

float RDP::DouglasPeucker::shortestDistance(const Point2d& p, const Point2d& a, const Point2d& b)
{
	auto point_dist_sqr = [](const Point2d& i, const Point2d& j) {
		return powf(i.x_ - j.x_, 2) + powf(i.y_ - j.y_, 2);
	};
	float line_len_sqr = point_dist_sqr(a, b);
	float distance = -1;
	if (line_len_sqr == 0) {
		distance = point_dist_sqr(p, a);
	}
	else {
		auto t = ((p.x_ - a.x_) * (b.x_ - a.x_) + (p.y_ - a.y_) * (b.y_ - a.y_)) / line_len_sqr;

		if (t < 0) {
			distance = point_dist_sqr(p, a);
		}
		else if (t > 1) {
			distance = point_dist_sqr(p, b);
		}
		else {
			distance = point_dist_sqr(p, Point2d(a.x_ + t * (b.x_ - a.x_), a.y_ + t * (b.y_ - a.y_)));
		}
	}
	return sqrt(distance);
}

RDP::DistanceIndex RDP::DouglasPeucker::maxDistance(std::vector<Point2d>& points, std::function<float(const Point2d&, const Point2d&, const Point2d&)> distance_fn) {
	auto first = points[0];
	auto last = points[points.size() - 1];

	int index = -1;
	float distance = 0;

	for (size_t i = 1; i < points.size()-1; i++)
	{
		float d = distance_fn(points[i], first, last);
		if (d > distance) {
			distance = d;
			index = i;
		}
	}
	return DistanceIndex(distance, index);

}

float RDP::DouglasPeucker::binarySearch(std::function<int(int)> test, float min, float max)
{
	int l = floorl(min), r = floorl(max), m = floorl(l + (r -l)*0.5);
	while (r-l >=1)
	{
		const int t = test(m);
		if (t == 0) return m;
		else if (t < 0) r = m - 1;
		else l = m + 1;
		m = floorl(l + (r - l)*0.5);
	}
	return m;
}

