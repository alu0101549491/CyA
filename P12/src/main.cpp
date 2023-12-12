// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 11: Algoritmos Voraces (Greedy). Euclidean Minimum Spanning Tree
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 05/12/2023
// Archivo main.cpp: programa cliente.
// Contiene la función main del proyecto
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P11
//
// Historial de revisiones
// 01/12/2023 - Creación (primera versión) del código
// 04/12/2023 - Finalización (última versión) del código

#include <fstream>
#include <iostream>
#include <sstream>

#include "point_set.hpp"

bool dot_activated = false; 

/** @brief Función que se encarga de imprimir erroress
 *  @param[in] message. Mensaje de error
 */
void ErrorExit(std::string message) {
  std::cerr << "./greedy: " << message << std::endl;
}

/** @brief Función que se encarga de comprobar el formato
 *         del fichero de entrada.
 *  @param[in] input_file. Nombre del fichero de entrada
 *  @return true si está todo correcto, false si hay errores
 */
bool CheckFile(std::ifstream& input_file) {
  int num_nodes;
  std::string text_line;
  std::getline(input_file, text_line);
  try {
    num_nodes = std::stoi(text_line);
  } catch (const std::invalid_argument& error) {
    input_file.close();
    ErrorExit("El fichero input.txt contiene fallos al declarar el número de nodos");
    return false;
  }
  for (int i = 0; i < num_nodes; ++i) {
    std::getline(input_file, text_line);
    if (text_line.empty()) {
      input_file.close();
      ErrorExit("El fichero input.txt tiene un número distinto de nodos al señalado al principio del fichero");
      return false;
    }
    std::stringstream splitted_line (text_line);
    std::string value;
    int j = 0;
    while (splitted_line >> value) {
      if (!value.empty()) {
        switch(j) {
          case 0:
          case 1: {
            try {
              std::stoi(value);
            } catch (const std::invalid_argument& error) {
              input_file.close();
              ErrorExit("Los nodos deben tener valores numéricos");
              return false;
            }
            j++;
            break;
          }
          default:
            input_file.close();
            ErrorExit("El fichero input.txt contiene más de dos elementos por linea de descripción de nodos");
            return false;
        }
      }
      else {
        break;
      }
    }
    if (j < 2) {
      input_file.close();
      ErrorExit("El fichero input.txt contiene menos de dos elementos por linea de nodos");
      return false;
    }
  }
  std::getline(input_file, text_line);
  if (!text_line.empty()) {
    input_file.close();
    ErrorExit("El fichero input.txt contiene más nodos de los descritos al principio del fichero");
    return false;
  }
  input_file.close();
  return true;
}

/** @brief Revisa que los parámetros introducidos al programa funcionen correctamente y no generen errores
  * @param[in] argc. Número de parámetros pasados al programa a través de la terminal
  * @param[in] argv. Vector de char* que contiene los parámetros pasados al programa
  * @return Valor booleano que determina si el parámetro que se le pasó al programa es correcto y se puede proseguir
  */
bool CheckParameters(const int& argc, char* argv[]) {
  if (argc < 2 || argc > 2) {
    std::cout << "Modo de empleo: ./greedy input.txt" << std::endl;
    return false;
  }
  else {
    std::string file;
    if (std::string(argv[1]) == "-d") {
      file = argv[2];
      dot_activated = true;
    }
    else {
      file = argv[1];
    }
    std::ifstream input{file};
    if (input.fail()) {
      ErrorExit("No se ha encontrado el fichero introducido");
      return false;
    }
    else {
      if (CheckFile(input)) {
        return true;
      }
      else {
        return false;
      }
    }
  }
}

/** @brief Función que se encarga de leer el fichero y guardar
 *         sus datos en un vector de puntos.
 *  @param[in] input_file. Nombre del fichero de entrada
 *  @return Vector de puntos
 */
ConvexHull::point_vector ReadFile(std::ifstream& input_file) {
  std::string text_line;
  ConvexHull::point_vector vector_of_points;
  std::getline(input_file, text_line);
  vector_of_points.reserve(std::stoi(text_line));
  std::getline(input_file, text_line);
  while (!text_line.empty()) {
    std::string value;
    std::stringstream splitted_line(text_line);
    splitted_line >> value;
    double coord_i = std::stod(value);
    splitted_line >> value;
    double coord_j = std::stod(value);
    ConvexHull::point new_point = std::pair<double, double>(coord_i, coord_j);
    vector_of_points.push_back(new_point);
    std::getline(input_file, text_line);
  }
  return vector_of_points;
}

/** @brief Main function
 *  @param[in] argc Number of command line parameters
 *  @param[in] argv Vector containing (char*) the parameters
 */
int main(int argc, char* argv[]) {
	if (CheckParameters(argc, argv)) { 
    std::ifstream input_file;
    std::ofstream output_txt{"output.txt"};
    if (dot_activated) {
      input_file = std::ifstream{argv[2]};
    }
    else {
      input_file = std::ifstream{argv[1]};
    }
    ConvexHull::point_vector vector = ReadFile(input_file);
    ConvexHull::point_set myset{vector};
    std::cout << "se leyó perfe\n";
    return 0;
  }
  return 1;
}