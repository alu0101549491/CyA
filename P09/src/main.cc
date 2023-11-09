// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 9: Implementación de un simulador de Máquinas de Turing
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 07/11/2023
// Archivo main.cc: programa cliente.
// Contiene la función main del proyecto que usa la clase TuringMachine
// para procesar una cinta y una máquina de turing dada
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P09
//
// Historial de revisiones
// 07/11/2023 - Creación (primera versión) del código
// 08/11/2023 - Finalización (última versión) del código


#include "turing_machine.h"

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
    std::cout << "Modo de empleo: ./TuringMachineSimulator input.tm input.tape" << std::endl;
    std::cout << "Pruebe './TuringMachineSimulator --help' para más información." << std::endl;
    return false;
  }
  if (argc < 3 || argc > 3) {
    if (std::string(argv[1]) == "--help") {
      Help();
      return false;
    }
    else {
      std::cout << "Modo de empleo: ./TuringMachineSimulator input.tm input.tape" << std::endl;
      std::cout << "Pruebe './TuringMachineSimulator --help' para más información." << std::endl;
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
  * @return Retorna false, como es una salida de error
  */
bool ErrorExit(const std::string& error_message) {
  std::cout << "TuringMachineSimulator: " << error_message << std::endl;
  std::cout << "Consulte './TuringMachineSimulator --help' para más información" << std::endl;
  std::cerr << std::endl;
  return false;
}

/** @brief Revisa que todo en el fichero de texto esté correcto
  * @param[in] input. Nombre del fichero de texto
  * @return Si está todo en orden devuelve true, en caso contrario, false
  */
bool CheckFile(const std::string& input) {
  std::ifstream input_file{input};
  std::string text_line;
  int num_states;
  int num_tuples;
  std::string initial_state;
  std::string final_states;
  std::getline(input_file, text_line);
  try {
    num_states = std::stoi(text_line);
  } catch (const std::invalid_argument& error) {
    input_file.close();
    return ErrorExit("El fichero input.tm contiene fallos al declarar el número de estados");
  }
  if (num_states <= 0) {
    input_file.close();
    return ErrorExit("La máquina debe tener al menos un estado");
  }
  std::getline(input_file, text_line);
  initial_state = text_line;
  if (std::stoi(initial_state) < 0 || std::stoi(initial_state) > num_states) {
    input_file.close();
    return ErrorExit("El fichero input.tm contiene un estado inicial no válido");
  }
  std::getline(input_file, text_line);
  if (text_line.empty()) {
    input_file.close();
    return ErrorExit("La máquina de turing debe tener al menos un estado de aceptación");
  }
  std::stringstream splitted_line(text_line);
  std::string value;
  while (splitted_line >> value) {
    if (std::stoi(value) < 0 || std::stoi(value) > num_states) {
      input_file.close();
      return ErrorExit("El fichero input.tm contiene un estado final no válido");
    }
  }
  std::getline(input_file, text_line);
  try {
    num_tuples = std::stoi(text_line);
  } catch (const std::invalid_argument& error) {
    input_file.close();
    return ErrorExit("El fichero input.tm contiene fallos al declarar el número de tuplas");
  }
  int tuple_counter = -1;
  while (!text_line.empty()) {
    std::getline(input_file, text_line);
    std::stringstream splitted_line(text_line);
    std::string value;
    int i = 0;
    while (splitted_line >> value) {
      switch(i) {
        case 0: {
          if (std::stoi(value) < 0 || std::stoi(value) > num_states) {
            input_file.close();
            return ErrorExit("Una de las tuplas contiene un estado no perteneciente al conjunto anteriormente señalado");
          }
          break;
        }
        case 3: {
          if (value.length() > 1 || (value[0] != 'S' && value[0] != 'L' && value[0] != 'R')) {
            input_file.close();
            return ErrorExit("Una de las tuplas contiene un movimiento no reconocible");
          }
          break;
        }
        case 4: {
          if (std::stoi(value) < 0 || std::stoi(value) > num_states) {
            input_file.close();
            return ErrorExit("Una de las tuplas contiene un estado no perteneciente al conjunto anteriormente señalado");
          }
          break;
        }
      }
      i++;
    }
    tuple_counter++;
  }
  if (tuple_counter != num_tuples) {
    input_file.close();
    return ErrorExit("El número de tuplas introducido es distinto al número de tuplas especificado");
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
    std::string machine_file = argv[1];
    std::string tape_file = argv[2];
    if (CheckFile(machine_file)) {
      TuringMachine turing_machine{machine_file, tape_file};
      //turing_machine.PrintTuringMachine();
      std::cout << turing_machine << std::endl;
      if (turing_machine.ProcessTape()) {
        std::cout << "\nCadena ACEPTADA" << std::endl;
      }
      else {
        std::cout << "\nCadena RECHAZADA" << std::endl;
      }
      return 0;
    }
  }
  return 1;
}