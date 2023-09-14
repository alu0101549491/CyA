// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 1: Contenedores asociativos
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 13/09/2023
// Archivo P01-single-grades.cc: programa cliente.
// Contiene la clase Contenedor y la declaración de las funciones del programa
// para ... (indicar brevemente el objetivo)
// Referencias:
// https://github.com/alu0101549491/CyA-P01
//
// Historial de revisiones
// 13/09/2023 - Creación (primera versión) del código

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>

class Container {
 public:
  void ReadTextFile(const std::string& grades);
  void PrintContainerElements();
 private:
  std::map <std::string, double> container_;
};

bool CheckParameters(const int& argc, char* argv[]);
void Help();