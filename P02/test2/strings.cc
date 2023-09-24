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

String::String(const std::string& input_file, const std::string& output_file) { 
  input_file_ = input_file; 
  output_file_ = output_file; 
}

std::set<std::string> String::Alphabet(const std::string& string) {
  std::set<std::string> alphabet;
  for (auto i : string) {
    std::string aux;
    aux += i;
    alphabet.insert(aux);
  }
  return alphabet;
}

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

void String::Read() {
  std::ifstream input_file{GetInputFile()};
  while (input_file) {
    std::string text_string;
    std::getline(input_file, text_string);
    if (text_string != "") {
      String_.insert(text_string);
    }
  }
}

void String::Write() {
  std::ofstream output_file{GetOutputFile()};
  std::unordered_set<std::string> string_set {GetStringSet()};
  output_file << "{";
  if (!string_set.empty()) {
    auto it = string_set.begin();
    output_file << *it;
    ++it;
    for (it; it != string_set.end(); ++it) {
      output_file << ", " << *it;
    }
  }
  output_file << "}" << std::endl;
}

bool operator<(String string_1, String string_2) {
  
}

std::istream& operator>>(std::istream& input, String& String_register) {
  String_register.Read();
}

std::ostream& operator<<(std::ostream& output, String& String_register) {
  String_register.Write();
}