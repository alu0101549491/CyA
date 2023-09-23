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
  for (auto i : symbols_) {
    std::cout << i << std::endl;
  }
}