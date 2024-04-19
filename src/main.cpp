// Copyright 2024 alenkaLo
#include <iostream>
#include "textgen.h"

int main() {
    setlocale(LC_ALL, "Rus");
    const int NPREF = 2; // количество слов в префиксе
    const int MAXGEN = 700; //объем текста на выходе
    std::string path = "InputText.txt";
    std::map<prefix, std::vector<std::string>> statetab;
    statetab = ReadFile(NPREF, path);
    prefix start = { "Умная", "собачка" };
    std::cout << generateText(NPREF, MAXGEN, start, statetab);
}
