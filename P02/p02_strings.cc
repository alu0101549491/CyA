// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Operaciones con Cadenas
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 21/09/2023
// Archivo p02_strings.cc: programa cliente.
// Contiene la función main del proyecto que usa la clase Strings
// para procesar un fichero que contiene cadenas e imprimir los 
// resultados en un fichero de salida
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P02
//
// Historial de revisiones
// 21/09/2023 - Creación (primera versión) del código

#include "strings.h"
#include "strings.cc"

int main(int argc, char* argv[]) {
  if (CheckParameters(argc, argv)) {
    std::string input_file = argv[1];
    std::string output_file = argv[2];
    Strings strings_register(input_file, output_file);
    std::cin >> strings_register;
    switch (std::stoi(argv[3])) {
      case 1:
        strings_register.MakeAlphabet();
        break;
      case 2:
        strings_register.MakeLength();
        break;
      case 3:
        strings_register.MakeInverse();
        break;
      case 4:
        strings_register.MakePrefixes();
        break;
      case 5:
        strings_register.MakeSuffixes();
        break;
      default:
        std::cout << "La opción elegida no es correcta" << std::endl;
        return 1;
    }
    std::cout << strings_register;
    return 0;
  }
  else {
    return 1;
  }
}