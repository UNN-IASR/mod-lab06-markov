#include "textgen.h"
#include <fstream>
#include <iostream>
#include <random>

const int NPREF = 2;
const int MAXGEN = 1000;

TextGenerator::TextGenerator(std::string FilePath, int prefix_le) {
    prefix_len = prefix_le;
    analyzeText(FilePath);
}

TextGenerator::TextGenerator(int prefix_le) {
    prefix_len = prefix_le;
}

void TextGenerator::analyzeText(std::string filepath) {
    std::ifstream file(filepath);
    if (!file) {
        throw std::runtime_error("Файл не найден: " + filepath);  // Прерываем выполнение
    }

    prefix pref;
    std::string word;

    // Загрузка начального префикса
    for (int i = 0; i < prefix_len; i++) {
        if (!(file >> word)) {
            throw std::runtime_error("Файл слишком короткий для префикса длины " + std::to_string(prefix_len));
        }
        pref.push_back(word);
    }
    init_pref = pref;

    // Построение таблицы переходов
    while (file >> word) {
        statetab[pref].push_back(word);
        pref.push_back(word);
        pref.pop_front();
    }

    if (statetab.empty()) {
        throw std::runtime_error("Таблица переходов пуста (недостаточно данных в файле)");
    }

    end_pref = pref;
}

std::string TextGenerator::genText(int min_words, int max_words) {
    if (statetab.empty()) return "";

    std::string result;
    prefix current = init_pref;
    int word_count = 0;

    // 1. Добавляем начальный префикс
    for (const auto& word : current) {
        result += word + " ";
        word_count++;
    }

    // 2. Основная генерация
    while (word_count < max_words) {
        // Если достигли конца цепи - начинаем с начала
        if (current == end_pref || !statetab.count(current)) {
            current = init_pref;
            continue;
        }

        std::string next_word = genSuffix(current);
        result += next_word + " ";
        word_count++;

        // Перенос строки для читаемости
        if (word_count % 20 == 0) result += "\n";

        current.push_back(next_word);
        current.pop_front();

        // Прекращаем только после достижения минимума
        if (word_count >= min_words && current == end_pref) {
            break;
        }
    }

    // Удаляем последний пробел
    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }

    return result;
}

std::string TextGenerator::genSuffix(prefix pref) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(0, statetab[pref].size() - 1);
    return statetab[pref][dist(gen)];
}

void TextGenerator::addTransition(prefix pref, std::string word) {
    if (init_pref.empty()) {
        init_pref = pref;
    }
    statetab[pref].push_back(word);
    end_pref = prefix(pref.begin() + 1, pref.end());
    end_pref.push_back(word);
}