// Copyright 2022 UNN-IASR
#include <string>
#include "textgen.h"

int main() {
    TextGeneratorClass tg(INPUT_FILE_PATH);
    std::string text = tg.generateText();
    std::ofstream file(OUTPUT_FILE_PATH);
    file << text;
    file.close();
    return 0;
}
