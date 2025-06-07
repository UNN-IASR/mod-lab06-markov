#include "textgen.h"

int main(int argc, char* argv[]) {
    SetConsoleOutputCP(CP_UTF8);
    Markov generator;
    generator.learnFromFile("input.txt");
    generator.generateText();
    generator.recordGeneratedTextToFile("gen.txt");
    std::cout << generator.getGeneratedText() << std::endl;
    return 0;
}