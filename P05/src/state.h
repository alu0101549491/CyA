// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 5: Implementación de un simulador de autómatas finitos
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 16/10/2023
// Archivo state.h: programa cliente.
// Contiene la clase State y la declaración de los métodos de la clase
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P05
//
// Historial de revisiones
// 12/10/2023 - Creación (primera versión) del código
// 16/10/2023 - Finalización (última versión) del código

#pragma once

#include "alphabet.h"

class State {
 public:
  State(std::vector<std::string> properties);
  State(std::string state) { state_id_ = state; }
  State() {}
  void SetAlphabet(Alphabet alphabet) { alphabet_ = alphabet; }
  bool GetFinal() const { return final_; }
  std::string GetID() const { return state_id_; }
  std::multimap<std::string, int> GetTransitions() const { return transitions_; }
  friend std::ostream& operator<<(std::ostream& out, const State& state);
  friend bool operator<(const State& state1, const State& state2);
 private:
  std::string state_id_;
  Alphabet alphabet_;
  bool final_;
  int number_of_transitions_;
  std::multimap<std::string, int> transitions_;
};
