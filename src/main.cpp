// opyright [year] <Copyright Owner>
#include <iostream>
#include <fstream>
#include "textgen.h"
int main() {
    const int NPREF = 2;
    const int MAXGEN = 1000;
    std::ifstream input_stream("test.txt");
    std::string string, line;
    while (std::getline(input_stream, line)) string += line + " ";
    Text_Gen textgen;
    textgen.Prefixes(string, NPREF);
    std::cout << textgen.Text(time(0), MAXGEN);
}
