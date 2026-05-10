#include "textgen.h"
#include <fstream>
#include <iostream>

int main() {
    TextGen gen;

    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Place 'input.txt' in the working directory." << std::endl;
        return 1;
    }

    gen.readText(file);
    file.close();

    std::string final_text = gen.generate(1200);

    std::ofstream out("../result/gen.txt");

    if (!out.is_open()) {
        out.open("gen.txt");
        std::cout << "Warning: folder 'result' not found in root. Saved to current folder." << std::endl;
    }
    else {
        std::cout << "Success! Text saved to result/gen.txt" << std::endl;
    }

    out << final_text;
    out.close();

    return 0;
}
