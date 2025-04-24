#include <fstream>
#include <iostream>
#include <string>
#include <ctime>

#include "textgen.h"

int main() {
    std::ifstream input("../../datasets/checkov.txt");
    TextGenerator gena(input);
    //gena.PrintTable(std::cout);
    std::cout << gena.Generate(100, time(0));
    std::ofstream output("../../result/result.txt");
    output << gena.Generate(1010, time(0));
    output.close();
}
