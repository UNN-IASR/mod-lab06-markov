// Copyright 2024 Mikhas3009

#include "textgen.h"

namespace markov {
    void MarkovChain::initializeRandomGenerator() {
        mt.seed(static_cast<unsigned int>(time(NULL)));
    }

    void MarkovChain::train(const std::string& filename, int npref) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: unable to open file " << filename << std::endl;
            return;
        }
        Prefix pref;
        std::string word;
        while (file >> word) {
            if (pref.size() < npref) {
                pref.push_back(word);
                continue;
            }
            table[pref].push_back(word);
            pref.pop_front();
            pref.push_back(word);
        }
        file.close();
    }

    std::string MarkovChain::generate(int len, bool randfirst) {
        std::string result = "";
        initializeRandomGenerator();
        auto it = table.begin();
        if (randfirst) {
            std::uniform_int_distribution<> udist(0, table.size()-1);
            std::advance(it, udist(mt));
        }
        Prefix pref = it->first;
        for (const auto& word : pref) {
            result += word + " ";
        }
        for (int i = 0; i < len - pref.size(); i++) {
            if (table[pref].empty()) break;
            std::uniform_int_distribution<> udist(0, table[pref].size()-1);
            std::string next_word = table[pref][udist(mt)];
            result += next_word + " ";
            pref.pop_front();
            pref.push_back(next_word);
        }
        return result;
    }
}// namespace markov
