// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 11: Algoritmos Voraces (Greedy). Euclidean Minimum Spanning Tree
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 05/12/2023
// Archivo point_set.cpp: programa cliente.
// Contiene las definiciones de los métodos de la clase point_set
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P11
//
// Historial de revisiones
// 01/12/2023 - Creación (primera versión) del código
// 04/12/2023 - Finalización (última versión) del código

#include "point_types.hpp"
#include "point_set.hpp"

/** @brief Constructor de la clase point_set
 *  @param[in] points. Vector de puntos de entrada
 */
inline point_set::point_set(const Kruskal::point_vector& points) {
  for (auto& i : points) {
    push_back(i);
  }
  EMST();
}

/** @brief Método que se encarga de encontrar el Euclidean Minimum Spanning Tree */
inline void point_set::EMST(void) {
  Kruskal::arc_vector vector_of_arcs;
  ComputeArcVector(vector_of_arcs);
  forest subtree_forest;
  for (const Kruskal::point &point : *this) {
    EMST::sub_tree subtree;
    subtree.AddPoint(point);
    subtree_forest.push_back(subtree);
  }
  for (const Kruskal::weigthed_arc &arc : vector_of_arcs) {
    int i, j;
    FindIncidentSubtrees(subtree_forest, arc.second, i, j);
    if (i != j) {
      MergeSubtrees(subtree_forest, arc, i, j);
    }
    if (subtree_forest[0].GetPoints().size() == size()) {
      break;
    }
  }
  emst_ = subtree_forest[0].GetArcs();
}

/** @brief Método que se encarga de computar un vector de arcos entrante
 *         por referencia en base al vector de puntos que hereda la clase.
 *  @param[in] vector_of_arcs. Vector de arcos que se computará
 */
void point_set::ComputeArcVector(Kruskal::arc_vector& vector_of_arcs) const {
  vector_of_arcs.clear();
  const int n = size();
  for (int i = 0; i < n - 1; ++i) {
    const Kruskal::point &point_i = (*this)[i];
    for (int j = i + 1; j < n; ++j) {
      const Kruskal::point &point_j = (*this)[j];
      const double dist = EuclideanDistance(std::make_pair(point_i, point_j));
      vector_of_arcs.push_back(std::make_pair(dist, std::make_pair(point_i, point_j)));
    }
  }
  std::sort(vector_of_arcs.begin(), vector_of_arcs.end());
}

/** @brief Método que se encarga de encontrar arboles incidentes
 *  @param[in] subtree_forest. Conjunto de arboles
 *  @param[in] arc. Arco que se comprobará que pertenece a alguno de los arboles
 *  @param[in] id_i. Identificador (color) del primer punto perteneciente al arbol
 *  @param[in] id_j. Identificador (color) del segundo punto perteneciente al arbol
 */
void point_set::FindIncidentSubtrees(const forest& subtree_forest, const Kruskal::arc& arc, int& id_i, int& id_j) const {
  for (unsigned it = 0; it < subtree_forest.size(); ++it) {
    if (subtree_forest[it].Contains(arc.first) && subtree_forest[it].Contains(arc.second)) {
      id_i = it;
      id_j = it;
      break;
    }
    else {
      if (subtree_forest[it].Contains(arc.first) && !subtree_forest[it].Contains(arc.second)) {
        id_i = it;
      }
      if (!subtree_forest[it].Contains(arc.first) && subtree_forest[it].Contains(arc.second)) {
        id_j = it;
      }
    }
  }
}

/** @brief Método que se encarga de fusionar arboles incidentes
 *  @param[in] subtree_forest. Conjunto de arboles
 *  @param[in] arc. Arco con el que se unirán ambos arboles
 *  @param[in] id_i. Identificador (color) del primer punto perteneciente al arbol
 *  @param[in] id_j. Identificador (color) del segundo punto perteneciente al arbol
 */
void point_set::MergeSubtrees(forest& subtree_forest, const Kruskal::weigthed_arc& arc, int id_i, int id_j) const {
  EMST::sub_tree empty_subtree;
  if (id_i < id_j) {
    subtree_forest[id_i].Merge(subtree_forest[id_j], arc);
    subtree_forest[id_j] = empty_subtree;
  }
  else {
    subtree_forest[id_j].Merge(subtree_forest[id_i], arc);
    subtree_forest[id_i] = empty_subtree;
  }
}

/** @brief Método que se encarga de computar el coste total del EMST.
 *  @return Valor total del coste.
 */
double point_set::ComputeCost(void) const {
  double total_cost;
  for (auto& arc : emst_) {
    total_cost += EuclideanDistance(arc);
  }
  return total_cost;
}

/** @brief Método que se encarga de calcular la distancia euclideana de dos puntos.
 *  @param[in] arc. Arco de dos puntos.
 *  @return Valor de la distancia entre ambos puntos.
 */
double point_set::EuclideanDistance(const Kruskal::arc& arc) const {
  Kruskal::point point1 = arc.first;
  Kruskal::point point2 = arc.second;
  return sqrt(pow(point2.first - point1.first,2) + pow(point2.second - point1.second,2));
}

/** @brief Método que se encarga de imprimir el vector de puntos.
 *  @param[in] outstream. Flujo de salida
 */
void point_set::Write(std::ostream& outstream) const {
  for (auto& i : (*this)) {
    outstream << i << std::endl;
  }
}

/** @brief Método que se encarga de imprimir el EMST.
 *  @param[in] outstream. Flujo de salida
 */
void point_set::WriteTree(std::ostream& outstream) const {
  for (auto& arc : emst_) {
    outstream << "(" << arc.first << ") -> (" << arc.second << ")" << std::endl;
  }
  outstream << std::endl << std::setprecision(2) << ComputeCost() << std::endl;
}

/** @brief Método que se encarga de crear un fichero .dot */
void point_set::MakeADot() const {
  std::ofstream outstream{"output.dot"};
  int point_name = 0;
  outstream << "graph {" << std::endl;
  std::multimap<int, Kruskal::point> points_map;
  for (auto& point : GetPoints()) {
    outstream << "\t" << point_name << " [pos=\"" << point.first << "," << point.second << "!\"]" << std::endl;
    points_map.insert(std::pair<int,Kruskal::point>(point_name,point));
    point_name++;
  }
  for (auto& arc : emst_) {
    int origin, destination;
    for (auto& pair : points_map) {
      if (pair.second == arc.first) {
        origin = pair.first;
      }
      if (pair.second == arc.second) {
        destination = pair.first;
      }
    }
    outstream << "\t" << origin << " -- " << destination << std::endl;
  }
  outstream << "}" << std::endl;
}
