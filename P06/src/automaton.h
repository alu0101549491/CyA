// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Convertir un NFA en un DFA
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 18/10/2023
// Archivo automaton.h: programa cliente.
// Contiene la clase Automaton y la declaración de las funciones del programa
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P06
//
// Historial de revisiones
// 18/10/2023 - Creación (primera versión) del código
// 21/10/2023 - Finalización (última versión) del código

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include "state.h"
#include "alphabet.h"

class Automaton {
 public:
  Automaton() {}
  Automaton(std::ifstream& input_file);
  void SetAlphabet(Alphabet alphabet) { alphabet_ = alphabet; }
  void SetNumberOfStates(int num) { number_of_states_ = num; }
  void SetStates(std::set<State> states) { states_ = states; }
  void SetInitialState(State initial) { initial_state_ = initial; }
  void InsertToFinalStates(State final) { final_states_.insert(final); }
  void InsertActualState(State state) { actual_states_.insert(state); }
  State GetInitialState() const { return initial_state_; }
  std::set<State> GetActualStates() { return actual_states_; }
  Alphabet GetAlphabet() { return alphabet_; }
  std::set<State>& GetStates() { return states_; }
  void Print();
  bool CheckStates();
  bool CheckIfFinalState(const std::set<State>& states);
  // PRÁCTICA 5
    void UpdateActualStates(std::set<State>& actual_states, const char& character);
    bool ProcessStrings(const std::string& string);
  // PRÁCTICA 6
  bool CheckIfBelongsToAlphabet(const char& character);
  bool CheckTransition(const std::string& transition_id);
  std::set<State> EpsilonClosure(const std::set<State>& actual_states);
  std::set<State> Move(const std::set<State>& origin_states, const char& symbol);
  Automaton CreateDFA(std::map<std::string, std::set<State>> states, std::map<std::string, std::multimap<char, std::string>> transitions);
  Automaton TransformToDFA();
  void WriteDFAInOutputFile(std::ostream& output);
 private:
  Alphabet alphabet_;
  int number_of_states_;
  std::set<State> states_;
  State initial_state_;
  std::set<State> final_states_;
  std::set<State> actual_states_;
};

