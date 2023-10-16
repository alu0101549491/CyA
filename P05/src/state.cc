// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 5: Implementación de un simulador de autómatas finitos
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 16/10/2023
// Archivo state.cc: programa cliente.
// Contiene las definiciones de las funciones y métodos declarados en state.h
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P05
//
// Historial de revisiones
// 12/10/2023 - Creación (primera versión) del código
// 16/10/2023 - Finalización (última versión) del código

#include "state.h"

/** @brief Constructor de la clase State al que se le pasa una serie de propiedades
 *         cuyo orden viene dado por la sintaxis aceptada en los ficheros .fa por defecto
 *         adaptado para ser utilizado por el constructor de la clase Automaton
 *  @param[in] properties. Vector que contiene todas las propiedades del estado
 */
State::State(std::vector<std::string> properties) {
  state_id_ = properties[0];
  final_ = std::stoi(properties[1]);
  number_of_transitions_ = std::stoi(properties[2]);
  for (unsigned i = 3; i < properties.size(); i += 2) {
    int j = i + 1;
    std::pair<std::string, int> transition(properties[i], std::stoi(properties[j]));
    transitions_.insert(transition);
  }
}

/** @brief Sobrecarga del operador de extracción para la clase State
 *  @param[in] out. Flujo de salida
 *  @param[in] state. Objeto de la clase State que se va a imprimir
 *  @return Devuelve el flujo de salida
 */
std::ostream& operator<<(std::ostream& out, const State& state) {
  out << "~~~ State ID ~~~\n";
  out << state.state_id_ << std::endl;
  out << "~~~ Alphabet ~~~\n";
  out << state.alphabet_ << std::endl;
  out << "~~~ Is a Final State? ~~~\n";
  if (state.final_ == 1) {
    out << "YES" << std::endl;
  }
  else {
    out << "NO" << std::endl;
  }
  out << "~~~ Number of Transitions ~~~\n";
  out << state.number_of_transitions_ << std::endl;
  out << "~~~ Transitions ~~~\n";
  for (auto i : state.transitions_) {
    out << i.first << ": " << state.state_id_ << " --> " << i.second << std::endl;
  }
  return out;
}

/** @brief Sobrecarga del operador de comparación "<"
 *  @param[in] state1. Estado 1
 *  @param[in] state2. Estado 2
 *  @return Devuelve la comparación de los estados en base a su ID
 */
bool operator<(const State& state1, const State& state2) {
  return state1.state_id_ < state2.state_id_;
}