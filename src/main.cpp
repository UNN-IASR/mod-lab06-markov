#include "textgen.h"
#include <fstream>
#include <iostream>
#include <filesystem>

using namespace std;

const int NPREF = 2;
const int MAXGEN = 1000;

typedef deque<string> prefix;
map<prefix, vector<string>> statetab;

int main(int argc, char* argv[]) {
    string inputFile = "input.txt";
    string outputFile = "gen.txt";

    ifstream in(inputFile);
    if (!in) {
        cerr << "Ошибка открытия файла " << inputFile << endl;
        system("pause");
        return 1;
    }

    try {
        TextGenerator generator;
        generator.build(in);
        generator.generate(MAXGEN, outputFile);
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }

    system("pause");
    return 0;
}