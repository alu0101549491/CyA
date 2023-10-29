// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 7: Gramáticas en Forma Normal de Chomsky
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 26/10/2023
// Archivo main.cc: programa cliente.
// Contiene la función main del proyecto que usa la clase Grammar
// para convertir una gramática a FNC
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P07
//
// Historial de revisiones
// 26/10/2023 - Creación (primera versión) del código
// 29/10/2023 - Finalización (última versión) del código


#include "grammar.h"
#include "grammar.cc"

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
    std::cout << "Modo de empleo: ./Grammar2CNF input.gra output.gra" << std::endl;
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

/** @brief Imprime un mensaje de error dado para el cierre del programa
  * @param[in] error_message. Mensaje de error
  */
void ErrorExit(const std::string& error_message) {
  std::cout << "Grammar2CNF: " << error_message << std::endl;
  std::cout << "Consulte './Grammar2CNF --help' para más información" << std::endl;
  std::cerr << std::endl;
  return;
}

/** @brief Revisa que todo en el fichero de texto esté correcto
  * @param[in] input. Nombre del fichero de texto
  * @return Si está todo en orden devuelve true, en caso contrario, false
  */
bool CheckFile(const std::string& input) {
  std::ifstream input_file{input};
  std::string text_line;
  int num_terminals;
  int num_nonterminals;
  int num_productions;
  std::getline(input_file, text_line);
  try {
    num_terminals = std::stoi(text_line);
  } catch (const std::invalid_argument& error) {
    ErrorExit("El fichero input.gra contiene fallos al declarar el número de terminales");
    input_file.close();
    return false;
  }
  for (int i = 0; i < num_terminals; ++i) {
    std::getline(input_file, text_line);
    if (text_line.length() > 2) {
      ErrorExit("Los símbolos terminales deben tener un solo caracter");
      input_file.close();
      return false;
    }
    if (text_line[0] < 'a' || text_line[0] > 'z') {
      ErrorExit("Los terminales por convenio deberían ser símbolos del alfabeto latino en minúscula, compruebe si se introdujo un caracter erroneo o una cantidad de terminales menor o mayor a la especificada");
      input_file.close();
      return false;
    }
  }
  std::getline(input_file, text_line);
  try {
    num_nonterminals = std::stoi(text_line);
  } catch (const std::invalid_argument& error) {
    ErrorExit("El fichero input.gra contiene fallos al declarar el número de no-terminales");
    input_file.close();
    return false;
  }
  for (int j = 0; j < num_nonterminals; ++j) {
    std::getline(input_file, text_line);
    if (text_line.length() > 2) {
      ErrorExit("Los símbolos no-terminales deben tener un solo caracter");
      input_file.close();
      return false;
    }
    if (text_line[0] < 'A' || text_line[0] > 'Z') {
      ErrorExit("Los no-terminales por convenio deberían ser símbolos del alfabeto latino en mayúscula, compruebe si se introdujo un caracter erroneo o una cantidad de no-terminales menor o mayor a la especificada");
      input_file.close();
      return false;
    }
  }
  std::getline(input_file, text_line);
  try {
    num_productions = std::stoi(text_line);
  } catch (const std::invalid_argument& error) {
    ErrorExit("El fichero input.gra contiene fallos al declarar el número de producciones");
    input_file.close();
    return false;
  }
  for (int k = 0; k < num_productions; ++k) {
    std::getline(input_file, text_line);
    std::string origin, production;
    std::stringstream splitted_line(text_line);
    splitted_line >> origin, splitted_line >> production;
    if (!origin.empty() && !production.empty()) {
      if (origin.length() > 2) {
        ErrorExit("Los símbolos no-terminales deben tener un solo caracter");
        input_file.close();
        return false;
      }
      if (origin[0] < 'A' || origin[0] > 'Z') {
        ErrorExit("Los no-terminales por convenio deberían ser símbolos del alfabeto latino en mayúscula, compruebe si se introdujo un caracter erroneo o una cantidad de no-terminales menor o mayor a la especificada");
        input_file.close();
        return false;
      }
    }
    else {
      ErrorExit("Se encontró un fallo en una de las lineas de producción, compruebe si no hay ninguna linea vacía y que el no-terminal origen esté separado de la producción por un espacio");
      input_file.close();
      return false;
    }
  }
  input_file.close();
  return true;
}

/** @brief Main function
 *  @param[in] argc Number of command line parameters
 *  @param[in] argv Vector containing (char*) the parameters
 */
int main(int argc, char* argv[]) {
  if (CheckParameters(argc, argv)) {
    std::string input_file = argv[1];
    std::ofstream output_file{std::string(argv[2])};
    if (CheckFile(input_file)) {
      Grammar standard_grammar{input_file};
      //standard_grammar.Print();
      if (!standard_grammar.CheckIfEmptyProductions() && !standard_grammar.CheckIfUnitaryProductions()) {
        standard_grammar.ConvertToCNF();
        standard_grammar.Print();
        output_file << standard_grammar;
        return 0;
      }
      else {
        std::cerr << "No se puede producir una gramática en Forma Normal de Chomsky" << std::endl;
        return 1;
      }
    }
    else {
      return 1;
    }
  }
  return 1;
}