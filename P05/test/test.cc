#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

int main() {
  /*std::vector<std::string> outputs;
  std::cout << "Reading from input.txt...\n";
  std::ifstream infile("test.txt");
  while(infile) {
    std::string temp;
    std::getline(infile, temp);
    std::cout << temp << std::endl;
    std::string val;
    std::stringstream ss(temp);
    while (ss >> val) {
      std::cout << "Valor separado: " << val << "\n";
    }
  }*/
  std::vector <int> v = {1, 2, 3, 4, 5, 6, 7, 8};
  for (int i = 0; i < v.size(); i += 2) {
    cout << v[i] << endl;
  }
  return 0;
}