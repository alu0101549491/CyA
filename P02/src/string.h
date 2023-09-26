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
// 24/09/2023 - Finalización (última versión) del código
// 26/09/2023 - Modificación de la práctica

#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <unordered_set>
#include "language.cc"
#include "alphabet.cc"

class String {
 public:
  String(std::string string);
  std::string GetString() const;
  void Insert(std::string string);
  Alphabet CreateAlphabet();
  int GetLength();
  String InverseString();
  Language Prefixes();
  Language Suffixes();
  String Power(int n);
  friend bool operator<(String string_1, String string_2);
  friend bool operator==(String string_1, String string_2);
  friend std::ifstream& operator>>(std::ifstream& input, String string);
  friend std::ostream& operator<<(std::ostream& output, const String& string);
 private:
  std::string string_;
};

bool operator==(String string_1, String string_2);
bool operator<(String string_1, String string_2);
std::ifstream& operator>>(std::ifstream& input, String string);
std::ostream& operator<<(std::ostream& output, const String& string);