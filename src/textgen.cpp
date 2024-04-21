// Copyright 2024 Ignatyev Artyom

#include "../include/textgen.h"

void Generator::createStatetab(std::istream &source, int prefixSize) {
    Prefix prefix;
    std::string word;
    while (source >> word) {
        if (prefix.size() == prefixSize) {
            statetab[prefix].push_back(word);
            prefix.pop_front();
        }
        prefix.push_back(word);
    }
}

std::string Generator::generateText(int length) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dis(0, statetab.size() - 1);
    auto statetab_it = statetab.begin();
    std::advance(statetab_it, dis(gen));

    Prefix prefix = statetab_it->first;
    std::string res;

    for (const auto &word : prefix)
        res += word + " ";

    for (int i = 0; i < length - prefix.size(); i++) {
        if (statetab[prefix].empty()) break;

        std::uniform_int_distribution<> dis_words(0,
            statetab[prefix].size() - 1);
        int random_index = dis_words(gen);
        std::string word = statetab[prefix][random_index];

        res += word + " ";
        prefix.pop_front();
        prefix.push_back(word);
    }
    return res;
}

void Generator::setStatetab(std::map<Prefix, std::vector<std::string> > _map)
    { statetab = _map; }

std::map<Prefix, std::vector<std::string> > Generator::getStatetab()
    { return statetab; }
