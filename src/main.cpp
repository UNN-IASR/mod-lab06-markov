// Copyright 2024 Annenko Misha

//#include "textgen.h"
#include "../include/textgen.h"

// количество слов в префиксе
const int NPREF = 2;
//объем текста на выходе
const int MAXGEN = 1000;

std::string Read_and_show_old_text(const std::string& file_name) {
    std::ifstream file(file_name);
    std::string str;
    std::string out_text1;
    while (std::getline(file, str)) {
        std::string g = str;
        if (g.size() == 0) {
            str += " ";
        }
        out_text1 += str;
    }
    file.close();
    return out_text1;
}

int main() {
    setlocale(LC_ALL, "");
    textgen Markov_Chain;
    std::string File_name = "text.txt";
    std::string file_contents = Read_and_show_old_text(File_name);
    Markov_Chain.memorization(file_contents, NPREF);
    std::cout << Markov_Chain.generate__text(MAXGEN, NPREF);
}
