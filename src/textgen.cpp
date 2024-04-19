// Copyright 2024 alenkaLo
#include "textgen.h"
std::map<prefix, std::vector<std::string>>
ReadFile(int NPREF, std::string path) {
    prefix pref;
    std::map<prefix, std::vector<std::string>> statetab; // префикс-суффиксы
    std::string word;
    std::ifstream in(path);
    if (in.is_open()) {
        while (in >> word) {
            if (pref.size() < NPREF) {
                pref.push_back(word);
            } else {
                statetab[pref].push_back(word);
                pref.push_back(word);
                pref.pop_front();
            }
        }
    }
    in.close();     // закрываем файл
    return statetab;
}

std::string genWord(std::deque<std::string>(* start),
std::map<std::deque<std::string>,
std::vector<std::string>> statetab, std::string(* text)) {
    std::vector<std::string> variable = statetab[*start];
    int index = 0;
    if (variable.size() > 0) {
        index = std::rand() % variable.size();
        *text = *text + variable[index] + " ";
        (*start).pop_front();
        (*start).push_back(variable[index]);
    }
    return variable[index];
}

std::string generateText(int NPREF, int MAXGEN,
    std::deque<std::string> start,
    std::map<std::deque<std::string>,
    std::vector<std::string>> statetab) {
    std::string text;
    for (int i = 0; i < MAXGEN; i++) {
        genWord(&start, statetab, &text);
    }
    return text;
}

