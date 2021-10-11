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
		static int getTValue(std::vector<Point2d>& pointList, float step, size_t pointsCount, int i);
		static float perpendicularDistance(const Point2d& p, const Point2d& line_p1, const Point2d& line_p2);
		static float shortestDistance(const Point2d& p, const Point2d& line_p1, const Point2d& line_p2);
		static DistanceIndex maxDistance(std::vector<Point2d>& pointList, bool use_perpendicular_dist);
		static float binarySearch(std::vector<Point2d>& pointList, float step, size_t pointsCount, float min = 1, float max = std::numeric_limits<float>::max());
	};
}
