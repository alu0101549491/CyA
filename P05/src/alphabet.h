// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 5: Implementación de un simulador de autómatas finitos
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 16/10/2023
// Archivo alphabet.h: programa cliente.
// Contiene la clase Alphabet y la declaración de las funciones del programa
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P05
//
// Historial de revisiones
// 12/10/2023 - Creación (primera versión) del código
// 16/10/2023 - Finalización (última versión) del código

#pragma once

class Alphabet {
 public:
  void Insert(char symbol) { alphabet_.insert(symbol); }
  friend std::ostream& operator<<(std::ostream& out, const Alphabet& alphabet);
 private:
  std::set<char> alphabet_;
};

/** @brief Sobrecarga del operador de extracción para la clase Alphabet
 *  @param[in] out. Flujo de salida
 *  @param[in] alphabet. Objeto de la clase Alphabet que se va a imprimir
 *  @return Devuelve el flujo de salida
 */
std::ostream& operator<<(std::ostream& out, const Alphabet& alphabet) {
  for (auto it = alphabet.alphabet_.begin(); it != alphabet.alphabet_.end(); ++it) {
    out << *it << " ";
  }
  return out;
}