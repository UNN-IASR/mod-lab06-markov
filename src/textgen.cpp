// Copyright 2022 UNN-IASR

#include <deque>
#include <map>
#include <vector>
#include <string>
//#include <cstdlib>
//#include <ctime>
#include <random>

#include "textgen.h"

MarkovTextGenerator::MarkovTextGenerator() {
    std::random_device rd;
    rng.seed(rd());
}

void MarkovTextGenerator::createTable(const std::vector<std::string>& words) {
    prefix currPref;

    for (int i = 0; i < NPREF; i++) {
        currPref.push_back(words[i]);
    }

    startPref = currPref;

    for (int i = NPREF; i < words.size(); i++) {
        const std::string& suffix = words[i];

        table[currPref].push_back(suffix);

        currPref.pop_front();
        currPref.push_back(suffix);
    }
}

std::string MarkovTextGenerator::generateText() {
    std::string result = "";
    prefix currPref = startPref;

    for (int i = 0; i < NPREF; i++) {
        result += currPref[i];
        result += " ";
    }

    int cntWords = NPREF;
    int numSuffixes = 0;
    int randIndex = -1;
    std::string choiceSuffix = "";

    while (cntWords < MAXGEN) {
        auto searchElement = table.find(currPref);

        if (searchElement == table.end() || searchElement->second.empty()) {
            break;
        }

        std::vector<std::string>& suffixes = searchElement->second;
        numSuffixes = suffixes.size();
        std::uniform_int_distribution<int> dist(0, suffixes.size() - 1);
        int randIndex = dist(rng);

        choiceSuffix = suffixes[randIndex];

        result += choiceSuffix;
        result += " ";
        cntWords++;

        currPref.pop_front();
        currPref.push_back(choiceSuffix);
    }

    return result;
}
