#include "point_set.hpp"

using namespace ConvexHull;

/** @brief Función que se encarga de imprimir un punto
 *  @param[in] outstream. Flujo de salida
 *  @param[in] point. Punto a imprimir
 *  @return Retorna el flujo de salida
 */
std::ostream& ConvexHull::WritePoint(std::ostream& outstream, const point& point) {
	outstream << "(" << std::setw(3) << std::fixed << std::setprecision(0) << point.first << ", ";
	outstream << std::setw(3) << std::fixed << std::setprecision(0) << point.second << ")" << std::endl;
	return outstream;
}

/** @brief Constructor de la clase point_set
 *  @param[in] points. Vector de puntos para pasarle a la herencia de vector de puntos de la clase
 */
point_set::point_set(const std::vector<point> &points) {
	for (auto& point : points) {
		push_back(point);
	}
	QuickHull();
}

/** @brief Método que se encarga de imprimir la envoltura convexa
 *  @param[in] outstream. Flujo de salida
 */
void point_set::WriteHull(std::ostream &outstream) const {
	for (auto& point : hull_) {
		WritePoint(outstream, point);
	}
}

/** @brief Método que se encarga de imprimir los puntos de point_set
 *  @param[in] outstream. Flujo de salida
 */
void point_set::Write(std::ostream &outstream) const {
	for (auto& point : (*this)) {
		WritePoint(outstream, point);
	}
}

/** @brief Método que se encarga de imprimir los datos de point_set en un fichero tipo .dot
 *  @param[in] outstream. Flujo de salida
 */
void point_set::MakeADot(std::ostream &outstream) const {
	int point_name = 0;
  std::map<int, point> points_map;
	outstream << "graph {" << std::endl;
	for (auto& p : hull_) {
		outstream << "\t" << point_name << " [pos=\"" << p.first << "," << p.second << "!\"]" << std::endl;
		points_map.insert(std::pair<int, point>(point_name, p));
		point_name++;
	}
	for (auto& line : lines_) {
		int origin, destination;
		for (auto& pair : points_map) {
			if (pair.second == line.first) origin = pair.first;
			if (pair.second == line.second) destination = pair.first;
		}
		outstream << "\t" << origin << " -- " << destination << " [color=purple];" << std::endl;
	}
	outstream << "}" << std::endl;
}

/** @brief Método que se encarga de inicializar la búsqueda de la envoltura convexa recursivamente */
void point_set::QuickHull(void) {
	hull_.clear();
	point min_x_point, max_x_point; 
	XBounds(min_x_point, max_x_point);

	QuickHull(line(min_x_point, max_x_point), side::LEFT);
	QuickHull(line(min_x_point, max_x_point), side::RIGHT);

	std::sort(hull_.begin(), hull_.end());
	hull_.erase(std::unique(hull_.begin(), hull_.end()), hull_.end());
}

/** @brief Método que se encarga de realizar la búsqueda de el punto más lejano a una linea en cierto lado 
 *  @param[in] my_line. Linea desde la cual se va a buscar el punto más lejano a un lado determinado.
 *  @param[in] side. Lado determinado
 */
void point_set::QuickHull(const line &my_line, int side) {
	point farthest;
	if (FarthestPoint(my_line, side, farthest)) {
		QuickHull(line(my_line.first, farthest), -FindSide(line(my_line.first, farthest), my_line.second));
		QuickHull(line(farthest, my_line.second), -FindSide(line(farthest, my_line.second), my_line.first));
	}
	else {
		hull_.push_back(my_line.first);
		hull_.push_back(my_line.second);
		lines_.push_back(my_line);
	}
}

/** @brief Método que calcula la distancia entre una linea y un punto
 *  @param[in] my_line. Linea dada.
 *  @param[in] my_point. Punto dado.
 *  @return Valor de la distancia
 */
double point_set::Point2Line(const line &my_line, const point &my_point) const {
	const point &p1 = my_line.first;
	const point &p2 = my_line.second;
	return (my_point.second - p1.second) * (p2.first - p1.first) - (p2.second - p1.second) * (my_point.first - p1.first);
}

/** @brief Método que calcula la distancia entre una linea y un punto en valor absoluto
 *  @param[in] my_line. Linea dada.
 *  @param[in] my_point. Punto dado.
 *  @return Valor de la distancia en valor absoluto.
 */
double point_set::Distance(const line &my_line, const point &my_point) const {
	return fabs(Point2Line(my_line, my_point));
}

/** @brief Método que revisa si existe un punto considerado como el más lejano de una linea en cierto dado
 *  @param[in] my_line. Linea dada.
 *  @param[in] side. Lado dado.
 *  @param[in] farthest. En caso de que existiese se guarda el punto aqui.
 *  @return Si existe devuelve true, sino devuelve false.
 */
bool point_set::FarthestPoint(const line &my_line, int side, point &farthest) const {
	farthest = point_vector::at(0);
	double max_dist = 0;
	bool found = false;
	for (const point &vec_point : *this) {
		const double dist = Distance(my_line, vec_point);
		if (FindSide(my_line, vec_point) == side && dist > max_dist) {
			farthest = vec_point;
			max_dist = dist;
			found = true;
		}
	}
	return found;
}

/** @brief Método que encuentra a que lado está un punto de una linea
 *  @param[in] my_line. Linea dada.
 *  @param[in] my_point. Punto dado.
 *  @return Valor del lado en la enumeracion del namespace ConvexHull.
 */
int point_set::FindSide(const line &my_line, const point &my_point) const {
	if (Point2Line(my_line, my_point) > 0) return side::RIGHT;
	if (Point2Line(my_line, my_point) < 0) return side::LEFT;
	else return side::CENTER;
}

/** @brief Método que encuentra inicialmente los puntos más alejados entre si
 *  @param[in] min_x. Aquí se devolverá el punto mínimo.
 *  @param[in] max_x. Aquí se devolverá el punto máximo.
 */
void point_set::XBounds(point &min_x, point &max_x) const {
	min_x = std::make_pair(INT32_MAX, INT32_MAX);
	max_x = std::make_pair(0.0,0.0);
	for (unsigned i = 0; i < (*this).size(); ++i) {
		if ((*this)[i].first < min_x.first || (*this)[i].second < min_x.second) {
			min_x = (*this)[i];
		}
		if ((*this)[i].first > max_x.first || (*this)[i].second > max_x.second) {
			max_x = (*this)[i];
		}
	}
}

double point_set::BiggestDistance(point& point1, point& point2) {
	double distance = 0.0;
	for (unsigned i = 0; i < hull_.size() - 1; ++i) {
		unsigned j = i + 1;
		double aux_distance = sqrt(pow(hull_[j].first - hull_[i].first, 2) + pow(hull_[j].second - hull_[i].second, 2));
		if (aux_distance > distance) {
			distance = aux_distance;
			point1 = hull_[i];
			point2 = hull_[j];
		}
	}
	return distance;
}
