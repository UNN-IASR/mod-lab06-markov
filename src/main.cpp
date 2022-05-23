// Copyright 2022 UNN-IASR
#include <iostream>
#include <fstream>
#include "textgen.h"

int main() {
    std::setlocale(LC_ALL, "Russian");
    text_generator gener{ 2 };
    gener.power_up("text.txt");
    //gener.print_data_base();
    std::cout << gener.generate_text(100, 5);
}
