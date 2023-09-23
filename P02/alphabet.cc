// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Operaciones con Cadenas
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 22/09/2023
// Archivo alphabet.cc: programa cliente.
// Contiene las definiciones de las funciones y métodos declarados en alphabet.h
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P02
//
// Historial de revisiones
// 22/09/2023 - Creación (primera versión) del código

#include "alphabet.h"

void Alphabet::Insert(const Symbols& symbols) {
  alphabet_.insert(symbols);
}