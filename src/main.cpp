// Copyright 2022 UNN-IASR

#include <iostream>
#include <string>

#include "textgen.h"

int main() {
    const std::string input_file_path = "../../src/input.txt";
    const int NPREF = 2;
    const int MAXGEN = 1000;

    TextGenerator text_generator;

    text_generator.__create_state_table__(input_file_path, NPREF);

    const std::string output_file_path = "../../result/gen.txt";
    text_generator.__generate_text_and_write_to_file__(MAXGEN, output_file_path);

    return 0;
}
