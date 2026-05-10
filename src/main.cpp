#include <iostream>
#include <fstream>
#include <vector>
#include "../include/textgen.h"

int main() {
    std::vector<std::string> words;
    std::string word;

    // В реальной задаче лучше читать из файла. 
    // Для примера используем стандартный ввод или тестовый файл.
    std::ifstream infile("input.txt");
    if (infile.is_open()) {
        while (infile >> word) {
            words.push_back(word);
        }
        infile.close();
    }
    else {
        std::cout << "Файл input.txt не найден. Генерация отменена." << std::endl;
        return 1;
    }

    TextGenerator generator;
    generator.train(words);

    std::string generated_text = generator.generate(MAXGEN);

    std::ofstream outfile("result/gen.txt");
    if (outfile.is_open()) {
        outfile << generated_text;
        outfile.close();
        std::cout << "Текст успешно сгенерирован и сохранен в result/gen.txt" << std::endl;
    }
    else {
        std::cout << "Не удалось открыть файл для записи результата." << std::endl;
    }

    return 0;
}