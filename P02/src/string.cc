// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Operaciones con Cadenas
// Autor: Fabián González Lence
// Correo: alu0101549491@ull.edu.es
// Fecha: 21/09/2023
// Archivo string.cc: programa cliente.
// Contiene las definiciones de las funciones y métodos declarados en string.h
// Referencias:
// https://github.com/alu0101549491/CyA/tree/master/P02
//
// Historial de revisiones
// 21/09/2023 - Creación (primera versión) del código
// 24/09/2023 - Finalización (última versión) del código
// 26/09/2023 - Modificación de la práctica

#include "string.h"

/** @brief Constructor de la clase String
  * @param[in] string. Parámetro de tipo std::string que se va a asignar al atributo principal de la clase
  */
String::String(std::string string) { 
  string_ = string;
}

/** @brief Getter de la clase String
  * @return Devuelve el valor de el atributo principal de la clase como un std::string
  */
std::string String::GetString() const { 
  return string_;
}

/** @brief Se encarga de añadir simbolos y/o subcadenas a la cadena atributo de la clase String
  * @param[in] string. Cadena que se va a añadir al atributo de la clase
  */
void String::Insert(std::string string) {
  string_ += string;
}

/** @brief Se encarga de analizar la longitud de la cadena del atributo principal de la clase
  * @return Devuelve el valor de la longitud de la String como un int
  */
int String::GetLength() { 
  return string_.length();
}

/** @brief Se encarga de crear el alfabeto de la cadena atributo de la clase
  * @return Devuelve el alfabeto como tipo Alphabet
  */
Alphabet String::CreateAlphabet() {
  std::set<char> aux_set;
  for (auto i : GetString()) {
    aux_set.insert(i);
  }
  Alphabet alphabet{aux_set};
  return alphabet;
}

/** @brief Se encarga de crear el inverso de la cadena atributo de la clase
  * @return Devuelve la cadena inversa como tipo String
  */
String String::InverseString() {
  std::string inverted_string = string_;
  std::reverse(inverted_string.begin(), inverted_string.end());
  String inverted{inverted_string};
  return inverted;
}

/** @brief Se encarga de crear los prefijos de la cadena atributo de la clase
  * @return Devuelve la lista de prefijos como tipo Language
  */
Language String::Prefixes() {
  std::set<String> prefixes_set;
  String substring{""};
  for (unsigned i = 0; i < string_.length(); ++i) {
    substring.Insert(std::string(1,string_[i]));
    prefixes_set.insert(substring);
  }
  Language prefixes{prefixes_set};
  return prefixes;
}

/** @brief Se encarga de crear los sufijos de la cadena atributo de la clase
  * @return Devuelve la lista de sufijos como tipo Language
  */
Language String::Suffixes() {
  std::set<String> suffixes_set;
  String substring{""};
  for (int i = GetLength() - 1; i >= 0; --i) {
    substring.Insert(std::string(1,string_[i]));
    suffixes_set.insert(substring.InverseString());
  }
  Language suffixes{suffixes_set};
  return suffixes;
}

String String::Power(int n) {
  String power{""};
  if (n == 0) {
    power.string_ += "&";
  }
  else {
    for (int i = 0; i < n; ++i) {
      power.string_ += string_;
    }
  }
  return power;
}

/** @brief Sobrecarga del operador de comparación "<"
  * @param[in] string_1. Primera cadena de la comparación
  * @param[in] string_2. Segunda cadena de la comparación
  * @return Devuelve el valor booleano de la comparación
  */
bool operator<(String string_1, String string_2) {
  return string_1.GetLength() < string_2.GetLength();
}

/** @brief Sobrecarga del operador de comparación "=="
  * @param[in] string_1. Primera cadena de la comparación
  * @param[in] string_2. Segunda cadena de la comparación
  * @return Devuelve el valor booleano de la comparación
  */
bool operator==(String string_1, String string_2) {
  return string_1.GetString() == string_2.GetString();
}

/** @brief Sobrecarga del operador de inserción
  * @param[in] input. Flujo de entrada
  * @param[in] string. Cadena tipo String donde se va a guardar la entrada
  * @return Devuelve el flujo de entrada dado a la función
  */
std::ifstream& operator>>(std::ifstream& input, String string) {
  std::string text_line;
  std::getline(input, text_line);
  if (text_line != "") {
    for (unsigned i = 0; i < text_line.length(); ++i) {
      std::string character;
      character += text_line[i];
      string.string_ += character;
    }
  }
  return input;
}

/** @brief Sobrecarga del operador de extracción
  * @param[in] output. Flujo de salida
  * @param[in] string. Cadena tipo String que se va a extraer
  * @return Devuelve el flujo de salida dado a la función
  */
std::ostream& operator<<(std::ostream& output, const String& string) {
  output << string.GetString();
  return output;
}