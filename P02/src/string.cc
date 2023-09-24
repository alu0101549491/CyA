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


std::set<Symbol> String::GetAlphabet() {
  std::set<Symbol> alphabet;
  for (auto i : GetString()) {
    std::string aux;
    aux += i.GetSymbol();
    alphabet.insert(aux);
  }
  return alphabet;
}
/*
std::unordered_set<int> String::Length() {
  std::unordered_set<int> length;
  for (auto i : GetStringSet()) {
    int counter{0};
    for (unsigned j = 0; j < i.length(); ++j) {
      counter++;
    }
    length.insert(counter);
  }
  return length;
}

std::string String::Inverse(std::string string) {
  std::reverse(string.begin(), string.end());
  return string;
}

std::set<std::string> String::Prefixes(const std::string& string) {
  std::set<std::string> prefixes;
  std::string substring = "";
  prefixes.insert("&");
  for (unsigned i = 0; i < string.length(); ++i) {
    substring += string[i];
    prefixes.insert(substring);
  }
  return prefixes;
}

std::set<std::string> String::Suffixes(const std::string& string) {
  std::set<std::string> suffixes;
  std::string substring = "";
  for (int i = string.length() - 1; i >= 0; --i) {
    substring += string[i];
    suffixes.insert(Inverse(substring));
  }
  suffixes.insert("&");
  return suffixes;
}



bool operator<(String string_1, String string_2) {
  
}
*/
std::ifstream& operator>>(std::ifstream& input, String string) {
  std::string text_line;
  std::getline(input, text_line);
  if (text_line != "") {
    for (unsigned i = 0; i < text_line.length(); ++i) {
      std::string character;
      character += text_line[i];
      Symbol symbol = character;
      string.GetString().insert(symbol);
    }
  }
  return input;
}

std::ostream& operator<<(std::ostream& output, String string) {
  for (auto i : string.GetString()) {
    output << i;
  }
}