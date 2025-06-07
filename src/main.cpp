#include "textgen.h"

int main(int argc, char* argv[]) {
    Markov generator;
    generator.learnFromFile("input.txt");
    generator.generateText();
    generator.recordGeneratedTextToFile("gen.txt");
    return 0;
}
