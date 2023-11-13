// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 9: Implementación de un simulador de Máquinas de Turing
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 07/11/2023
// Archivo turing_machine.h: programa cliente.
// Contiene la clase TuringMachine y la declaración de las funciones del programa
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P09
//
// Historial de revisiones
// 07/11/2023 - Creación (primera versión) del código
// 08/11/2023 - Finalización (última versión) del código

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <tuple>

#include "state.h"
#include "state.cc"
#include "alphabet.h"

class TuringMachine {
 public:
  TuringMachine(const std::string& input, const std::string& tape);
  void PrintTuringMachine();
  bool AlreadyInStates(const std::string& state);
  bool MachineStop(const State& actual_state);
  bool ProcessTape();
  std::tuple<std::string, char, char> Move(const State& actual_state, char symbol) const { return actual_state.GetTuple(symbol); };
  friend std::ostream& operator<<(std::ostream& out, TuringMachine m1);
 private:
  int number_of_states_;
  int number_of_tuples_;
  std::set<State> states_;
  Alphabet tape_alphabet_;
  Alphabet input_alphabet_;
  std::string tape_;
  State initial_state_;
  std::set<State> final_states_;
};

