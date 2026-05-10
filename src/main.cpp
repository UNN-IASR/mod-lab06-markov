#include "textgen.h"
#include <fstream>
#include <iostream>

int main() {
    TextGen gen;

    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Положите 'input.txt' в каталог" << std::endl;
        return 1;
    }

    gen.readText(file);
    file.close();

    std::string final_text = gen.generate(1200);

    std::ofstream out("../result/gen.txt");

    if (!out.is_open()) {
        out.open("gen.txt");
        std::cout << "'result' не найдена в корне" << std::endl;
    }
    else {
        std::cout << "Сохранено в result/gen.txt" << std::endl;
    }

    out << final_text;
    out.close();

    return 0;
}
