// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 5: Implementación de un simulador de autómatas finitos
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 16/10/2023
// Archivo automaton.cc: programa cliente.
// Contiene las definiciones de las funciones y métodos declarados en automaton.h
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P05
//
// Historial de revisiones
// 12/10/2023 - Creación (primera versión) del código
// 16/10/2023 - Finalización (última versión) del código

#include "automaton.h"

/** @brief Constructor de la clase Automaton que lee el fichero de texto que le es suministrado
 *         para extraer los datos filtrados en atributos de la clase Automaton
 *  @param[in] input_file. Fichero de texto con los datos del Autómata
 */
Automaton::Automaton(std::ifstream& input_file) {
  int i = 0;
  int aux_initial = 0;
  while(input_file) {
    std::string text_line;
    std::getline(input_file, text_line);
    if (!text_line.empty()) {
      switch (i) {
        case 0: {
          char value;
          std::stringstream splitted_line(text_line);
          alphabet_.Insert('&');
          while (splitted_line >> value) {
            alphabet_.Insert(value);
          }
          break;
        }
        case 1: {
          number_of_states_ = std::stoi(text_line);
          break;
        }
        case 2: {
          aux_initial = std::stoi(text_line);
          break;
        }
        default: {
          std::string value;
          std::stringstream splitted_line(text_line);
          std::vector<std::string> properties;
          while (splitted_line >> value) {
            properties.push_back(value);
          }
          State state{properties};
          state.SetAlphabet(alphabet_);
          states_.insert(state);
          break;
        }
      }
    ++i;
    }
  }
  for (auto i : states_) {
    if (std::stoi(i.GetID()) == aux_initial) {
      initial_state_ = i;
    }
    if (i.GetFinal() == 1) {
      final_states_.push_back(i);
    }
  }
  actual_states_.push_back(initial_state_);
}

/** @brief Método para imprimir información del autómata */ 
void Automaton::Print() {
  std::cout << "----- ALPHABET -----\n";
  std::cout << alphabet_ << "\n";
  std::cout << "\n";
  std::cout << "----- NUMBER OF STATES -----\n";
  std::cout << number_of_states_ << "\n";
  std::cout << "\n";
  std::cout << "----- STATES -----\n\n";
  for (auto j : states_) {
    std::cout << j << "\n\n";
  }
  std::cout << "----- INITIAL STATE -----\n\n";
  std::cout << initial_state_ << "\n";
  std::cout << "----- FINAL STATES -----\n\n";
  for (auto k : final_states_) {
    std::cout << k << "\n\n";
  }
  std::cout << "----- ACTUAL STATES -----\n\n";
  for (auto l : actual_states_) {
    std::cout << l << "\n\n";
  }
}

/** @brief Revisa si en el conjunto de estados suministrados via atributo se encuentra un estado final
 *  @param[in] states. Conjunto de estados
 *  @return "true" si states tiene un estado final y "false" en caso contrario
 */
bool Automaton::CheckIfFinalState(const std::vector<State>& states) {
  for (auto i : states) {
    if (i.GetFinal() == 1) {
      return true;
    }
  }
  return false;
}

/** @brief Función complementaria del método UpdateActualStates que revisa si a los estados
 *         actuales les queda alguna épsilon-transición que procesar
 *  @param[in] states. Conjunto de estados
 *  @return "true" si states le quedan épsilon-transiciones y "false" en caso contrario
 */
bool CheckIfEpsilonTransitions(const std::vector<State>& states) {
  for (auto state : states) {
    std::multimap<std::string, int> transitions = state.GetTransitions();
    if (!transitions.empty()) {
      for (auto transition : transitions) {
        if (transition.first == "&") {
          return true;
        }
      }
    }
  }
  return false;
}

/** @brief Actualiza el conjunto de estados actuales suministrados via parámetro por referencia
 *         realizando las transiciones desde el conjunto de estados actuales hacia nuevos estados
 *         posibles por el símbolo dado
 *  @param[in] actual_states. Conjunto de estados actuales
 *  @param[in] character. Caracter para revisar al transicionar
 */
void Automaton::UpdateActualStates(std::vector<State>& actual_states, const char& character) {
  std::vector<State> new_states;
  for (auto actual_state : actual_states) {
    std::multimap<std::string, int> transitions = actual_state.GetTransitions();
    if (!transitions.empty()) {
      for (auto transition : transitions) {
        if (transition.first == std::string(1,character)) {
          for (auto state : states_) {
            if (transition.second == std::stoi(state.GetID())) {
              new_states.push_back(state);
              actual_states = new_states;
            }
          }
        }
      }
    }
  }
  if (character == '&' && CheckIfEpsilonTransitions(actual_states)) {
    UpdateActualStates(actual_states, character);
  }
}

/** @brief LLama a UpdateActualStates pero con el símbolo '&' */
void Automaton::EpsilonClosure(std::vector<State>& actual_states) {
  UpdateActualStates(actual_states, '&');
}

/** @brief Se encarga de procesar una cadena para comprobar si pertenece al lenguaje
 *         que reconoce el autómata
 *  @param[in] string. Cadena a procesar
 *  @return "true" si la cadena pertenece y "false" en caso contrario
 */
bool Automaton::ProcessStrings(const std::string& string) {
  std::vector<State> actual_states = GetActualStates();
  int counter = 0;
  for (auto character : string) {
    if (counter == 0) {
      EpsilonClosure(actual_states);
    }
    if (character == '&') {
      return CheckIfFinalState(actual_states);
    }
    else {
      if (actual_states.empty()) {
        return false;
      }
      else {
        UpdateActualStates(actual_states, character);
      }
    }
    counter++;
    EpsilonClosure(actual_states);
  }
  return CheckIfFinalState(actual_states);
} 