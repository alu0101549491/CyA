// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Convertir un NFA en un DFA
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 18/10/2023
// Archivo main.cc: programa cliente.
// Contiene la función main del proyecto que usa la clase Automaton
// para convertir un NFA en un DFA
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P06
//
// Historial de revisiones
// 18/10/2023 - Creación (primera versión) del código
// 21/10/2023 - Finalización del código


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
    std::cout << "Modo de empleo: ./NFA2DFA input.nfa output.dfa" << std::endl;
    std::cout << "Pruebe './NFA2DFA --help' para más información." << std::endl;
    return false;
  }
  if (argc < 3 || argc > 3) {
    if (std::string(argv[1]) == "--help") {
      Help();
      return false;
    }
    else {
      std::cout << "Modo de empleo: ./NFA2DFA input.nfa output.dfa" << std::endl;
      std::cout << "Pruebe './NFA2DFA --help' para más información." << std::endl;
      return false;
    }
  }
  else {
    std::ifstream input{argv[1]};
    std::ifstream output{argv[2]};
    if (input.fail() || output.fail()) {
      std::cout << "No se ha encontrado el fichero introducido" << std::endl;
      return false;
    }
    else {
      return true;
    }
  }
}

/** @brief Revisa que si los simbolos de una cadena pertenecen al alfabeto dado
  * @param[in] string. Cadena a revisar
  * @param[in] alphabet. Alfabeto dado
  * @return Valor booleano que determina si la cadena pertenece o no al alfabeto
  */
bool CheckAlphabet(std::string string, Alphabet alphabet) {
  unsigned counter = 0;
  for (auto i : string) {
    for (auto j : alphabet.GetSet()) {
      if (i == j) {
        counter++;
      }
    }
  }
  if (counter == string.length()) {
    return true;
  }
  return false;
}

/** @brief Main function
 *  @param[in] argc Number of command line parameters
 *  @param[in] argv Vector containing (char*) the parameters
 */
int main(int argc, char* argv[]) {
  if (CheckParameters(argc, argv)) {
    std::ifstream nfa_file{std::string(argv[1])};
    std::ofstream dfa_file{std::string(argv[2])};
    Automaton NFA{nfa_file};
    if (NFA.CheckStates()) {
      //NFA.Print();
      Automaton DFA = NFA.TransformToDFA();
      //DFA.Print();
      DFA.WriteDFAInOutputFile(dfa_file);
    }
    return 0;
  }
  else {
    return 1;
  }
}