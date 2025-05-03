#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <clocale>

int main() {
    setlocale(LC_ALL, ".65001");

    const std::string input_filename = "data/book.txt";

    std::ifstream inputFile(input_filename);

    std::string word;
    while (inputFile >> word) {
        std::cout << word << std::endl;
    }

    std::cout << "\nFinished reading." << std::endl;

    return 0;
} 