// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 9: Implementación de un simulador de Máquinas de Turing
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 07/11/2023
// Archivo state.h: programa cliente.
// Contiene la clase State y la declaración de los métodos de la clase
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P09
//
// Historial de revisiones
// 07/11/2023 - Creación (primera versión) del código
// 08/11/2023 - Finalización (última versión) del código

#pragma once

#include "alphabet.h"

class State {
 public:
  State(const std::string& state) { state_id_ = state; }
  State() {}
  std::string GetID() const { return state_id_; }
  void SetIfFinal(bool final) { final_ = final; }
  bool GetIfFinal() const { return final_; }
  void InsertTuple(std::pair<char, std::tuple<std::string, char, char>> tuple) { tuples_.insert(tuple); number_of_tuples_ = tuples_.size(); }
  std::tuple<std::string, char, char> GetTuple(const char& key) const;
  std::map<char, std::tuple<std::string, char, char>> GetTupleMap() const { return tuples_; }
  friend bool operator<(const State& state1, const State& state2);
  friend bool operator==(const State& state1, const State& state2);
  friend std::ostream& operator<<(std::ostream& out, const State& state);
 private:
  std::string state_id_;
  bool final_;
  std::map<char, std::tuple<std::string, char, char>> tuples_;
  int number_of_tuples_;
};