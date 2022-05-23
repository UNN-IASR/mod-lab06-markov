// Copyright 2022 UNN-IASR
#include <iostream>
#include <random>
#include "textgen.h"
#include "utils.h"

std::default_random_engine& my_engine() {
    static std::default_random_engine e{};
    return e;
}


int randm() { return my_engine()() - my_engine().min(); }


void text_generator::power_up(const std::vector<std::string>& words) {
    if (words.size() < prefix_size + 1) {
        return;
    }
    std::deque<std::string> key;
    for (int i = 0; i < prefix_size; i++) {
        key.push_back(words[i]);
    }
    for (int i = prefix_size; i < words.size(); i++) {
        data_base[key][words[i]]++;
        key.pop_front();
        key.push_back(words[i]);
    }
    for (std::size_t i = prefix_size; i > 0; i--) {
        key.pop_front();
        key.push_back(words[words.size() - i]);
    }
    data_base[key] = std::map<std::string, std::size_t>();
    data_base[key]["."] = 1;

    data_base_power += words.size();
}

void text_generator::power_up(const std::string& file_path) {
    std::ifstream fin;
    fin.open(file_path);
    if (!fin) {
        throw(std::bad_exception());
    }
    std::vector<std::string> words = read_stream(fin);
    fin.close();
    power_up(words);
}

std::string text_generator::generate_text
(std::size_t text_size, std::size_t words_in_line) {
    if (text_size < prefix_size) {
        return "Too small text size\n";
    }
    std::srand(std::time(nullptr));
    std::size_t pos = randm() % data_base.size();
    auto iterator = data_base.begin();
    for (std::size_t i = 0; i < pos; i++) {
        ++iterator;
    }
    std::deque<std::string> key = iterator->first;
    std::string out = "";
    for (auto& s : key) {
        out = out + s + " ";
    }
    std::size_t key_variant_power;
    std::string next_w;
    std::size_t chance;
    std::size_t line_size = prefix_size;
    std::size_t chance_counter = 0;
    for (std::size_t i = prefix_size; i < text_size; i++) {
        if (line_size >= words_in_line) {
            out += "\n";
            line_size = 0;
        }
        key_variant_power = 0;
        for (auto& m : data_base[key]) {
            key_variant_power += m.second;
        }
        chance = randm() % (key_variant_power);
        for (auto& m : data_base[key]) {
            if (m.second + chance_counter >= chance) {
                next_w = m.first;
                chance_counter = 0;
                break;
            }
            chance_counter += m.second;
        }
        if (next_w == ".") {
            out = out + next_w;
            break;
        }
        out = out + next_w + " ";
        key.pop_front();
        key.push_back(next_w);
        ++line_size;
    }
    return out;
}

std::map<std::deque<std::string>, std::map<std::string,
    std::size_t>> text_generator::get_base() {
    return data_base;
}

void text_generator::print_data_base() {
    for (auto& up_map : data_base) {
        std::cout << "[ ";
        for (auto& key : up_map.first) {
            std::cout << key << " ";
        }
        std::cout << "] { ";
        for (auto& down_map : up_map.second) {
            std::cout << down_map.first << " ";
        }
        std::cout << " }\n";
    }
}
