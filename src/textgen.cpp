// Copyright 2022 UNN-IASR
#include "textgen.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <vector>
#include <map>
#include <deque>
#include <set>
#include <string>

void Generator::AnalisText() {
    std::ifstream file("text.txt");
    prefix currentPrefix;
    std::string word;
    std::string fir;
    std::string sec;
    file >> fir;
    file >> sec;
    first.push_back(fir);
    first.push_back(sec);
    file.seekg(0);
    while (file >> word) {
        if (currentPrefix.size() == NPREF) {
            if (!prefixSet[currentPrefix].count(word) > 0) {
                statetab[currentPrefix].push_back(word);
                prefixSet[currentPrefix].insert(word);
                currentPrefix.pop_front();
                currentPrefix.push_back(word);
            }
        } else {
            if (!word.empty())
                currentPrefix.push_back(word);
        }
    }
    file.close();
}

Generator::Generator(std::string testtext) {
    prefix currentPrefix;
    std::vector<std::string> words;
    std::string currentWord;
    bool inWord = false;
    testtext += ' ';
    for (char c : testtext) {
        if (c == ' ' || c == '\n') {
            if (inWord) {
                words.push_back(currentWord);
                currentWord.clear();
                inWord = false;
            }
        } else {
            currentWord += c;
            inWord = true;
        }
    }
    for (int i = 0; i < words.size(); i++) {
        std::string word = words[i];
        if (currentPrefix.size() == NPREF) {
            if (!prefixSet[currentPrefix].count(word) > 0) {
                statetab[currentPrefix].push_back(word);
                prefixSet[currentPrefix].insert(word);
                currentPrefix.pop_front();
                currentPrefix.push_back(word);
            }
        } else {
            if (!word.empty())
                currentPrefix.push_back(word);
        }
    }
}
void Generator::CreateText() {
    AnalisText();
    srand(time(0));
    if (statetab.empty())
        return;

    int randomIndex;
    auto current = first;
    std::string text = "";
    text += current[0] + ' ' + current[1] + ' ';
    int counter = 2;
    while (counter < MAXGEN) {
        if (statetab.count(current) > 0) {
            if (!statetab[current].empty()) {
                std::uniform_int_distribution<>
                    dist(0, statetab[current].size() - 1);
                std::mt19937 gen(rd());
                randomIndex = dist(gen);
                text += statetab[current][randomIndex] + ' ';
                counter++;
                std::string word2 = statetab[current][randomIndex];
                current.pop_front();
                current.push_back(word2);
            } else {
                break;
            }
        } else {
            break;
        }
    }
    result = text;
    std::ofstream out_file(
        "C:/Users/armok/Documents/lebedeva/IASR/"
        "mod-lab06-markov/result/result.txt");
    if (out_file.is_open()) {
        out_file << text;
        out_file.close();
        std::cout << "Текст успешно записан в файл" << std::endl;
    } else {
        std::cout << "Ошибка: не удалось открыть файл для записи" << std::endl;
    }
}
