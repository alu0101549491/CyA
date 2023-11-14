// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 9: Implementación de un simulador de Máquinas de Turing
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 14/11/2023
// Archivo turing_machine.cc: programa cliente.
// Contiene las definiciones de las funciones y métodos declarados en turing_machine.h
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P09
//
// Historial de revisiones
// 07/11/2023 - Creación (primera versión) del código
// 08/11/2023 - Finalización (última versión) del código

#include "turing_machine.h"

/** @brief Constructor de la clase TuringMachine
 *  @param[in] input. Fichero input.tm
 *  @param[in] tape. Fichero input.tape
 */
TuringMachine::TuringMachine(const std::string& input, const std::string& tape) {
  std::ifstream input_file{input};
  std::string initial_state;
  std::set<std::string> final_states;
  int counter = 1;
  while (input_file) { 
    std::string text_line;
    std::getline(input_file, text_line);
    if (!text_line.empty()) {
      switch (counter) {
        case 1: {
          number_of_states_ = std::stoi(text_line);
          break;
        }
        case 2: {
          initial_state = text_line;
          break;
        }
        case 3: {
          std::stringstream splitted_line(text_line);
          std::string value;
          while (splitted_line >> value) {
            final_states.insert(value);
          }
          break;
        }
        case 4: {
          number_of_tuples_ = std::stoi(text_line);
          break;
        }
        default: {
          std::string id_state, input, write, movement, next_state;
          std::stringstream splitted_line(text_line);
          splitted_line >> id_state >> input >> write >> movement >> next_state;
          std::pair<char, std::tuple<std::string, char, char>> new_tuple;
          new_tuple.first = input[0];
          new_tuple.second = std::tuple<std::string, char, char>(next_state, write[0], movement[0]);
          if (!AlreadyInStates(id_state)) {
            State new_state{id_state};
            for (auto i : final_states) {
              if (i == id_state) {
                new_state.SetIfFinal(1);
              }
            }
            new_state.InsertTuple(new_tuple);
            states_.insert(new_state);
          }
          else {
            for (auto j : states_) {
              if (j.GetID() == id_state) {
                State new_aux_state = j;
                new_aux_state.InsertTuple(new_tuple);
                states_.erase(j);
                states_.insert(new_aux_state);
              }
            }
          }

        }
      }
      counter++;
    }
  }
  int aux_num_of_tuples = 0;
  for (auto k : states_) {
    aux_num_of_tuples += k.GetTupleMap().size();
    if (k.GetID() == initial_state) {
      initial_state_ = k;
    }
    for (auto l : final_states) {
      if (!AlreadyInStates(l)) {
        State new_state{l};
        new_state.SetIfFinal(1);
        states_.insert(new_state);
      }
      if (k.GetID() == l) {
        final_states_.insert(k);
      }
    }
  }
  number_of_tuples_ = aux_num_of_tuples;
  number_of_states_ = states_.size();
  std::ifstream tape_file{tape};
  std::string tape_line;
  std::getline(tape_file, tape_line);
  for (auto i : tape_line) {
    input_alphabet_.Insert(i);
  }
  tape_alphabet_ = input_alphabet_;
  tape_alphabet_.Insert('$');
  tape_ = "$", tape_ += tape_line, tape_ += "$";
  input_file.close();
  tape_file.close();
}

/** @brief Método para imprimir la máquina de turing */
void TuringMachine::PrintTuringMachine() {
  std::cout << "Number of States: " << number_of_states_ << std::endl;
  std::cout << "States: ";
  for (auto i : states_) {
    std::cout << i.GetID() << " ";
  }
  std::cout << std::endl;
  std::cout << "Number of Tuples: " << number_of_tuples_ << std::endl; // FIX THIS
  std::cout << "Tuples: " << std::endl;
  for (auto j : states_) {
    for (auto k : j.GetTupleMap()) {
      std::cout << "(" << j.GetID() << ", " << k.first << ") ";
      std::cout << "-> {" << std::get<0>(k.second) << ", " << std::get<1>(k.second) << ", " << std::get<2>(k.second) << "}" << std::endl;
    }
  }
  std::cout << "Input Alphabet: " << input_alphabet_;
  std::cout << "Tape Alphabet: " << tape_alphabet_;
  std::cout << "Tape: " << tape_ << std::endl;
  std::cout << "Initial State: " << initial_state_.GetID() << std::endl;
  std::cout << "Final States: ";
  for (auto l : final_states_) {
    std::cout << l.GetID() << " ";
  }
  std::cout << std::endl << std::endl;
}

