// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 11: Algoritmos Voraces (Greedy). Euclidean Minimum Spanning Tree
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 05/12/2023
// Archivo point_set.hpp: programa cliente.
// Contiene la declaración de la clase point_set, heredada de
// un vector de puntos del namespace Kruskal
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P11
//
// Historial de revisiones
// 01/12/2023 - Creación (primera versión) del código
// 04/12/2023 - Finalización (última versión) del código

#pragma once

#include <algorithm>
#include <iomanip>
#include <cmath>
#include <map>

#include "subtree.hpp"

typedef std::vector<EMST::sub_tree> forest;

class point_set : public Kruskal::point_vector {
 public:
	inline point_set(const Kruskal::point_vector &points);
	point_set() {};
	inline ~point_set(void) { emst_.clear(); };
	inline void EMST(void);
	void WriteTree(std::ostream &outstream) const;
	void Write(std::ostream &outstream) const;
	void MakeADot() const;
	double GetMin() const { return min_; }
	double GetMax() const { return max_; }
	void CalculateMinAndMax();
	inline const Kruskal::tree& GetTree(void) const { return emst_; }
	inline const Kruskal::point_vector& GetPoints(void) const { return *this; }
	inline const double GetCost(void) const { return ComputeCost(); }
 private:
	Kruskal::tree emst_;
	double min_;
	double max_;
	void ComputeArcVector(Kruskal::arc_vector &vector_of_arcs) const;
	void FindIncidentSubtrees(const forest& subtree_forest, const Kruskal::arc &arc, int& id_i, int& id_j) const;
	void MergeSubtrees(forest& subtree_forest, const Kruskal::weigthed_arc &arc, int id_i, int id_j) const;
	double ComputeCost(void) const;
	double EuclideanDistance(const Kruskal::arc& arc) const;
};