// Copyright 2022 UNN
#include "textgen.h"

Generator::Generator(std::string path) {
    std::ifstream file(path);
    std::string s;
    for (file >> s; !file.eof(); file >> s) {
        text.push_back(s);
    }
    for (int i = 0; i < text.size() - NPREF + 1; i++) {
        prefix prefix;
        std::vector<std::string> suffixes;
        for (int j = 0; j < NPREF; j++) {
            prefix.push_back(text[i + j]);
        }
        for (int j = 0; j < text.size() - NPREF; j++) {
            bool flag = true;
            for (int k = 0; k < NPREF; k++) {
                if (text[i + k] != text[j + k])
                    flag = false;
            }
            if (flag)
                suffixes.push_back(text[j + NPREF]);
        }
        statetab.insert(make_pair(prefix, suffixes));
    }
}

std::string Generator::newText() {
    prefix currPrefix;
    for (int i = 0; i < NPREF; i++) {
        currPrefix.push_back(text[i]);
    }
    srand(time(NULL));
    std::string newtext = currPrefix[0] + " " + currPrefix[1] + " ";
    for (int i = NPREF; i < MAXGEN - NPREF; i++) {
        std::vector <std::string> currSuffix = statetab.at(currPrefix);

        if (currSuffix.size() == 0)
            break;

        int ind = rand() % currSuffix.size();
        newtext += currSuffix[ind] + " ";
        currPrefix.erase(currPrefix.begin());
        currPrefix.push_back(currSuffix[ind]);
    }
    return newtext;
}

std::string Generator::Suffix(std::deque<std::string> pref) {
    prefix prefixes;
    for (int i = 0; i < pref.size(); i++)
        prefixes.push_back(pref[i]);

    srand(time(NULL));
    std::vector <std::string> suffix = statetab.at(prefixes);
    int ind = rand() % suffix.size();
    return suffix[ind];
}
