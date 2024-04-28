// Copyright 2022 GHA Test Team

#include "textgen.h"

std::string Markov::GenerateText(std::string text, int sizePref, int maxLen) {
    std::map<prefix, suffixes> statetab = GenerateStatetab(sizePref, text);

    std::string resStr = "";
    auto pref = statetab.begin()->first;

    for (std::string str : pref)
        resStr += str + " ";

    for (int i = 0; i < maxLen - sizePref; i++) {
        if (statetab[pref].size() < 1)
            return resStr;
        std::string selectSuffix = GetSuffix(statetab[pref]);
        resStr += selectSuffix + " ";

        pref.pop_front();
        pref.push_back(selectSuffix);
    }

    return resStr;
}

std::map<prefix, suffixes> Markov::GenerateStatetab
(int sizePref, std::string text) {
    auto splitText = Split(text);

    std::map<prefix, suffixes> statetab;
    for (int i = 0; i < splitText.size() - sizePref; i++) {
        prefix  pref = prefix();
        for (int j = i; j < sizePref + i; j++) {
            pref.push_back(splitText[j]);
        }

        statetab[pref].push_back(splitText[sizePref + i]);
    }

    return statetab;
}

std::string Markov::GetSuffix(suffixes suffixes) {
    unsigned int seed = 41;
    return suffixes.at(rand_r(&seed) % suffixes.size());
}

std::vector<std::string> Markov::Split(std::string text) {
    std::string delimiter = " ";

    int pos_start = 0, pos_end;
    std::string token;
    std::vector<std::string> splitText;

    while ((pos_end = text.find(" ", pos_start)) != std::string::npos) {
        token = text.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delimiter.length();

        if (token != " " && token != "")
            splitText.push_back(token);
    }

    if (text.substr(pos_start) != "")
        splitText.push_back(text.substr(pos_start));

    return splitText;
}


std::string ReadFile(std::string path) {
    std::string strAns = "";

    std::ifstream file(path);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line))
            strAns += line + "\n";
    }

    file.close();

    return strAns;
}
