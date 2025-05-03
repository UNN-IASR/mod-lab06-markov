#include "textgen.h"

#include <deque>
#include <map>
#include <vector>
#include <string>
// #include <random>
#include <cstdlib>
#include <ctime>

MarkovTextGenerator::MarkovTextGenerator() {
    srand(static_cast<unsigned int>(time(0)));
}


void MarkovTextGenerator::createTable(std::vector<std::string>& words) {
    prefix currPref;

    for (int i = 0; i < NPREF; i++) {
        currPref.push_back(words[i]);
    }
    
    for (int i = NPREF; i < words.size(); i++) {
        std::string& suffix = words[i];

        table[currPref].push_back(suffix);

        currPref.pop_front();
        currPref.push_back(suffix);
    }

}

std::string MarkovTextGenerator::generateText() {
    std::string result = "";
    prefix currPref = table.begin()->first;

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
        randIndex = rand() % numSuffixes;

        choiceSuffix = suffixes[randIndex];

        result += choiceSuffix;
        result += " ";
        cntWords++;

        currPref.pop_front();
        currPref.push_back(choiceSuffix);
    }

    return result;
}