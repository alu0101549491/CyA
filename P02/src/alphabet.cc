// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Operaciones con Cadenas
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 24/09/2023
// Archivo alphabet.cc: programa cliente.
// Contiene las definiciones de las funciones y métodos declarados en alphabet.h
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P02
//
// Historial de revisiones
// 23/09/2023 - Creación (primera versión) del código
// 24/09/2023 - Finalización (última versión) del código

#include "alphabet.h"

/** @brief Constructor de la clase Alphabet
  * @param[in] alphabet. Set de tipo clase char cuyos valores serán copiados al atributo de la clase Alphabet
  */
Alphabet::Alphabet(std::set<char> alphabet) { 
  alphabet_ = alphabet;
}

/** @brief Getter del atributo de la clase Alphabet
  * @return Devuelve el valor 
  */
std::set<char> Alphabet::GetAlphabet() { 
  return alphabet_;
}

/** @brief Sobrecarga del operador de extracción
  * @param[in] output. Flujo de salida
  * @param[in] alphabet. Objeto de tipo Alphabet para imprimir en el flujo de salida
  * @return Devuelve el flujo de salida dado a la función
  */
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
}