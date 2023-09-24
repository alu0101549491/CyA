// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Operaciones con Cadenas
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 24/09/2023
// Archivo alphabet.h: programa cliente.
// Contiene la clase Alphabet y la declaración de las funciones del programa
// para realizar operaciones con distintas cadenas
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P02
//
// Historial de revisiones
// 24/09/2023 - Creación (primera versión) del código

#pragma once
#include "string.h"

class Alphabet {
 public:
  Alphabet(std::set<char> alphabet) { alphabet_ = alphabet; }
  std::set<char> GetAlphabet() { return alphabet_; }
  friend std::ostream& operator<<(std::ostream& output, Alphabet alphabet);
 private:
  std::set<char> alphabet_;
};

std::ostream& operator<<(std::ostream& output, Alphabet alphabet) {
  std::set<char> my_alphabet_set = alphabet.GetAlphabet();
  output << "{";
  for (auto it = my_alphabet_set.begin(); it != my_alphabet_set.end(); ++it) {
    output << *it;
    if (std::next(it) != my_alphabet_set.end()) {
      output << ", ";
    }
  }
  output << "}";
  return output;
};
