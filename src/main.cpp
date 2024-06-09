// Copyright 2024 Shelnov Yuriy
#include "textgen.h"
#include"locale.h"

const int NPREF = 2;
//объем текста на выходе
const int MAXGEN = 1000;



int main() {
    setlocale(LC_ALL, "rus");
    std::string File_name = "input_file.txt";
    TextGenerator  TGenerate = TextGenerator(File_name, 2);
    std::cout << TGenerate.getText(MAXGEN) << std::endl;
    TGenerate.WriteOnFileGenerateText(MAXGEN);
}
