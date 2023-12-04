// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 11: Algoritmos Voraces (Greedy). Euclidean Minimum Spanning Tree
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 05/12/2023
// Archivo point_types.hpp: programa cliente.
// Contiene las declaraciones de tipos de variable del namespace Kruskal
// y sus sobrecargas de operador
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P11
//
// Historial de revisiones
// 01/12/2023 - Creación (primera versión) del código
// 04/12/2023 - Finalización (última versión) del código

#pragma once

#include <iostream>
#include <utility>
#include <iomanip>
#include <vector>
#include <set>

#define MAX_SZ 3
#define MAX_PREC 0

namespace Kruskal {
	typedef std::pair<double, double> point;
	typedef std::pair<point, point> line;
	typedef std::vector<point> point_vector;

	typedef std::pair<point, point> arc;
	typedef std::pair<double, arc> weigthed_arc;
	typedef std::vector<weigthed_arc> arc_vector;

	typedef std::set<point> point_collection;
	typedef std::vector<arc> tree;
}

std::ostream& operator<<(std::ostream& outstream, const Kruskal::point_vector& points);
std::ostream& operator<<(std::ostream& outstream, const Kruskal::point& point);

std::istream& operator>>(std::istream& inputstream, Kruskal::point_vector& points);
std::istream& operator>>(std::istream& inputstream, Kruskal::point& point);