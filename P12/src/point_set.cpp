#include "point_set.hpp"

using namespace ConvexHull;

point_set::point_set(const std::vector<point> &points) {
	hull_ = points;
}

void point_set::quickHull(void) {
	hull_.clear();

	point min_x_point; 
	point max_x_point;

	x_bounds(min_x_point, max_x_point);

	quickHull(line(min_x_point, max_x_point), side::LEFT);
	quickHull(line(min_x_point, max_x_point), side::RIGHT);

	// Remove duplicates
	std::sort(hull_.begin(), hull_.end());
	hull_.erase(std::unique(hull_.begin(), hull_.end()), hull_.end());
}

void point_set::quickHull(const line &my_line, int side) {
	point farthest;
	if (farthest_point(my_line, side, farthest)) {
		quickHull(line(my_line.first, farthest), -find_side(line(my_line.first, farthest), my_line.second));
		quickHull(line(farthest, my_line.second), -find_side(line(farthest, my_line.second), my_line.first));
	}
	else {
		hull_.push_back(my_line.first);
		hull_.push_back(my_line.second);
	}
}

bool point_set::farthest_point(const line &my_line, int side, point &farthest) const {
	farthest = point_vector::at(0);
	double max_dist = 0;
	bool found = false;
	for (const point &vec_point : *this) {
		const double dist = distance(my_line, vec_point);
		if (find_side(my_line, vec_point) == side && dist > max_dist) {
			farthest = vec_point;
			max_dist = dist;
			found = true;
		}
	}
	return found;
}

double point_set::distance(const line &my_line, const point &my_point) const {

}

int point_set::find_side(const line &my_line, const point &my_point) const {

}

void point_set::x_bounds(point &min_x, point &max_x) const {
	min_x = std::pair<double, double>(INT32_MAX,INT32_MAX);
	max_x = std::pair<double, double>(0,0);
	for (int i = 0; i < (*this).size(); ++i) {
		if ((*this)[i].first < min_x.first || (*this)[i].second < min_x.second) {
			min_x = (*this)[i];
		}
		if ((*this)[i].first > max_x.first || (*this)[i].second > max_x.second) {
			max_x = (*this)[i];
		}
	}
}

double point_set::point_2_line(const line &my_line, const point &my_point) const {

}