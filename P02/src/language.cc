// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Operaciones con Cadenas
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 24/09/2023
// Archivo language.cc: programa cliente.
// Contiene las definiciones de las funciones y métodos declarados en language.h
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P02
//
// Historial de revisiones
// 24/09/2023 - Creación (primera versión) del código
// 24/09/2023 - Finalización (última versión) del código

#include "language.h"

/** @brief Constructor de la clase Language
  * @param[in] language. Set de tipo clase String cuyos valores serán copiados al atributo de la clase Language
  */
Language::Language(std::set<String> language) {
  language_ = language; 
}

/** @brief Método que devuelve el valor del tamaño del set
  * @return Devuelve el número de elementos que tiene el set
  */
int Language::LanguageSize() { 
  return language_.size(); 
}

/** @brief Getter del atributo de la clase Language
  * @return Devuelve el atributo de la clase
  */
std::set<String> Language::GetLanguage() {
  return language_;
}