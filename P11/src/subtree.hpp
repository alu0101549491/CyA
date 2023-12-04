// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 11: Algoritmos Voraces (Greedy). Euclidean Minimum Spanning Tree
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 05/12/2023
// Archivo subtree.hpp: programa cliente.
// Contiene la declaración de la clase sub_tree perteneciente
// al namespace EMST
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P11
//
// Historial de revisiones
// 01/12/2023 - Creación (primera versión) del código
// 04/12/2023 - Finalización (última versión) del código

#pragma once

#include <iostream>
#include <cmath>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <utility>

#include "point_types.hpp"

namespace EMST {
	class sub_tree {
	 public:
		sub_tree(void);
		~sub_tree(void);

		void AddArc(const Kruskal::arc &new_arc);
		void AddPoint(const Kruskal::point &new_point);
		bool Contains(const Kruskal::point &point) const;
		void Merge(const sub_tree &subtree, const Kruskal::weigthed_arc &arc);

		inline const Kruskal::tree& GetArcs(void) const { return arcs_; }
		inline const Kruskal::point_collection& GetPoints(void) const { return points_; }
		inline double GetCost(void) const { return cost_; }
	 private:
		Kruskal::tree arcs_;
		Kruskal::point_collection points_;
		double cost_;
	};
	
	typedef std::vector<sub_tree> sub_tree_vector;
}