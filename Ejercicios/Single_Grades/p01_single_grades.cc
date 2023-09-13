#include "p01_single_grades.h"

/** @brief Imprime en pantalla una breve guía y explicación sobre el funcionamiento del programa */
void Help() {
  std::ifstream input_file{"help.txt"};
  while (input_file) {
    std::string linea_de_texto;
    std::getline(input_file, linea_de_texto);
    std::cout << linea_de_texto << std::endl;
  }
}