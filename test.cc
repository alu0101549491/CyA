#include <iostream>

using namespace std;

int input() {
  int variable;
  cout << "Introduce un número entre el 1 y el 10: ";
  cin >> variable;
  return variable;
}

int main() {
  int variable = input();
  if (variable < 1 || variable > 10) {
    cout << "Ese número no es válido" << endl;
    main();
  }
  else {
    for (int i = 0; i < variable; ++i) {
      cout << "que pelotudo que sos xd" << endl;
    }
  }
  return 0;
}