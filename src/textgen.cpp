// Copyright 2024 Nekkozzz

#include "textgen.h"

void generator::train(std::istream &source, int prefix_size) {
    prefix prefix;
    std::string word;
    while (source >> word) {
        if (prefix.size() == prefix_size) {
            map[prefix].push_back(word);
            prefix.pop_front();
        }
        prefix.push_back(word);
    }
}

std::string generator::generate_text(int length, unsigned int seed) {
    auto map_it = map.begin();
    std::advance(map_it, rand_r(&seed) % map.size());
    prefix prefix = map_it->first;
    std::string res;
    for (auto it = prefix.begin(); it != prefix.end(); ++it)
        res += *it + " ";
    for (int i = 0; i < length - prefix.size(); i++) {
        if (map[prefix].empty()) break;
        std::string word = map[prefix][rand_r(&seed) % map[prefix].size()];
        res += word + " ";
        prefix.pop_front();
        prefix.push_back(word);
    }
    return res;
}

void generator::set_map(std::map<prefix, std::vector<std::string> > _map)
    { map = _map; }
std::map<prefix, std::vector<std::string> > generator::get_map()
    { return map; }
