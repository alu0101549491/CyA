#include "point_types.h"
#include "point_set.h"

void point_set::EMST(void) {
  CyA::arc_vector av;
  compute_arc_vector(av);
  forest st;

  for (const CyA::point &p : *this) {
    EMST::sub_tree s;
    s.add_point(p);

    st.push_back(s);
  }

  for (const CyA::weigthed_arc &a : av) {
    int i, j;
    find_incident_subtrees(st, a.second, i, j);
    if (i != j) {
        merge_subtrees(st, a.second, i, j);
    }
  }

  emst_ = st[0].get_arcs();
}
