// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Operaciones con Cadenas
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 24/09/2023
// Archivo symbol.h: programa cliente.
// Contiene la clase Symbol y la declaración de las funciones del programa
// para realizar operaciones con distintas cadenas
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P02
//
// Historial de revisiones
// 21/09/2023 - Creación (primera versión) del código

#pragma once
#include "string.h"

class Symbol {
 public:
  Symbol(std::string symbol) { symbol_ = symbol; }
  std::string GetSymbol() { return symbol_; }
  friend std::ofstream& operator<<(std::ofstream& output, Symbol symbol);
 private:
  std::string symbol_;
};

bool operator<(Symbol symbol_1, Symbol symbol_2) {
  return (symbol_1.GetSymbol().length() < symbol_2.GetSymbol().length());
}
std::ostream& operator<<(std::ostream& output, Symbol symbol) {
  output << symbol.GetSymbol();
  return output;
}