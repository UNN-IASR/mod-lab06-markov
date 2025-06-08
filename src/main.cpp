// Copyright 2024 StatsenkoArs

#include "textgen.h"

int main() {
    std::string line;
    std::string text = "";
    std::ifstream in("input.txt");
    if (in.is_open()) {
        while (std::getline(in, line)) {
            text += line;
        }
    }
    in.close();

    Markov chain;
    std::string gen_text = chain.gen(text);

    std::ofstream out("output.txt");
    if (out.is_open()) {
        out << gen_text;
    }

    return 0;
}
