// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 7: Gramáticas en Forma Normal de Chomsky
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 31/10/2023
// Archivo grammar.cc: programa cliente.
// Contiene las definiciones de las funciones y métodos declarados en grammar.h
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P07
//
// Historial de revisiones
// 26/10/2023 - Creación (primera versión) del código
// 29/10/2023 - Finalización (última versión) del código

#include "grammar.h"

/** @brief Constructor de la clase Grammar que lee el fichero de texto que le es suministrado
 *         para extraer los datos filtrados en atributos de la clase Grammar
 *  @param[in] input_file. Fichero de texto con los datos de la gramática
 */
Grammar::Grammar(const std::string& input) {
  std::ifstream input_file{input};
  int counter = 1;
  int num_terminals, num_of_non_terminals, num_of_productions;
  while (input_file) {
    std::string text_line;
    std::getline(input_file, text_line);
    if (!text_line.empty()) {
      switch (counter) {
        case 1: {
          num_terminals = std::stoi(text_line);
        }
        case 2: {
          for (int i = 1; i <= num_terminals; ++i) {
            std::getline(input_file, text_line);
            terminals_.Insert(text_line[0]);
          }
          std::getline(input_file, text_line);
        }
        case 3: {
          num_of_non_terminals = std::stoi(text_line);
        }
        case 4: {
          for (int i = 1; i <= num_of_non_terminals; ++i) {
            std::getline(input_file, text_line);
            if (i == 1) {
              initial_ = text_line;
            }
            non_terminals_.insert(text_line);
          }
          std::getline(input_file, text_line);
        }
        case 5: {
          num_of_productions = std::stoi(text_line);
        }
        case 6: {
          for (int i = 1; i <= num_of_productions; ++i) {
            std::getline(input_file, text_line);
            std::string origin, production;
            std::stringstream splitted_line(text_line);
            splitted_line >> origin, splitted_line >> production;
            productions_.insert(std::pair<std::string, std::string>(origin, production));
          }
          std::getline(input_file, text_line);
        }
      }
      counter++;
    }
  }
  input_file.close();
}

/** @brief Método para imprimir información de la gramática */ 
void Grammar::Print() {
  std::cout << "=== Not Terminals ===" << std::endl;
  for (auto& i : non_terminals_) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
  std::cout << "=== Terminals ===" << std::endl;
  for (auto& j : terminals_.GetSet()) {
    std::cout << j << " ";
  }
  std::cout << std::endl;
  std::cout << "=== Initial ===" << std::endl;
  std::cout << initial_ << std::endl;
  std::cout << "=== Productions ===" << std::endl;
  for (auto& k : productions_) {
    std::cout << k.first << " -> " << k.second << std::endl;
  }
}

/** @brief Método que revisa si la gramática contiene producciones vacías
  * @return Devuelve true si contiene prodcciones vacías, en caso contrario, false
  */ 
bool Grammar::CheckIfEmptyProductions() {
  for (auto& production : productions_) {
    if (production.second == "&" && production.first != initial_) {
      std::cout << "La gramática suministrada contiene producciones vacías" << std::endl;
      return true;
    }
  }
  return false;
}

/** @brief Método que revisa si la gramática contiene producciones unitarias
  * @return Devuelve true si contiene prodcciones unitarias, en caso contrario, false
  */ 
bool Grammar::CheckIfUnitaryProductions() {
  for (auto& production : productions_) {
    for (auto& non_terminal : non_terminals_) {
      if (production.second == non_terminal) {
        std::cout << "La gramática suministrada contiene producciones unitarias" << std::endl;
        return true;
      }
    }
  }
  return false;
}

/** @brief Método que se encarga de cambiar el valor de el símbolo de un nuevo no-terminal
  *        que vaya a ser introducido a la gramática
  * @param[in] symbol. Símbolo a analizar
  */ 
void Grammar::ChangeNonTerminalSymbol(char& symbol) {
  if (symbol == 'Z') {
    symbol = 'A';
  }
  else {
    symbol++;
  }
  while (non_terminals_.find(std::string(1,symbol)) != non_terminals_.end()) {
    symbol++;
  }
}

/** @brief Método que se encarga de realizar la conversión de la gramática a Forma Normal de */ 
void Grammar::ConvertToCNF() {
  char aux_char;
  auto it = --non_terminals_.end();
  if (*it == initial_) {
    --it;
  }
  aux_char = (*it)[0] + 1;
  std::map<char, char> aux_non_terms;
  for (auto& symbol : terminals_.GetSet()) {
    std::string aux;
    aux += aux_char;
    aux_non_terms[symbol] = aux_char;
    ChangeNonTerminalSymbol(aux_char);
  }
  for (auto& production : productions_) {
    if (production.second.length() >= 2) {
      for (auto& prod_symbol : production.second) {
        if (terminals_.GetSet().find(prod_symbol) != terminals_.GetSet().end() && std::islower(prod_symbol)) {
          if (productions_.find(std::string(1,aux_non_terms[prod_symbol])) == productions_.end()) {
            productions_.insert(std::make_pair(std::string(1,aux_non_terms[prod_symbol]), std::string(1,prod_symbol)));
            non_terminals_.insert(std::string(1,aux_non_terms[prod_symbol]));
          }
          prod_symbol = aux_non_terms[prod_symbol];
        }
      }
    }
  }
  for (auto& production : productions_) {
    while (production.second.length() >= 3) {
      for (unsigned i = 1; i < production.second.length() - 1; ++i) {
        std::string new_production;
        new_production += production.second[production.second.length() - 2];
        new_production += production.second[production.second.length() - 1];
        productions_.insert(std::make_pair(std::string(1,aux_char), new_production));
        non_terminals_.insert(std::string(1,aux_char));
        size_t position = production.second.find(new_production);
        if (position != std::string::npos) {
          production.second.replace(position, new_production.length(), std::string(1,aux_char));
        }
        ChangeNonTerminalSymbol(aux_char);
      }
    }
  }
}

/** @brief Sobrecarga del operador de extracción para la clase Grammar
 *  @param[in] out. Flujo de salida
 *  @param[in] output_grammar. Objeto de la clase Grammar que se va a imprimir
 *  @return Devuelve el flujo de salida
 */
std::ostream& operator<<(std::ostream& out, Grammar output_grammar) {
  out << output_grammar.terminals_.GetSet().size() << std::endl;
  out << output_grammar.terminals_;
  out << output_grammar.non_terminals_.size() << std::endl;
  for (auto& i : output_grammar.non_terminals_) {
    out << i << std::endl;
  }
  out << output_grammar.productions_.size() << std::endl;
  for (auto& j : output_grammar.productions_) {
    out << j.first << " " << j.second << std::endl;
  }
  return out;
}