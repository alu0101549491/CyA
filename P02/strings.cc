// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Operaciones con Cadenas
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 21/09/2023
// Archivo strings.cc: programa cliente.
// Contiene las definiciones de las funciones y métodos declarados en strings.h
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P02
//
// Historial de revisiones
// 21/09/2023 - Creación (primera versión) del código

#include "strings.h"

Strings::Strings(const std::string& input_file, const std::string& output_file) { 
  input_file_ = input_file; 
  output_file_ = output_file; 
}

std::unordered_set<int> Strings::Length() {
  std::unordered_set<int> length;
  for (auto i : GetStringsSet()) {
    int counter{0};
    for (unsigned j = 0; j < i.length(); ++j) {
      counter++;
    }
    length.insert(counter);
  }
  return length;
}

std::unordered_set<std::string> Strings::Inverse() {
  std::unordered_set<std::string> inverted_strings;
  for (auto i : GetStringsSet()) {
    std::reverse(i.begin(), i.end());
    inverted_strings.insert(i);
  }
  return inverted_strings;
}

std::set<Strings> Strings::Prefixes() {
  std::set<Strings> prefixes_of_strings;
  for (auto i : GetStringsSet()) {
    Strings prefixes("","");
    std::string substring;
    prefixes.GetStringsSet().insert("ε");
    for (auto j : i) {
      substring += j;
      prefixes.GetStringsSet().insert(substring);
    }
    prefixes_of_strings.insert(prefixes);
  }
  return prefixes_of_strings;
}
std::set<Strings> Strings::Suffixes() {

}

void Strings::Read() {
  std::ifstream input_file{GetInputFile()};
  while (input_file) {
    std::string text_string;
    std::getline(input_file, text_string);
    if (text_string != "") {
      strings_.insert(text_string);
    }
  }
}

void Strings::Write() {
  for (auto i : GetStringsSet()) {
    std::cout << i << std::endl;
  }
}

bool operator<(Strings symbols_1, Strings symbols_2) {
  if (symbols_1.GetStringsSet().size() < symbols_2.GetStringsSet().size()) {
    return true;
  }
  else {
    return false;
  }
}

std::istream& operator>>(std::istream& input, Strings& strings_register) {
  strings_register.Read();
}

std::ostream& operator<<(std::ostream& output, Strings& strings_register) {
  strings_register.Write();
}