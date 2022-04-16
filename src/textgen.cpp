// Copyright 2022 UNN-IASR
// #pragma once
#include "textgen.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <sstream>
#include <fstream>
#include <random>


TextGenerator::TextGenerator(std::string file) {
    my_file = file;
}


void TextGenerator::get_connected() {
    prefix pairs;
    for (int i = 0; i < prefixes.size()-2; i++) {
        pairs.push_back(prefixes[i]);
        pairs.push_back(prefixes[i+1]);
        statetab.insert(make_pair(pairs, suffix[i]));
        pairs.clear();
    }
}


std::string TextGenerator::get_result(int size) {
    std::string text[MAXGEN];
    std::string output;
    prefix two_elem;
    std::vector <std::string> suf;

    text[0] = prefixes[0];
    text[1] = prefixes[1];

    two_elem.push_back(text[0]);
    two_elem.push_back(text[1]);

    output = text[0] + " " + text[1] + " ";

    for (int i = 2; i < size-2; i++) {
        suf = statetab.at(two_elem);
        if (suf.size() == 0) {
            break;
        }
        std::random_device rd;
        std::default_random_engine e1(rd());
        std::uniform_int_distribution<int> uniform_dist(0, suf.size()-1);
        int randint = uniform_dist(e1);
        text[i] = suf[randint];
        output += text[i] + " ";
        two_elem.erase(two_elem.begin());
        two_elem.push_back(text[i]);
    }
    return output;
}


void TextGenerator::generate(int size) {
    read_from_file();
    get_words();
    find_suffix();
    get_connected();
    std::string result = get_result(size);
    write_to_file(result);
}


void TextGenerator::write_to_file(std::string str) {
    std::ofstream out;
    out.open("output.txt");
    if (out.is_open()) {
        out << str << std::endl;
    }
}


std::string TextGenerator::get_list_of_strings(std::string text) {
    std::string delim(" ");
    size_t prev = 0;
    size_t next;
    size_t delta = delim.length();

    while ((next = text.find(delim, prev)) != std::string::npos) {
        std::string str = text.substr(prev, next-prev);
        slova.push_back(text.substr(prev, next-prev));
        prev = next + delim.length();
    }
    std::string str = text.substr(prev);
    return str;
}


void TextGenerator::get_words() {
    std::string text = "";
    std::ifstream in(my_file);

    if (!in.fail()) {
        while (!in.eof()) text += in.get();
        in.close();
    } else {
        std::cout << "File not found." << std::endl;
    }

    slova.push_back(get_list_of_strings(text));

    for (int i = 0; i < slova.size(); i++) {
        prefixes.push_back(slova[i]);
    }
}


void TextGenerator::find_suffix() {
    std::vector<std::string> results;
    for (int k = 1; k < slova.size()-1; k++) {
        for (int j = 1; j < slova.size()-1; j++) {
            if (prefixes[k] == slova[j]) {
                results.push_back(slova[j+1]);
            }
        }
        suffix.push_back(results);
        results.clear();
    }
}


void TextGenerator::read_from_file() {
    std::ifstream myfile;
    myfile.open(my_file);

    if (myfile.is_open()) {
        myfile >> words;
    } else {
        std::cout << "Error!" << std::endl;
    }
}
