// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 7: Gramáticas en Forma Normal de Chomsky
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 26/10/2023
// Archivo grammar.h: programa cliente.
// Contiene la clase Grammar y la declaración de las funciones del programa
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P07
//
// Historial de revisiones
// 26/10/2023 - Creación (primera versión) del código
// 29/10/2023 - Finalización (última versión) del código

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <sstream>
#include "alphabet.h"

class Grammar {
 public:
  Grammar(const std::string& input);
  Grammar() {}
  void Print();
  void ConvertToCNF();
  bool CheckIfEmptyProductions();
  bool CheckIfUnitaryProductions();
  void ChangeNonTerminalSymbol(char& symbol);
  friend std::ostream& operator<<(std::ostream& out, Grammar output_grammar);
 private:
  std::set<std::string> non_terminals_;
  Alphabet terminals_;
  std::string initial_;
  std::multimap<std::string, std::string> productions_;
};