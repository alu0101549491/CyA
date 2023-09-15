// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 1: Contenedores asociativos
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 13/09/2023
// Archivo p01-multiple-grades.cc: programa cliente.
// Contiene la función main del proyecto que usa la clase Container
// para procesar un fichero de texto con identificadores de alumnos y sus notas
// Referencias:
// https://github.com/alu0101549491/CyA-P01
//
// Historial de revisiones
// 15/09/2023 - Creación (primera versión) del código
// 15/09/2023 - Finalización (última versión) del código

#include "container.h"
#include "container.cc"

/** @brief Main function
 *  @param[in] argc Number of command line parameters
 *  @param[in] argv Vector containing (char*) the parameters
 */
int main(int argc, char* argv[]) {
  if (CheckParameters(argc, argv)) {
    Container grades_register;
    std::string grades = argv[1];
    grades_register.ReadTextFile(grades);
    grades_register.PrintContainerElements();
    while (true) {
      std::cout << "¿Desea añadir otro dato? (y/n): ";
      char decision;
      std::cin >> decision;
      if (decision == 'y') {
        grades_register.AddNewData();
        grades_register.PrintContainerElements();
      }
      else {
        if (decision == 'n') {
          break;
        }
        else {
          std::cout << "Opción incorrecta, vuélvalo a intentar." << std::endl;
        }
      }
    }
    return 0;
  }
  else {
    return 1;
  }
}