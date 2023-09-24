// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Operaciones con Cadenas
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 21/09/2023
// Archivo string.cc: programa cliente.
// Contiene las definiciones de las funciones y métodos declarados en string.h
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P02
//
// Historial de revisiones
// 21/09/2023 - Creación (primera versión) del código

#include "string.h"

Alphabet String::CreateAlphabet() {
  std::set<char> aux_set;
  for (auto i : GetString()) {
    aux_set.insert(i);
  }
  Alphabet alphabet{aux_set};
  return alphabet;
}

String String::InverseString() {
  std::string inverted_string = string_;
  std::reverse(inverted_string.begin(), inverted_string.end());
  String inverted{inverted_string};
  return inverted;
}

Language String::Prefixes() {
  std::set<String> prefixes_set;
  String substring{""};
  prefixes_set.insert(String("&"));
  for (unsigned i = 0; i < string_.length(); ++i) {
    substring.Insert(std::string(1,string_[i]));
    prefixes_set.insert(substring);
  }
  Language prefixes{prefixes_set};
  return prefixes;
}

Language String::Suffixes() {
  std::set<String> suffixes_set;
  String substring{""};
  for (int i = GetLength() - 1; i >= 0; --i) {
    substring.Insert(std::string(1,string_[i]));
    suffixes_set.insert(substring.InverseString());
  }
  suffixes_set.insert(String("&"));
  Language suffixes{suffixes_set};
  return suffixes;
}

bool operator<(String string_1, String string_2) {
  return string_1.GetLength() < string_2.GetLength();
}

std::ifstream& operator>>(std::ifstream& input, String string) {
  std::string text_line;
  std::getline(input, text_line);
  if (text_line != "") {
    for (unsigned i = 0; i < text_line.length(); ++i) {
      std::string character;
      character += text_line[i];
      string.string_ += character;
    }
  }
  return input;
}

std::ostream& operator<<(std::ostream& output, const String& string) {
  output << string.GetString();
  return output;
}