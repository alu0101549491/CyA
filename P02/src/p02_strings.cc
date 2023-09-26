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
// 24/09/2023 - Finalización (última versión) del código
// 26/09/2023 - Modificación de la práctica

#include "string.h"
#include "string.cc"
#include "alphabet.h"

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
  if (argc < 4 || argc > 4) {
    std::string input_file = argv[1];
    if (input_file == "--help") {
      Help();
      return false;
    }
    else {
      std::cout << "Modo de empleo: ./p02_strings filein.txt fileout.txt opcode" << std::endl;
      std::cout << "Pruebe './p02_strings --help' para más información" << std::endl;
      return false;
    }
  }
  else {
    std::ifstream input{std::string{argv[1]}};
    std::ofstream output{std::string{argv[2]}};
    if (input.fail() || output.fail()) {
      std::cout << "No se ha encontrado el fichero introducido" << std::endl;
      return false;
    }
    else {
      return true;
    }
  }
}

/** @brief Función que se encarga de imprimir un lenguaje con el formato de llaves y comas ({&, a, ab, abb})
  * @note Intenté hacer esta función como un método de la clase pero el compilador me saltaba errores con
  * el operador<< de la clase String al intentar imprimir "i", lo cual no le encontré mucho sentido, ya que
  * "i" era un const String y la sobrecarga del operador debería encargarse de ello, pero no fue el caso aparentemente.
  * @param[in] output. Flujo de salida de la impresión
  * @param[in] my_language. El lenguaje que se va a iterar para imprimir cada una de sus cadenas
  */
void WriteLanguage(std::ostream& output, Language my_language) {
  output << "{&, ";
  int counter = 0;
  for (auto i : my_language.GetLanguage()) {
    output << i;
    if (counter != my_language.LanguageSize() - 1) {
      output << ", ";
    }
    counter++;
  }
  output << "}" << std::endl;
}

/** @brief Main function
 *  @param[in] argc Number of command line parameters
 *  @param[in] argv Vector containing (char*) the parameters
 */
int main(int argc, char* argv[]) {
  if (CheckParameters(argc, argv)) {
    std::ifstream input{std::string(argv[1])};
    std::ofstream output{std::string(argv[2])};
    int n = 0;
    if ((std::stoi(argv[3])) == 6) {
      std::cout << "Introduce el valor de n para la potencia: ";
      std::cin >> n;
    }
    while (input) {
      std::string text_line;  
      std::getline(input, text_line);
      if (!text_line.empty()) {
        String my_string{text_line};
        switch (std::stoi(argv[3])) {
          case 1: {
            Alphabet alphabet = my_string.CreateAlphabet();
            output << alphabet << std::endl;
            break;
          }
          case 2: {
            int length = my_string.GetLength();
            output << length << std::endl;
            break;
          }
          case 3: {
            String inverted_string = my_string.InverseString();
            output << inverted_string << std::endl;
            break;
          }
          case 4: {
            Language prefixes = my_string.Prefixes();
            WriteLanguage(output, prefixes);
            break;
          }
          case 5: {
            Language suffixes = my_string.Suffixes();
            WriteLanguage(output, suffixes);
            break;
          }
          case 6: {
            String power = my_string.Power(n);
            output << power << std::endl;
            break;
          }
          default:
            std::cout << "La opción elegida no es correcta" << std::endl;
            return 1;
        }
      }
    }
    return 0;
  }
  else {
    return 1;
  }
}