// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Convertir un NFA en un DFA
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 18/10/2023
// Archivo state.h: programa cliente.
// Contiene la clase State y la declaración de los métodos de la clase
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P06
//
// Historial de revisiones
// 18/10/2023 - Creación (primera versión) del código
// 21/10/2023 - Finalización (última versión) del código

#pragma once

#include "alphabet.h"

class State {
 public:
  State(const std::vector<std::string>& properties);
  State(const State& state);
  State(const std::string& state) { state_id_ = state; }
  State() {}
  void SetAlphabet(Alphabet alphabet) { alphabet_ = alphabet; }
  void SetIfFinal(bool final) { final_ = final; }
  void SetNumberOfTransitions(const int& num) { number_of_transitions_ = num; }
  void SetTransitionMap(std::multimap<char,std::string> transitions) { transitions_ = transitions; }
  void SetTransition(std::pair<char,std::string> transition) { transitions_.insert(transition); number_of_transitions_++; }
  std::string GetID() const { return state_id_; }
  Alphabet GetAlphabet() const { return alphabet_; }
  bool GetFinal() const { return final_; }
  int GetNumberOfTransitions() const { return number_of_transitions_; }
  std::multimap<char, std::string> GetTransitions() const { return transitions_; }
  friend std::ostream& operator<<(std::ostream& out, const State& state);
  friend bool operator<(const State& state1, const State& state2);
  friend bool operator==(const State& state1, const State& state2);
 private:
  std::string state_id_;
  Alphabet alphabet_;
  bool final_;
  std::multimap<char, std::string> transitions_;
  int number_of_transitions_;
};
