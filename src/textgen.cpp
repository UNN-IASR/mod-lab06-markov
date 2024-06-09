// Copyright 2024 CSB

#include "textgen.h"

Markov::Markov(std::string text, int sizePrefix) {
    Markov::sizePrefix = sizePrefix;
    CreateStatetab(SplitText(text));
}

void Markov::CreateStatetab(std::vector<std::string> words) {
    if (words.size() <= sizePrefix)
        throw std::invalid_argument("violation of lengths");

    for (int i = 0; i < words.size() - sizePrefix; i++) {
        prefix  pref = prefix();
        for (int j = i; j < sizePrefix + i; j++) {
            pref.push_back(words[j]);
        }

        statetab[pref].push_back(words[sizePrefix + i]);
    }
}

std::string Markov::GenerateText(prefix pref, int lenght) {
    std::string ans = "";
    unsigned int seed = 1;

    for (std::string str : pref)
        ans += str + " ";

    for (int i = 0; i < lenght - sizePrefix; i++) {
        if (statetab[pref].size() < 1)
            return ans;

        int index = rand_r(&seed) % statetab[pref].size();
        std::string pushWord = statetab[pref].at(index);
        ans += pushWord + " ";

        pref.pop_front();
        pref.push_back(pushWord);
    }

    return ans;
}

std::string Markov::GenerateText(int lenght) {
    std::string ans = "";
    prefix pref = statetab.begin()->first;

    return GenerateText(pref, lenght);
}

std::map<prefix, std::vector<std::string>> Markov::GetStatetab() {
    return statetab;
}

std::vector<std::string> SplitText(std::string text) {
    std::string delimiter = " ";

    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = text.find(delimiter, pos_start)) != std::string::npos) {
        token = text.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;

        if (token != " " && token != "")
            res.push_back(token);
    }

    if (text.substr(pos_start) != "")
        res.push_back(text.substr(pos_start));

    return res;
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
