#include <iomanip>
#include <cmath>
#include <algorithm>
#include <utility>

#include "subtree.h"

namespace EMST {
	sub_tree::sub_tree(void) : arcs_(), points_(), cost_(0) {}

	sub_tree::~sub_tree(void) {

	}

	void sub_tree::add_arc(const CyA::arc &a) {
		arcs_.push_back(a);
		points_.insert(a.first);
		points_.insert(a.second);
	}

	void sub_tree::add_point(const CyA::point &p) {
		points_.insert(p);
	}

	bool sub_tree::contains(const CyA::point &p) const {
		return points_.find(p) != points_.end();
	}

	void sub_tree::merge(const sub_tree &subtree, const CyA::weigthed_arc &arc) {
		arcs_.insert(arcs_.end(), subtree.arcs_.begin(), subtree.arcs_.end());
		arcs_.push_back(arc.second);

		points_.insert(subtree.points_.begin(), subtree.points_.end());
		points_.insert(arc.second.first);
		points_.insert(arc.second.second);

		cost_ += arc.first + subtree.get_cost();
	}

}