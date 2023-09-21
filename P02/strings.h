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
#include <string>
#include <set>

class Strings {
 public:
  Strings(const std::string& input_file, const std::string& output_file) { input_file_ = input_file; output_file_ = output_file; }
  std::string GetInputFile() { return input_file_; }
  std::string GetOutputFile() { return output_file_; }
  void ReadFile(const std::string& file);
  void WriteFile(const std::string& file);
  Strings MakeAlphabet();
  Strings MakeLength();
  Strings MakeInverse();
  Strings MakePrefixes();
  Strings MakeSuffixes();
  friend std::istream& operator>>(std::istream& input, Strings& strings_register);
  friend std::ostream& operator<<(std::ostream& output, Strings& strings_register);
 private:
  std::set<std::string> strings_;
  std::string input_file_;
  std::string output_file_;
};

std::istream& operator>>(std::istream& input, Strings& strings_register) {
  strings_register.ReadFile(strings_register.GetInputFile());
}

std::ostream& operator<<(std::ostream& output, Strings& strings_register) {
  strings_register.WriteFile(strings_register.GetOutputFile());
}

bool CheckParameters(const int& argc, char* argv[]);
void Help();