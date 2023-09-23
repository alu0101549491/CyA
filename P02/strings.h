// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Operaciones con Cadenas
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 21/09/2023
// Archivo strings.h: programa cliente.
// Contiene la clase Strings y la declaración de las funciones del programa
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

class Strings {
 public:
  Strings(const std::string& input_file, const std::string& output_file);
  std::unordered_set<std::string> GetStringsSet() { return strings_; }
  std::string GetInputFile() { return input_file_; }
  std::string GetOutputFile() { return output_file_; }
  std::unordered_set<int> Length();
  std::unordered_set<std::string> Inverse();
  std::set<Strings> Prefixes();
  std::set<Strings> Suffixes();
  void Read();
  void Write();
  friend bool operator<(Strings symbols_1, Strings symbols_2);
  friend std::istream& operator>>(std::istream& input, Strings& strings_register);
  friend std::ostream& operator<<(std::ostream& output, Strings& strings_register);
 private:
  std::unordered_set<std::string> strings_;
  std::string input_file_;
  std::string output_file_;
};
bool operator<(Strings symbols_1, Strings symbols_2);
std::istream& operator>>(std::istream& input, Strings& strings_register);
std::ostream& operator<<(std::ostream& output, Strings& strings_register);