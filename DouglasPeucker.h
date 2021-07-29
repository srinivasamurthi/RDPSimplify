#pragma once

#include <vector>
#include <functional>
#include "Utils.h"

namespace RDP
{
	class DouglasPeucker
	{
	public:
		static std::vector<Point2d> Simplify(std::vector<Point2d>& pointList, float epsilon);
		static std::vector<Point2d> SimplifyTo(std::vector<Point2d>& pointList, size_t pointsCount);
	private:
		static float perpendicularDistance(const Point2d& p, const Point2d& line_p1, const Point2d& line_p2);
		static float shortestDistance(const Point2d& p, const Point2d& line_p1, const Point2d& line_p2);
		static DistanceIndex maxDistance(std::vector<Point2d>& pointList, std::function<float(const Point2d& , const Point2d&, const Point2d&)> distance_fn);
		static float binarySearch(std::function<int(int)> test, float min = 1, float max = std::numeric_limits<float>::max());
	};
}
