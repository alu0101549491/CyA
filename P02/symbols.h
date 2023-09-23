// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Operaciones con Cadenas
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 22/09/2023
// Archivo symbols.h: programa cliente.
// Contiene la clase Symbols y la declaración de las funciones del programa
// para realizar operaciones con distintas cadenas
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P02
//
// Historial de revisiones
// 22/09/2023 - Creación (primera versión) del código

#pragma once
#include "strings.h"

class Symbols {
 public:
  Symbols(std::string cadena);
  void Read();
  void Write();
 private:
  std::set <char> symbols_;
};

Symbols operator<(Symbols symbols_1, Symbols symbols_2) {
  
}