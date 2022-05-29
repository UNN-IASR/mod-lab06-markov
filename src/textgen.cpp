// Copyright 2022 UNN-IASR
#include <time.h>
#include <stdlib.h>
#include "textgen.h"

Markov::Markov(std::vector<std::string> words, int prfx_count, int gen_count) {
    NPREF = prfx_count;
    MAXGEN = gen_count;

    for (int i = 0; i < words.size() - NPREF + 1; i++) {
        prefix prfx;
        for (int j = 0; j < NPREF; j++)
            prfx.push_back(words.at(i + j));
        if (i == words.size() - NPREF)
            statelab[prfx].push_back("<Last_Prefix>");
        else
            statelab[prfx].push_back(words.at(i + NPREF));
    }
}

Markov::Markov(std::map<prefix, std::vector<std::string>> Gen, int gen_count) {
    statelab = Gen;
    NPREF = statelab.begin()->first.size();
    MAXGEN = gen_count;
}

std::string Markov::TextGen() {
    srand(time(NULL));
    std::string output;
    std::deque<std::string> words;

    auto it = statelab.begin();
    advance(it, rand() % statelab.size());
    for (int i = 0; i < NPREF; i++)
        words.push_back(it->first.at(i));

    while (output.size() < MAXGEN) {
        prefix prfx;
        for (int i = 0; i < NPREF; i++)
            prfx.push_back(words.at(i));
        unsigned int seed = 1;
        int random = rand_r(&seed) % statelab.find(prfx)->second.size();
        if (statelab.find(prfx)->second.at(random) == "<Last_Prefix>") {
            for (int i = 0; i < NPREF; i++)
                output += words.at(i) + ' ';
            break;
        }
        words.push_back(statelab.find(prfx)->second.at(random));

        output += words.at(0) + ' ';
        words.pop_front();
    }

    return output;
}
