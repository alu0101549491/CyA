// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Operaciones con Cadenas
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 21/09/2023
// Archivo strings.cc: programa cliente.
// Contiene las definiciones de las funciones y métodos declarados en strings.h
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P02
//
// Historial de revisiones
// 21/09/2023 - Creación (primera versión) del código

#include "strings.h"

Strings::Strings(const std::string& input_file, const std::string& output_file) { 
  input_file_ = input_file; 
  output_file_ = output_file; 
}

void Strings::Read() {
  std::ifstream input_file{GetInputFile()};
  while (input_file) {
    std::string text_string;
    std::getline(input_file, text_string);
    if (text_string != "") {
      strings_.insert(text_string);
    }
  }
}

void Strings::Write() {
  
}

std::istream& operator>>(std::istream& input, Strings& strings_register) {
  strings_register.Read();
}

std::ostream& operator<<(std::ostream& output, Strings& strings_register) {
  strings_register.Write();
}