/** @brief Método para comprobar si un estado existe en el set de estados
 *  @param[in] state_id. Identificador del estado a buscar
 *  @return Retorna true si ya está en el set de estados y false en caso contrario
 */
bool TuringMachine::AlreadyInStates(const std::string& state_id) {
  for (auto i : states_) {
    if (i.GetID() == state_id) {
      return true;
    }
  }
  return false;
}

/** @brief Se encarga de comprobar si el estado actual se encuentra en un estado de aceptación
 *  @param[in] actual_state. Estado actual
 *  @return Retorna true si está en un estado de aceptación
 */
bool TuringMachine::MachineStop(const State& actual_state) {
  if (actual_state.GetIfFinal() == 1) {
    return true;
  }
  return false;
}

/** @brief Se encarga de procesar una cinta y comprobar si la cadena pertenece al lenguaje
 *  @return Retorna true si la cadena pertenece al lenguaje
 */
bool TuringMachine::ProcessTape() {
  std::string tape = tape_;
  unsigned head_position = 0;
  State actual_state = initial_state_;
  for (unsigned i = 0; i < tape.length(); ++i) {
    if (tape[i] != '$') {
      head_position = i;
      break;
    }
  }
  while (true) {
    for (unsigned j = 0; j < tape.length(); ++j) {
      if (j == head_position) {
        std::cout << " q" << actual_state.GetID() << " ";
      }
      std::cout << tape[j];
    }
    std::cout << std::endl;
    std::tuple<std::string, char, char> new_instruction = Move(actual_state, tape[head_position]);
    if (std::get<0>(new_instruction) == "0" && std::get<1>(new_instruction) == '0' && std::get<2>(new_instruction) == '0') {
      return MachineStop(actual_state);
    }
    for (auto new_state : states_) {
      if (new_state.GetID() == std::get<0>(new_instruction)) {
        actual_state = new_state;
      }
    }
    tape[head_position] = std::get<1>(new_instruction);
    if (std::get<2>(new_instruction) == 'R') {
      if (tape[head_position] == '$' && head_position == tape.length() - 1) {
        tape += '$';
      }
      head_position += 1;
    }
    else if (std::get<2>(new_instruction) == 'L') {
      if (tape[head_position] == '$' && head_position == 0) {
        tape = '$' + tape;
      }
      else {
        head_position -= 1;
      }
    }
    else if (std::get<2>(new_instruction) == 'S') {
      head_position += 0;
    }
    if (tape[0] != '$') {
      tape = '$' + tape;
    }
    if (tape[tape.length() - 1] != '$') {
      tape += '$';
    }
  }
}

/** @brief Sobrecarga del operador de extracción para la clase TuringMachine
 *  @param[in] out. Flujo de salida
 *  @param[in] m1. Máquina de turing a imprimir
 *  @return Devuelve el flujo de salida
 */
std::ostream& operator<<(std::ostream& out, TuringMachine m1) {
  out << m1.number_of_states_ << std::endl;
  out << m1.initial_state_ << std::endl;
  for (auto i : m1.final_states_) {
    out << i << " ";
  }
  out << std::endl;
  out << m1.number_of_tuples_ << std::endl;
  for (auto j : m1.states_) {
    for (auto k : j.GetTupleMap()) {
      out << j << " " << k.first << " " << std::get<0>(k.second) << " " << std::get<1>(k.second) << " " << std::get<2>(k.second) << std::endl;
    }
  }
  return out;
}