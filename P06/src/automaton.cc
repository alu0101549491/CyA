// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Convertir un NFA en un DFA
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 18/10/2023
// Archivo automaton.cc: programa cliente.
// Contiene las definiciones de las funciones y métodos declarados en automaton.h
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P06
//
// Historial de revisiones
// 18/10/2023 - Creación (primera versión) del código
// 21/10/2023 - Finalización (última versión) del código

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
  for (auto& i : states_) {
    if (std::stoi(i.GetID()) == aux_initial) {
      initial_state_ = i;
    }
    if (i.GetFinal() == 1) {
      final_states_.insert(i);
    }
  }
  actual_states_.insert(initial_state_);
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
  for (auto& j : states_) {
    std::cout << j << "\n\n";
  }
  std::cout << "----- INITIAL STATE -----\n\n";
  std::cout << initial_state_ << "\n";
  std::cout << "----- FINAL STATES -----\n\n";
  for (auto& k : final_states_) {
    std::cout << k << "\n\n";
  }
  std::cout << "----- ACTUAL STATES -----\n\n";
  for (auto& l : actual_states_) {
    std::cout << l << "\n\n";
  }
}

/** @brief Revisa si en el conjunto de estados suministrados via atributo se encuentra un estado final
 *  @param[in] states. Conjunto de estados
 *  @return "true" si states tiene un estado final y "false" en caso contrario
 */
