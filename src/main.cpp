// Copyright 2022 UNN-IASR
#include <fstream>
#include "textgen.h"

int main() {
    const int NPREF = 2;
    const int MAXGEN = 1000;
    TextGenerator textgen = TextGenerator(NPREF, MAXGEN);
    textgen.gatherData("../../src/chekhov.txt");
    std::ofstream outFile("../../result/gen.txt");
    textgen.generateText(outFile);
    outFile.close();
}
