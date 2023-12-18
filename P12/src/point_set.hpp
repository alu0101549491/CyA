// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 12: Algoritmos Divide y Vencerás (Divide & Conquer). Cálculo de la envoltura convexa
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 19/12/2023
// Archivo point_set.hpp: programa cliente.
// Contiene la clase point_set y el namespace ConvexHull
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P12
//
// Historial de revisiones
// 12/12/2023 - Creación (primera versión) del código
// 18/12/2023 - Finalización (última versión) del código

#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <map>

// para el graphviz representar los puntos pertenecientes a la estructura de otro color

namespace ConvexHull {
	typedef std::pair<double,double> point;
	typedef std::pair<point, point> line;
	typedef std::vector<point> point_vector;
	typedef std::vector<line> line_vector;

	std::ostream& WritePoint(std::ostream& outstream, const point& point);

	enum side {
		LEFT = -1,
		CENTER,
		RIGHT
	};

	class point_set : public point_vector	{
	 public:
		point_set(const std::vector<point> &points);
		void QuickHull(void);
		void WriteHull(std::ostream &outstream) const;
		void Write(std::ostream &outstream) const;
		void MakeADot(std::ostream &outstream) const;
		inline const point_vector& GetHull(void) const { return hull_; }
		inline const point_vector& GetPoints(void) const { return *this; }
		double Point2Line(const line &my_line, const point &my_point) const;

	 private:
		point_vector hull_;
		line_vector lines_;
		void QuickHull(const line &my_line, int side);
		double Distance(const line &my_line, const point &my_point) const;
		void XBounds(point &min_x, point &max_x) const;
		int FindSide(const line &my_line, const point &my_point) const;
		bool FarthestPoint(const line &my_line, int side, point &farthest) const;
	};
}
