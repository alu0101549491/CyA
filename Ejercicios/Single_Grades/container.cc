// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 1: Contenedores asociativos
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 13/09/2023
// Archivo container.cc: programa cliente.
// Contiene las definiciones de las funciones y métodos declarados en container.h
// Referencias:
// https://github.com/alu0101549491/CyA-P01
//
// Historial de revisiones
// 13/09/2023 - Creación (primera versión) del código
// 14/09/2023 - Finalización (última versión) del código

#include "container.h"

/** @brief Imprime en pantalla una breve guía y explicación sobre el funcionamiento del programa 
  * @param[in] argc. Número de parámetros pasados al programa a través de la terminal
  * @param[in] argv. Vector de char* que contiene los parámetros pasados al programa
  * @return Valor booleano que determina si el parámetro que se le pasó al programa es correcto y se puede proseguir
  */
bool CheckParameters(const int& argc, char* argv[]) {
  if (argc < 2 || argc > 2) {
    std::cout << "Modo de empleo: ./p01_single_grades grades.txt" << std::endl;
    std::cout << "Pruebe 'p01_single_grades --help' para más información" << std::endl;
    return false;
  }
  else {
    std::string main_parameter = argv[1];
    if (main_parameter == "--help") {
      Help();
      return false;
    }
    else {
      std::ifstream input_file{main_parameter};
      if (!input_file.good()) {
        std::cout << "No se ha encontrado el fichero introducido" << std::endl;
        return false;
      }
      else {
        return true;
      }
    }
  }
}

/** @brief Imprime en pantalla una breve guía y explicación sobre el funcionamiento del programa */
void Help() {
  std::ifstream input_file{"help.txt"};
  while (input_file) {
    std::string text_line;
    std::getline(input_file, text_line);
    std::cout << text_line << std::endl;
  }
}

/** @brief Lee el fichero de texto que se le pasa al programa para procesar los datos en la clase Container
  * @param[in] grades. Fichero de texto que se va a procesar
  */
void Container::ReadTextFile(const std::string& grades) {
  std::ifstream input_file{grades};
  char delimiter = ' ';
  while (input_file) {
    std::string text_line, identifier, grade, aux;
    std::getline(input_file, text_line);
    if (text_line != "") {
      for (int i = 0; i <= text_line.size(); ++i) {
        if (i == text_line.size()) {
          grade = aux;
        }
        else {
          if (text_line[i] != delimiter) {
            aux += text_line[i];
          }
          else {
            identifier = aux;
            aux = "";
          }
        }
      }
      double numeric_grade = std::stod(grade);
      container_[identifier] = numeric_grade;
    }
  }
}

/** @brief Imprime los elementos del mapa de datos de la clase Container */
void Container::PrintContainerElements() {
  std::map <std::string, double>::iterator i = container_.begin();
  while (i != container_.end()) {
    std::cout << i->first << " " << i->second << std::endl;
    ++i; 
  }
}

/** @brief Permite añadir un nuevo dato al mapa de datos de la clase Container */
void Container::AddNewData() {
  std::string identifier;
  double grade{0.0};
  std::cout << "Introduzca el identificador del alumno: ";
  std::cin >> identifier;
  std::cout << "Introduzca la nota del alumno: ";
  std::cin >> grade;
  container_[identifier] = grade;
}