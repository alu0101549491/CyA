// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 11: Algoritmos Voraces (Greedy). Euclidean Minimum Spanning Tree
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 05/12/2023
// Archivo point_types.cpp: programa cliente.
// Contiene las definiciones de las funciones declaradas en point_types.hpp
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P11
//
// Historial de revisiones
// 01/12/2023 - Creación (primera versión) del código
// 04/12/2023 - Finalización (última versión) del código

#include "point_types.hpp"

/** @brief Sobrecarga del operador de extracción de un vector de puntos.
 * 	@param[in] outstream. Flujo de salida.
 * 	@param[in] points. Vector de puntos.
 *  @return Retorna el flujo de salida.
 */
std::ostream& operator<<(std::ostream& outstream, const Kruskal::point_vector& points) {
	outstream << points.size() << std::endl;
	for (const Kruskal::point &point : points) {
		outstream << point << std::endl;
	}
	return outstream;
}

/** @brief Sobrecarga del operador de extracción de un punto.
 * 	@param[in] outstream. Flujo de salida.
 * 	@param[in] point. Punto.
 *  @return Retorna el flujo de salida.
 */
std::ostream& operator<<(std::ostream& outstream, const Kruskal::point& point) {
	outstream << std::setw(MAX_SZ) << std::fixed << std::setprecision(MAX_PREC) << point.first << "\t";
	outstream << std::setw(MAX_SZ) << std::fixed << std::setprecision(MAX_PREC) << point.second;
	return outstream;
}

/** @brief Sobrecarga del operador de inserción de un vector de puntos.
 * 	@param[in] inputstream. Flujo de entrada.
 * 	@param[in] points. Vector de puntos.
 *  @return Retorna el flujo de entrada.
 */
std::istream& operator>>(std::istream& inputstream, Kruskal::point_vector& points) {
	int number_of_points;
	inputstream >> number_of_points;
	points.clear();

	for (int i = 0; i < number_of_points; ++i) {
		Kruskal::point new_point;
		inputstream >> new_point;

		points.push_back(new_point);
	}
	return inputstream;
}

/** @brief Sobrecarga del operador de inserción de un punto.
 * 	@param[in] inputstream. Flujo de entrada.
 * 	@param[in] point. Punto.
 *  @return Retorna el flujo de entrada.
 */
std::istream& operator>>(std::istream& inputstream, Kruskal::point& point) {
	inputstream >> point.first >> point.second;
	return inputstream;
}
