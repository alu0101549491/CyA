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
// Contiene la función main del proyecto que usa las clases X e Y
// para ... (indicar brevemente el objetivo)
// Referencias:
// https://github.com/alu0101549491/CyA-P01
//
// Historial de revisiones
// 13/09/2023 - Creación (primera versión) del código


#include "p01_single_grades.h"
#include "p01_single_grades.cc"

/** @brief Main function
 *  @param[in] argc Number of command line parameters
 *  @param[in] argv Vector containing (char*) the parameters
 */
int main(int argc, char* argv[]) {
  std::string main_parameter = argv[1];
  if (argc <= 1) {
    std::cout << "Modo de empleo: ./p01_single_grades grades.txt" << std::endl;
    std::cout << "Pruebe 'p01_single_grades --help' para más información" << std::endl;
    return 0;
  }
  if (main_parameter == "--help") {
    Help();
    return 0;
  }
  else {
    
  }
}