// Copyright 2021 GHA Test Team
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <algorithm>
#include "textgen.h"

textgen::textgen(std::string pathToSource, int prefixLength) {
    ReadSourceFile(pathToSource);
    for (int i = 0; i < tempWords.size() - NPREF; i++) {
        prefix tempPref = GetPref(i);

        std::vector<std::string> tempSuff = GetSuff(tempPref);

        std::map<prefix, std::vector<std::string>>::iterator it
        = statetab.find(tempPref);
        if (it == statetab.end()) {
            statetab.insert(make_pair(tempPref, tempSuff));
        }
    }
}

textgen::prefix textgen::GetPref(int ind) {
    prefix tempPref;
    for (int j = 0; j < NPREF; j++) {
        tempPref.push_back(tempWords[ind + j]);
    }
    return tempPref;
}

std::vector<std::string> textgen::GetSuff(prefix pref) {
    std::vector<std::string> suffix;
    for (int i = 0; i < tempWords.size() - NPREF; i++) {
        int tempSum = 0;
        for (int j = 0; j < NPREF; j++) {
            if (pref[j] == tempWords[i + j]) {
                tempSum++;
            }
        }
        if (tempSum == NPREF) {
            if (std::find(suffix.begin(), suffix.end(),
                tempWords[i + NPREF]) == suffix.end()) {
                suffix.push_back(tempWords[i + NPREF]);
            }
        }
    }
    return suffix;
}

std::string textgen::GetCertainSuffix(textgen::prefix pref) {
    std::string result;

    result = statetab.at(pref)[rand() % statetab.at(pref).size()];
    return result;
}

std::string textgen::CreateText(int wordcount) {
    std::string outputStr;

    int count = 0;
    prefix firstPref = GetPref(0);

    count = count + NPREF;

    for (int i = 0; i < NPREF; i++) {
        outputStr += firstPref[i] + " ";
    }

    prefix tempPref = firstPref;

    while ((count < wordcount) && (GetSuff(tempPref).size() > 0)) {
        std::string tempStr = GetCertainSuffix(tempPref);
        outputStr += tempStr + " ";
        count++;
        for (int i = 0; i < NPREF - 1; i++) {
            tempPref[i] = tempPref[i + 1];
        }
        tempPref[NPREF - 1] = tempStr;
    }

    return outputStr;
}

void textgen::ReadSourceFile(std::string pathToSourceText) {
    std::ifstream infile(pathToSourceText);
    std::string word;
    while (infile >> word) {
        tempWords.push_back(word);
    }
}
