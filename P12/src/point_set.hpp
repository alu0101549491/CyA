#pragma once

#include <vector>
#include <algorithm>
#include <fstream>
#include <cmath>

// para el graphviz representar los puntos pertenecientes a la estructura de otro color

namespace ConvexHull {
	typedef std::pair<double,double> point;
	typedef std::pair<point, point> line;
	typedef std::vector<point> point_vector;

	enum side {
		LEFT = -1,
		CENTER,
		RIGHT
	};

	class point_set : public point_vector	{
	 public:
		point_set(const std::vector<point> &points);
		void quickHull(void);
		//void write_hull(std::ostream &os) const;
		//void write(std::ostream &os) const;

		inline const point_vector& get_hull(void) const { return hull_; }
		inline const point_vector& get_points(void) const { return *this; }

	 private:
		point_vector hull_;
		void quickHull(const line &my_line, int side);
		double distance(const line &my_line, const point &my_point) const;
		double EuclideanDistance(const point& point_1, const point& point_2) const;
		int find_side(const line &my_line, const point &my_point) const;
		void x_bounds(point &min_x, point &max_x) const;
		double point_2_line(const line &my_line, const point &my_point) const;
		bool farthest_point(const line &my_line, int side, point &farthest) const;
	};
}
