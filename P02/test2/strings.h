// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Operaciones con Cadenas
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 21/09/2023
// Archivo String.h: programa cliente.
// Contiene la clase String y la declaración de las funciones del programa
// para realizar operaciones con distintas cadenas
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P02
//
// Historial de revisiones
// 21/09/2023 - Creación (primera versión) del código

#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <set>
#include <unordered_set>

class String {
 public:
  String(const std::string& input_file, const std::string& output_file);
  std::unordered_set<std::string> GetStringSet() { return String_; }
  std::string GetInputFile() { return input_file_; }
  std::string GetOutputFile() { return output_file_; }
  std::set<std::string> Alphabet(const std::string& string);
  std::unordered_set<int> Length();
  std::string Inverse(std::string string);
  std::set<std::string> Prefixes(const std::string& string);
  std::set<std::string> Suffixes(const std::string& string);
  void Read();
  void Write();
  friend bool operator<(String string_1, String string_2);
  friend std::istream& operator>>(std::istream& input, String& String_register);
  friend std::ostream& operator<<(std::ostream& output, String& String_register);
 private:
  std::unordered_set<std::string> String_;
  std::string input_file_;
  std::string output_file_;
};

bool operator<(String string_1, String string_2);
std::istream& operator>>(std::istream& input, String& String_register);
std::ostream& operator<<(std::ostream& output, String& String_register);