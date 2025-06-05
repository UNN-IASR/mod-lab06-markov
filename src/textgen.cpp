// Copyright 2022 UNN-IASR
#include "textgen.h"

const int DEFAULT_PREFIX = 2;
const int DEFAULT_OUTPUT = 1000;

MarkovChain::MarkovChain(const std::string& inputFile, int prefixSize) : 
    nPrefix(prefixSize) {
    buildStateTable(inputFile);
}

MarkovChain::MarkovChain(int prefixSize) : nPrefix(prefixSize) {}

void MarkovChain::buildStateTable(const std::string& inputFile) {
    std::ifstream input(inputFile);
    PrefixDeque current;
    
    if (!input) {
        std::cerr << "File error!" << std::endl;
        return;
    }
    
    for (int i = 0; i < nPrefix; i++) {
        std::string word;
        if (!(input >> word)) break;
        current.push_back(word);
    }
    firstPrefix = current;
    
    std::string nextWord;
    while (input >> nextWord) {
        transitions[current].push_back(nextWord);
        current.push_back(nextWord);
        current.pop_front();
    }
    lastPrefix = current;
}

std::string MarkovChain::generate(int outputSize) {
    std::string result;
    PrefixDeque current = firstPrefix;
    
    for (const auto& word : current) {
        result += word + " ";
    }
    
    for (int i = 0; i < outputSize - current.size(); i++) {
        if (current == lastPrefix) return result;
        
        std::string next = getNextWord(current);
        result += next + " ";
        
        if (i % 20 == 0) result += "\n";
        
        current.push_back(next);
        current.pop_front();
    }
    return result;
}

std::string MarkovChain::getNextWord(const PrefixDeque& currentPrefix) {
    std::random_device rd;
    std::mt19937 gen(rd());
    const auto& options = transitions.at(currentPrefix);
    std::uniform_int_distribution<> dist(0, options.size() - 1);
    return options[dist(gen)];
}

void MarkovChain::addWordTransition(const PrefixDeque& prefix, const std::string& nextWord) {
    if (firstPrefix.empty()) firstPrefix = prefix;
    transitions[prefix].push_back(nextWord);
    lastPrefix = {prefix.back(), nextWord};
}

PrefixDeque MarkovChain::getFinalPrefix() const {
    return lastPrefix;
}
