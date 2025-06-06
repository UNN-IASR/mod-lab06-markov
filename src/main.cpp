// Copyright 2025 cherniuta
#include <iostream>
#include <fstream>
#include <string>
#include "../include/textgen.h"

int main() {
    const int NPREF = 2;
    const int MAXGEN = 1000;

    TextGen generator(NPREF);

    std::string filename = "porosiata.txt";
    generator.train(filename);

    std::string generated_text = generator.generate(MAXGEN);

    std::ofstream outfile("result/gen.txt");
    outfile << generated_text;
    outfile.close();

    std::cout << "Generated text has been saved to result/gen.txt" << std::endl;

    return 0;
}
