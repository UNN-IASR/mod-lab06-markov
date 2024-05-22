// Copyright 2024 Burdeiniy Artem
#include "textgen.h"
#include <fstream>
#include <vector>
#include <map>

std::string Generator::GenerateText(std::string text,
                                        int prefixCount, int genLength) {
    std::string result;
    std::map<prefix, suffix> table = GenerateTable(prefixCount, text);
    prefix pref = table.begin()->first;
    std::srand(time(nullptr));
    std::vector<std::string> words;
    words = Split(result, " ");
    while (words.size() + prefixCount <= genLength) {
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

std::map<prefix, suffix> Generator::GenerateTable(int prefixCount,
                                                    std::string text) {
    std::map<prefix, suffix> table = std::map<prefix, suffix>();
    prefix pref = prefix();
    std::vector<std::string> words = Split(text, " ");
    for (int i = 0; i < prefixCount; i++) {
        pref.push_back(words[i]);
    }
    for (int i = prefixCount; i < words.size(); i++) {
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
    int startPos = 0, endPos;
    std::string token;
    std::vector<std::string> result;

    while ((endPos = text.find(" ", startPos)) != std::string::npos) {
        token = text.substr(startPos, endPos - startPos);
        startPos = endPos + separator.length();

        if (token != " " && token != "")
            result.push_back(token);
    }

    if (text.substr(startPos) != "")
        result.push_back(text.substr(startPos));

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
