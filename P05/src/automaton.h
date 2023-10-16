// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 5: Implementación de un simulador de autómatas finitos
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 16/10/2023
// Archivo automaton.h: programa cliente.
// Contiene la clase Automaton y la declaración de las funciones del programa
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P05
//
// Historial de revisiones
// 12/10/2023 - Creación (primera versión) del código
// 16/10/2023 - Finalización (última versión) del código

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <vector>
#include <map>
#include "state.h"
#include "alphabet.h"

class Automaton {
 public:
  Automaton(std::ifstream& input_file);
  std::vector<State> GetActualStates() { return actual_states_; }
  Alphabet GetAlphabet() { return alphabet_; }
  void Print();
  bool CheckIfFinalState(const std::vector<State>& states);
  void UpdateActualStates(std::vector<State>& actual_states, const char& character);
  void EpsilonClosure(std::vector<State>& actual_states);
  bool ProcessStrings(const std::string& string);
 private:
  Alphabet alphabet_;
  int number_of_states_;
  std::set<State> states_;
  State initial_state_;
  std::vector<State> final_states_;
  std::vector<State> actual_states_;
};

