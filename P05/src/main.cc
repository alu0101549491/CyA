// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 5: Implementación de un simulador de autómatas finitos
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 16/10/2023
// Archivo main.cc: programa cliente.
// Contiene la función main del proyecto que usa la clase Automaton
// para procesar un fichero que contiene cadenas e imprimir los 
// resultados en pantalla
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P05
//
// Historial de revisiones
// 12/10/2023 - Creación (primera versión) del código
// 16/10/2023 - Finalización del código


#include "automaton.h"
#include "automaton.cc"
#include "state.h"
#include "state.cc"

/** @brief Imprime en pantalla una breve guía y explicación sobre el funcionamiento del programa */
void Help() {
  std::ifstream input_file{"help.txt"};
  while (input_file) {
    std::string text_line;
    std::getline(input_file, text_line);
    std::cout << text_line << std::endl;
  }
}

/** @brief Revisa que los parámetros introducidos al programa funcionen correctamente y no generen errores
  * @param[in] argc. Número de parámetros pasados al programa a través de la terminal
  * @param[in] argv. Vector de char* que contiene los parámetros pasados al programa
  * @return Valor booleano que determina si el parámetro que se le pasó al programa es correcto y se puede proseguir
  */
bool CheckParameters(const int& argc, char* argv[]) {
  if (argc == 1) {
    std::cout << "Modo de empleo: ./p05_automata_simulator input.fa input.txt" << std::endl;
    std::cout << "Pruebe './p05_automata_simulator --help' para más información." << std::endl;
    return false;
  }
  if (argc < 3 || argc > 3) {
    if (std::string(argv[1]) == "--help") {
      Help();
      return false;
    }
    else {
      std::cout << "Modo de empleo: ./p05_automata_simulator input.fa input.txt" << std::endl;
      std::cout << "Pruebe './p05_automata_simulator --help' para más información." << std::endl;
      return false;
    }
  }
  else {
    std::ifstream input1{argv[1]};
    std::ifstream input2{argv[2]};
    if (input1.fail() || input2.fail()) {
      std::cout << "No se ha encontrado el fichero introducido" << std::endl;
      return false;
    }
    else {
      return true;
    }
  }
}

/** @brief Main function
 *  @param[in] argc Number of command line parameters
 *  @param[in] argv Vector containing (char*) the parameters
 */
int main(int argc, char* argv[]) {
  if (CheckParameters(argc, argv)) {
    std::ifstream nfa_file{std::string(argv[1])};
    std::ifstream strings_file{std::string(argv[2])};
    Automaton NFA{nfa_file};
    //NFA.Print();
    while (strings_file) {
      std::string text_line;
      std::getline(strings_file, text_line);
      if (!text_line.empty()) {
        //text_line.erase(text_line.rfind('\r'));
        if (NFA.ProcessStrings(text_line)) {
          std::cout << text_line << " --- Accepted" << std::endl;
        }
        else {
          std::cout << text_line << " --- Rejected" << std::endl;
        }
      }
    }
    return 0;
  }
  else {
    return 1;
  }
}