bool Automaton::CheckIfFinalState(const std::set<State>& states) {
  for (auto& i : states) {
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
bool CheckIfEpsilonTransitions(const std::set<State>& states) {
  for (auto& state : states) {
    std::multimap<char, std::string> transitions = state.GetTransitions();
    if (!transitions.empty()) {
      for (auto& transition : transitions) {
        if (transition.first == '&') {
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
void Automaton::UpdateActualStates(std::set<State>& actual_states, const char& character) {
  std::set<State> new_states;
  for (auto& actual_state : actual_states) {
    std::multimap<char, std::string> transitions = actual_state.GetTransitions();
    if (!transitions.empty()) {
      for (auto& transition : transitions) {
        if (transition.first == character) {
          for (auto& state : states_) {
            if (transition.second == state.GetID()) {
              new_states.insert(state);
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


/** @brief Se encarga de procesar una cadena para comprobar si pertenece al lenguaje
 *         que reconoce el autómata
 *  @param[in] string. Cadena a procesar
 *  @return "true" si la cadena pertenece y "false" en caso contrario
 */
bool Automaton::ProcessStrings(const std::string& string) {
  std::set<State> actual_states = GetActualStates();
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

/** @brief Método complementario de CheckStates que revisa de forma individual
 *         caracteres de las transiciones para comprobar que pertenezcan al alfabeto
 *  @param[in] character. Caracter para comprobar
 *  @return Retorna "true" si está todo correcto y "false" si hay un error
 */
bool Automaton::CheckIfBelongsToAlphabet(const char& character) {
  bool good_symbol = false;
  for (auto& symbol : alphabet_.GetSet()) {
    if (character == symbol) {
      good_symbol = true;
    }
  }
  return good_symbol;
}

/** @brief Método complementario de CheckStates que revisa de forma individual
 *         transiciones para comprobar que llevan a estados pertenecientes al autómata
 *  @param[in] transition_id. Identificador del destino de la transición
 *  @return Retorna "true" si está todo correcto y "false" si hay un error
 */
bool Automaton::CheckTransition(const std::string& transition_id) {
  bool good_transition = false;
  for (auto& state : states_) {
    if (state.GetID() == transition_id) {
      good_transition = true;
    }
  }
  return good_transition;
}

/** @brief Este método booleano se encarga de revisar todos los estados en busca de posibles 
 *         fallos como transiciones a estados que no pertenecen al autómata o transiciones 
 *         mediante simbolos que no pertenecen al alfabeto del autómata
 *  @return Retorna "true" si está todo correcto y "false" + un mensaje del estado que falla si hay un error
 */
bool Automaton::CheckStates() {
  std::map<std::string,bool> belongs_to_alphabet;
  std::map<std::string,bool> states_in_range;
  bool validity = true;
  for (auto& state : states_) {
    belongs_to_alphabet[state.GetID()] = true;
    states_in_range[state.GetID()] = true;
    for (auto& transition : state.GetTransitions()) {
      if (!CheckIfBelongsToAlphabet(transition.first)) {
        belongs_to_alphabet[state.GetID()] = false;
      }
      if (!CheckTransition(transition.second)) {
        states_in_range[state.GetID()] = false;
      }
    }
    if (!belongs_to_alphabet[state.GetID()]) {
      std::cout << "El estado '" << state.GetID() << "' contiene símbolos de transición que no pertenecen al alfabeto." << std::endl;
      validity = false;
    }
    if (!states_in_range[state.GetID()]) {
      std::cout << "El estado '" << state.GetID() << "' contiene transiciones a estados que no pertenecen al autómata." << std::endl;
      validity = false;
    }
  }
  return validity;
}

/** @brief Realiza la Epsilon-Clausura de un conjunto de estados dado
 *  @param[in] actual_states. Conjunto de estados
 *  @return Retorna el conjunto de estados que se corresponde con la Épsilon-Clausura del set pasado al método
 */
std::set<State> Automaton::EpsilonClosure(const std::set<State>& actual_states) {
  //UpdateActualStates(actual_states, '&');
  std::stack<State> stack_t;
  for (auto& state : actual_states) {
    stack_t.push(state);
  }
  std::set<State> epsilon_closure = actual_states;
  while (!stack_t.empty()) {
    State closure_state = stack_t.top();
    stack_t.pop();
    for (auto& transition : closure_state.GetTransitions()) {
      if (transition.first == '&') {
        for (auto& state : states_) {
          if (transition.second == state.GetID()) {
            if (epsilon_closure.find(state) == epsilon_closure.end()) {
              epsilon_closure.insert(state);
              stack_t.push(state);
            }
          }
        }
      }
    }
  }
  return epsilon_closure;
}

/** @brief Realiza la transicion desde un conjunto de estados a otro
 *  @param[in] origin_states. Conjunto de estados de origen
 *  @param[in] symbol. Conjunto de estados de origen
 *  @return Retorna el conjunto de estados de destino
 */
std::set<State> Automaton::Move(const std::set<State>& origin_states, const char& symbol) {
  std::set<State> destinations;
  for (auto& origin_state : origin_states) {
    for (auto& transition : origin_state.GetTransitions()) {
      if (transition.first == symbol) {
        for (auto& state : states_) {
          if (transition.second == state.GetID()) {
            destinations.insert(state);
          }
        }
      }
    }
  }
  return destinations;
}

/** @brief Revisa si en un mapa dado se encuentra un elemento con un identificador dado
 *  @param[in] my_map. Mapa de tipo std::string,std::set<State>
 *  @param[in] my_key. Identificador a buscar en el mapa
 *  @return Retorna "true" si existe un elemento con el identificador "my_key" en el mapa
 */
bool FindKey(const std::map<std::string,std::set<State>>& my_map, const std::string& my_key) {
  auto it = my_map.find(my_key);
  if (it == my_map.end()) {
    return false;
  }
  return true;
}

/** @brief Revisa si en un mapa que contiene sets de estados se encuentra un set de estados dado
 *  @param[in] map_of_states. Mapa de tipo std::string,std::set<State>
 *  @param[in] states. Set de estados a comparar
 *  @return Retorna "true" si existe un set de estados igual en el mapa
 */
bool AlreadyInDFA(std::map<std::string, std::set<State>> map_of_states, std::set<State> states) {
  for (auto& set_state : map_of_states) {
    if (states == set_state.second) {
      return true;
    }
  }
  return false;
}

/** @brief Se encarga de, apartir de una serie de un mapa que contiene estados,
 *         y otro que contiene transiciones, construir un automata tipo DFA
 *  @param[in] states. Mapa de estados
 *  @param[in] transitions. Mapa de transiciones
 *  @return Retorna el DFA construido
 */
Automaton Automaton::CreateDFA(std::map<std::string, std::set<State>> states, std::map<std::string, std::multimap<char, std::string>> transitions) {
  Automaton DFA;
  DFA.SetAlphabet(alphabet_);
  DFA.SetNumberOfStates(states.size());
  std::set<State> dfa_states;
  // Construcción del set de estados y sus transiciones
  for (auto& i : states) {
    State new_state{i.first};
    new_state.SetAlphabet(alphabet_);
    bool final_state = 0;
    for (auto& state : i.second) {
      if (state.GetFinal() == 1) {
        final_state = 1;
        break;
      }
    }
    new_state.SetIfFinal(final_state);
    for (auto& transition : transitions) {
      if (i.first == transition.first) {
        new_state.SetTransitionMap(transition.second);
        new_state.SetNumberOfTransitions(transition.second.size());
      }
    }
    dfa_states.insert(new_state);
  }
  // Revisión del set de estados para determinar que estados son finales y el estado inicial,
  // por la forma en la que está construido el algoritmo del método TransformToDFA().
  for (auto& state : dfa_states) {
    if (state.GetID() == "A") {
      DFA.SetInitialState(state);
    }
    if (state.GetFinal() == 1) {
      DFA.InsertToFinalStates(state);
    }
  }
  DFA.SetStates(dfa_states);
  DFA.InsertActualState(DFA.GetInitialState());
  return DFA;
}

/** @brief Se encarga de, siguiendo el modelo del algoritmo de construcción de subconjuntos,
 *         crear un DFA equivalente al NFA desde el que se llamó al método
 *  @return Retorna el DFA construido
 */
Automaton Automaton::TransformToDFA() {
  std::queue<std::string> pending_states;
  std::map<std::string, std::set<State>> dfa_states;
  std::map<std::string, std::multimap<char, std::string>> states_transitions;
  std::string state_id = "A";
  pending_states.push(state_id);
  dfa_states.insert(std::pair<std::string,std::set<State>>(state_id,EpsilonClosure(GetActualStates())));
  char new_id = 'B';
  while (FindKey(dfa_states, state_id) && !pending_states.empty()) {
    pending_states.pop();
    for (auto symbol : alphabet_.GetSet()) {
      std::string old_state_id = state_id;
      if (symbol != '&') {
        std::set<State> new_state_set = EpsilonClosure(Move(dfa_states[state_id], symbol));
        if (!AlreadyInDFA(dfa_states,new_state_set)) {
          pending_states.push(std::string(1,new_id));
          dfa_states.insert(std::pair<std::string,std::set<State>>(std::string(1,new_id), new_state_set));
          states_transitions[old_state_id].insert(std::pair<char,std::string>(symbol,std::string(1,new_id)));
          new_id++;
        }
        else {
          for (auto& state : dfa_states) {
            if (new_state_set == state.second) {
              states_transitions[old_state_id].insert(std::pair<char,std::string>(symbol,state.first));
            }
          }
        }
      }
    }
    state_id = pending_states.front();
  }
  return CreateDFA(dfa_states, states_transitions);
}

/** @brief Se encarga de escribir la información del DFA en un fichero de salida */
void Automaton::WriteDFAInOutputFile(std::ostream& output) {
  output << alphabet_ << std::endl;
  output << number_of_states_ << std::endl;
  output << initial_state_.GetID() << std::endl;
  for (auto& state : states_) {
    output << state.GetID() << " " << state.GetFinal() << " " << state.GetNumberOfTransitions() << " ";
    for (auto& transition : state.GetTransitions()) {
      output << transition.first << " " << transition.second << " ";
    }
    output << std::endl;
  }
}