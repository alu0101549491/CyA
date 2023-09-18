// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 1: Contenedores asociativos
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 13/09/2023
// Archivo container.h: programa cliente.
// Contiene la clase Container y la declaración de las funciones del programa
// para almacenar a través de un mapa ordenado una serie de datos relacionados
// al identificador de un alumno y su nota final
// Referencias:
// https://github.com/alu0101549491/CyA-P01
//
// Historial de revisiones
// 15/09/2023 - Creación (primera versión) del código
// 15/09/2023 - Finalización (última versión) del código

#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

class Container {
 public:
  void ReadTextFile(const std::string& grades);
  void PrintContainerElements();
  void AddNewData();
 private:
  std::multimap <std::string, double> container_;
};

bool CheckParameters(const int& argc, char* argv[]);
void Help();