// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Operaciones con Cadenas
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 24/09/2023
// Archivo language.h: programa cliente.
// Contiene la clase Language y la declaración de las funciones del programa
// para realizar operaciones con distintas cadenas
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P02
//
// Historial de revisiones
// 24/09/2023 - Creación (primera versión) del código

#pragma once
#include "string.h"

class String;
class Language {
 public:
  Language(std::set<String> language) { language_ = language; }
  int LanguageSize() { return language_.size(); }
  void Write(std::ostream& output);
  std::set<String> GetLanguage() { return language_; }
 private:
  std::set<String> language_;
};

void Language::Write(std::ostream& output) {
  output << "{";
  int counter = 0;
  for (auto i : GetLanguage()) {
    output << i;
    if (counter != LanguageSize() - 1) {
      output << ", ";
    }
    counter++;
  }
  output << "}" << std::endl;
}