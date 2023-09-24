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
#include "language.h"
#include "alphabet.h"

class String {
 public:
  String(std::string string) { string_ = string; }
  std::string GetString() const { return string_; }
  void SetString(std::string string) { string_ = string; }
  void Insert(std::string string) { string_ += string; }
  Alphabet CreateAlphabet();
  int GetLength() { return string_.length(); }
  String InverseString();
  Language Prefixes();
  Language Suffixes();
  //friend bool operator<(String string_1, String string_2);
  friend bool operator==(String string_1, String string_2);
  friend std::ifstream& operator>>(std::ifstream& input, String string);
  friend std::ostream& operator<<(std::ostream& output, const String& string);
 private:
  std::string string_;
};

//bool operator<(String string_1, String string_2);
bool operator==(String string_1, String string_2) {
  return string_1.GetString().size() == string_2.GetString().size();
}

std::ifstream& operator>>(std::ifstream& input, String string);
std::ostream& operator<<(std::ostream& output, const String& string);