// Copyright 2024 Matvey Bobrov
#include "textgen.h"
#include <fstream>
#include <vector>
#include <map>

std::string Generator::GenerateText(std::string text, int npref, int maxgen) {
    std::string result;
    std::map<prefix, suffix> table = GenerateTable(npref, text);
    prefix pref = table.begin()->first;
    std::srand(time(nullptr));
    std::vector<std::string> words;
    words = Split(result, " ");
    while (words.size() + npref <= maxgen) {
        if (table.find(pref) == table.end()) {
            break;
        }
        suffix suf = table[pref];
        int id = std::rand() % suf.size();
        result += suf[id] + " ";
        pref.pop_front();
        pref.push_back(suf[id]);
        words = Split(result, " ");
    }

    return result;
}

std::map<prefix, suffix> Generator::GenerateTable(int npref, std::string text) {
    std::map<prefix, suffix> table = std::map<prefix, suffix>();
    prefix pref = prefix();
    std::vector<std::string> words = Split(text, " ");
    for (int i = 0; i < npref; i++) {
        pref.push_back(words[i]);
    }
    for (int i = npref; i < words.size(); i++) {
        if (table.find(pref) == table.end()) {
            suffix suf = suffix();
            suf.push_back(words[i]);
            table[pref] = suf;
        } else {
            table[pref].push_back(words[i]);
        }
        pref.pop_front();
        pref.push_back(words[i]);
    }
    return table;
}

std::vector<std::string> Split(std::string text, std::string separator) {
    int pos_start = 0, pos_end;
    std::string token;
    std::vector<std::string> result;

    while ((pos_end = text.find(" ", pos_start)) != std::string::npos) {
        token = text.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + separator.length();

        if (token != " " && token != "")
            result.push_back(token);
    }

    if (text.substr(pos_start) != "")
        result.push_back(text.substr(pos_start));

    return result;
}

std::string ReadFile(std::string path) {
    std::string result = "";

    std::ifstream file(path);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line))
            result += line;
    }

    file.close();

    return result;
}
