#include "p01_single_grades.h"

bool CheckParameters(const int& argc, char* argv[]) {
  if (argc <= 1) {
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
      return true;
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

void Container::PrintContainerElements() {
  std::map<std::string, double>::iterator i = container_.begin();
  while (i != container_.end()) {
    std::cout << i->first << " " << i->second << std::endl;
    ++i; 
  }
}