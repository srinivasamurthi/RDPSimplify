/***
 * This is an Ramer¨CDouglas¨CPeucker algorithm implementation (2d version). https://en.wikipedia.org/wiki/Ramer%E2%80%93Douglas%E2%80%93Peucker_algorithm
 * Given a curve composed of line segments to find a similar curve with fewer points. 
 * 
 * Recursive implementation, might stack overflow when the curve is complicate.
 */


#include "DouglasPeucker.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include<string>

std::vector<RDP::Point2d> get_test_data() {
	auto data = std::vector<RDP::Point2d>();
	std::fstream f;
	std::string temp;
	f.open("E:\\_work\\others\\_WEB\\LineSimplify\\test.csv", std::ios::in);
	
	while (f >> temp) {
		std::vector<float> points;
		std::stringstream ss(temp);
		for (float i; ss >> i;) {
			points.push_back(i);
			if (ss.peek() == ',')
				ss.ignore();
		}
		data.push_back(RDP::Point2d(points[0], points[1]));
	}
	f.close();
	return data;
}

int main()
{
	std::vector<RDP::Point2d> vertices1;
	vertices1.push_back(RDP::Point2d(1, 1));
	vertices1.push_back(RDP::Point2d(1.2, 0.4));
	vertices1.push_back(RDP::Point2d(2, 0.2));
	vertices1.push_back(RDP::Point2d(3, 0.6));
	vertices1.push_back(RDP::Point2d(4, 3));
	auto data = get_test_data();

	std::vector<RDP::Point2d> result = RDP::DouglasPeucker::SimplifyTo(data, 150);
	
	//auto result = RDP::DouglasPeucker::Simplify(vertices1, 1.2);
	for (auto p:result)
		std::cout << p.x_ << " " << p.y_ << "\n";
	
	return 0;
}
