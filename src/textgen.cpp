// Copyright 2022 UNN-IASR
#include "textgen.h"

void Generator::AnalisText() {
    ifstream file("text.txt", ios::binary);
    prefix currentPrefix;
    string word;
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

Generator::Generator(string testtext) {
    prefix currentPrefix;
    vector<string> words;
    string currentWord;
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
        string word = words[i];
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

    string text = "";
    auto random_it = statetab.begin();
    advance(random_it, rand() % statetab.size());
    prefix current = random_it->first;

    text += current[0] + ' ' + current[1] + ' ';
    int random;
    int counter = 2;

    while (counter < MAXGEN) {
        if (statetab.count(current) > 0) {
            if (!statetab[current].empty()) {
                random = rand() % statetab[current].size();
                text += statetab[current][random] + ' ';
                counter++;
                string word2 = statetab[current][random];
                current.pop_front();
                current.push_back(word2);
            } else {
                break;
            }
        } else {
            break;
        }
    }
    ofstream out_file(
        "C:/Users/armok/Documents/lebedeva/IASR/mod-lab06-markov/result/result.txt");
    if (out_file.is_open()) {
        out_file << text;
        out_file.close();
        std::cout << "Текст успешно записан в файл" << std::endl;
    } else {
        std::cout << "Ошибка: не удалось открыть файл для записи" << std::endl;
    }
}
