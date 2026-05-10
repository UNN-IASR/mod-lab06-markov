//Copyright 2026 EnganK

#include "../include/textgen.h"
#include <iostream>
#include <fstream>
#include <deque>
#include <map>
#include <vector>
#include <random>
#include <string>

typedef std::deque<std::string> prefix;
typedef std::map<prefix, std::vector<std::string> > statetab;

void build_table(std::istream& input, statetab& table, int npref) {
    prefix pref;
    std::string word;
    while (input >> word) {
        if (pref.size() == npref) {
            table[pref].push_back(word);
            pref.pop_front();
        }
        pref.push_back(word);
    }
}

void generate_text(statetab& table, int npref, int maxgen) {
    std::random_device rd;
    std::mt19937 gen(rd());
    prefix pref;

    std::vector<prefix> valid_prefixes;
    for (auto& p : table) {
        if (p.first.size() == npref) {
            valid_prefixes.push_back(p.first);
        }
    }

    if (valid_prefixes.empty()) return;

    std::uniform_int_distribution<> prefix_dist(0, valid_prefixes.size() - 1);
    pref = valid_prefixes[prefix_dist(gen)];

    std::ofstream output("../result/gen.txt");

    for (int i = 0; i < npref; ++i) {
        std::cout << pref[i] << (i < npref - 1 ? " " : "");
        output << pref[i] << (i < npref - 1 ? " " : "");
    }

    int count = npref;
    while (count <= maxgen) {
        auto it = table.find(pref);
        if (it == table.end() || it->second.empty()) break;

        std::uniform_int_distribution<> dis(0, it->second.size() - 1);
        std::string next = it->second[dis(gen)];

        std::cout << " " << next;
        output << " " << next;

        ++count;
        pref.pop_front();
        pref.push_back(next);
    }
}
