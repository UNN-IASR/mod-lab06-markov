// Copyright 2022 UNN-IASR
#include "textgen.h"

MarkovGenerator::MarkovGenerator(std::string path, int preflen) {
    prefixSize = preflen;
    std::ifstream file(path);
    std::string s;
    for (file >> s; !file.eof(); file >> s) {
        words.push_back(s);
    }

    for (int i = 0; i < words.size() - prefixSize + 1; i++) {
        prefix aFewWords;
        std::vector<std::string> suffixes;

        for (int j = 0; j < prefixSize; j++) {
            aFewWords.push_back(words[i + j]);
        }

        for (int j = 0; j < words.size() - prefixSize; j++) {
            bool toSave = true;
            for (int k = 0; k < prefixSize; k++) {
                if (words[i + k] != words[j + k])
                    toSave = false;
        }
        if (toSave)
            suffixes.push_back(words[j + prefixSize]);
        }

    statetab.insert(make_pair(aFewWords, suffixes));
    }
}

std::string MarkovGenerator::getText(int wordsamount) {
    prefix currentPrefixes;
    for (int i = 0; i < prefixSize; i++) {
        currentPrefixes.push_back(words[i]);
    }
    srand(time(NULL));

    std::string result = currentPrefixes[0] + " " + currentPrefixes[1] + " ";

    for (int i = prefixSize; i < wordsamount - prefixSize; i++) {
        std::vector <std::string> currentSuffix = statetab.at(currentPrefixes);

        if (currentSuffix.size() == 0)
            break;

        int index = rand_r() % currentSuffix.size();
        result += currentSuffix[index] + " ";
        currentPrefixes.erase(currentPrefixes.begin());
        currentPrefixes.push_back(currentSuffix[index]);
    }

    return result;
}

int MarkovGenerator::getPrefixSize() {
    return prefixSize;
}

std::string MarkovGenerator::getSuffix(std::deque<std::string> prefdeq) {
    prefix prefixes;
    for (int i = 0; i < prefdeq.size(); i++)
        prefixes.push_back(prefdeq[i]);

    srand(time(NULL));
    std::vector <std::string> suffix = statetab.at(prefixes);
    int index = rand_r() % suffix.size();
    return suffix[index];
}
