// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Operaciones con Cadenas
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 22/09/2023
// Archivo symbols.cc: programa cliente.
// Contiene las definiciones de las funciones y métodos declarados en symbols.h
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P02
//
// Historial de revisiones
// 22/09/2023 - Creación (primera versión) del código

#include "symbols.h"

Symbols::Symbols(std::string cadena) { 
  for (unsigned i = 0; i < cadena.length(); ++i) {
    symbols_.insert(cadena[i]);
  }
}

bool operator<(Symbols symbols_1, Symbols symbols_2) {
  if (symbols_1.GetSymbols().size() < symbols_2.GetSymbols().size()) {
    return true;
  }
  else {
    return false;
  }
}


std::ostream& operator<<(std::ostream& output, Symbols& symbols) {
  output << "{";
  auto symbolList = symbols.GetSymbols();
  if (!symbolList.empty()) {
    auto it = symbolList.begin();
    output << *it;
    ++it;
    for (it; it != symbolList.end(); ++it) {
      output << ", " << *it;
    }
  }
  output << "}";
  return output;
}