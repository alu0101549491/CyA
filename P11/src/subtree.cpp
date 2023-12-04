// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 11: Algoritmos Voraces (Greedy). Euclidean Minimum Spanning Tree
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 05/12/2023
// Archivo subtree.cpp: programa cliente.
// Contiene las definiciones de los métodos de la clase sub_tree
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P11
//
// Historial de revisiones
// 01/12/2023 - Creación (primera versión) del código
// 04/12/2023 - Finalización (última versión) del código


#include "subtree.hpp"

namespace EMST {

	/** @brief Constructor de la clase sub_tree */
	sub_tree::sub_tree(void) : arcs_(), points_(), cost_(0) {}

	/** @brief Destructor de la clase sub_tree */
	sub_tree::~sub_tree(void) {}

	/** @brief Método que se encarga de añadir un nuevo arco al árbol
	 * 	@param[in] new_arc. Arco que será añadido.
	 */
	void sub_tree::AddArc(const Kruskal::arc &new_arc) {
		arcs_.push_back(new_arc);
		points_.insert(new_arc.first);
		points_.insert(new_arc.second);
	}

	/** @brief Método que se encarga de añadir un nuevo punto al árbol
	 * 	@param[in] new_point. Punto que será añadido.
	 */
	void sub_tree::AddPoint(const Kruskal::point &new_point) {
		points_.insert(new_point);
	}

	/** @brief Método que se encarga de comprobar que el árbol contiene
	 * 				 un punto dado
	 * 	@param[in] my_point. Punto que será comprobado.
	 *  @return Retorna true si lo contiene, y false en caso contrario.
	 */
	bool sub_tree::Contains(const Kruskal::point &my_point) const {
		return points_.find(my_point) != points_.end();
	}

	/** @brief Método que se encarga de fusionar el árbol con otro árbol 
	 * 				 mediante un arco.
	 * 	@param[in] subtree. Árbol al que se unirá.
	 * 	@param[in] arc. Arco mediante el cual se unirán los árboles.
	 */
	void sub_tree::Merge(const sub_tree &subtree, const Kruskal::weigthed_arc &arc) {
		arcs_.insert(arcs_.end(), subtree.arcs_.begin(), subtree.arcs_.end());
		arcs_.push_back(arc.second);

		points_.insert(subtree.points_.begin(), subtree.points_.end());

		cost_ += arc.first + subtree.GetCost();
	}

}