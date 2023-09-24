// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Operaciones con Cadenas
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 21/09/2023
// Archivo string.h: programa cliente.
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
#include <vector>
#include <string>
#include <set>
#include <unordered_set>
#include "symbol.h"

class String {
 public:
  std::set<Symbol> GetString() { return string_; }
  void SetString(std::set<Symbol> string) { string_ = string; }
  std::set<Symbol> GetAlphabet();
  /*std::set<std::string> Alphabet();
  int Length();
  std::string Inverse();
  std::set<std::string> Prefixes();
  std::set<std::string> Suffixes();
  void Read();
  void Write();*/
  //friend bool operator<(String string_1, String string_2);
  friend bool operator==(String string_1, String string_2);
  friend std::ifstream& operator>>(std::ifstream& input, String string);
  friend std::ostream& operator<<(std::ostream& output, String string);
 private:
  std::set<Symbol> string_;
};

//bool operator<(String string_1, String string_2);
bool operator==(String string_1, String string_2) {
  return string_1.GetString().size() == string_2.GetString().size();
}
std::ifstream& operator>>(std::ifstream& input, String string);
std::ostream& operator<<(std::ostream& output, String string);