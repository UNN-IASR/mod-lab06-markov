// Copyright 2021 GHA Test Team
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <algorithm>
#include "textgen.h"



TextGen::prefix TextGen::GetPref(int ind) {
    prefix temporaryPrefix;
    for (int j = 0; j < NPREF; j++) {
        temporaryPrefix.push_back(temporary[ind + j]);
    }
    return temporaryPrefix;
}

std::vector<std::string> TextGen::ChooseSuffix(prefix pref) {
    std::vector<std::string> suffix;
    for (int i = 0; i < temporary.size() - NPREF; i++) {
        int temporarySum = 0;
        for (int j = 0; j < NPREF; j++) {
            if (pref[j] == temporary[i + j]) {
                temporarySum++;
            }
        }
        if (temporarySum == NPREF) {
            if (std::find(suffix.begin(), suffix.end(),
                temporary[i + NPREF]) == suffix.end()) {
                suffix.push_back(temporary[i + NPREF]);
            }
        }
    }
    return suffix;
}
TextGen::TextGen(std::string FileAddress, int Prefix_Length) {
    ReadSourceFile(FileAddress);
    for (int i = 0; i < temporary.size() - NPREF; i++) {
        prefix temporaryPrefix = GetPref(i);

        std::vector<std::string> tempSuff = ChooseSuffix(temporaryPrefix);

        std::map<prefix, std::vector<std::string>>::iterator it
            = statetab.find(temporaryPrefix);
        if (it == statetab.end()) {
            statetab.insert(make_pair(temporaryPrefix, tempSuff));
        }
    }
}

std::string TextGen::ChooseAnySuffix(TextGen::prefix pref) {
    std::string result;

    result = statetab.at(pref)[rand() % statetab.at(pref).size()];
    return result;
}

void TextGen::ReadSourceFile(std::string pathToSourceText) {
    std::ifstream infile(pathToSourceText);
    std::string word;
    while (infile >> word) {
        temporary.push_back(word);
    }
}

std::string TextGen::CreateText(int wordcount) {
    std::string outputStr;

    int count = 0;
    prefix firstPref = GetPref(0);

    count = count + NPREF;

    for (int i = 0; i < NPREF; i++) {
        outputStr += firstPref[i] + " ";
    }

    prefix temporaryPref = firstPref;

    while ((count < wordcount) && (ChooseSuffix(temporaryPref).size() > 0)) {
        std::string tempStr = ChooseAnySuffix(temporaryPref);
        outputStr += tempStr + " ";
        count++;
        for (int i = 0; i < NPREF - 1; i++) {
            temporaryPref[i] = temporaryPref[i + 1];
        }
        temporaryPref[NPREF - 1] = tempStr;
    }

    return outputStr;
}
