// Copyright 2022 UNN-IASR
// #pragma once
#include "../include/textgen.h"
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

void TextGenerator::generate(int size) {
    read();
    get_words();
    make_dictionary();
    get_connected();
    std::string result = calculate(size);
    write(result);
}

void TextGenerator::read() {
    std::ifstream myfile;
    myfile.open(my_file);

    if (myfile.is_open()) {
        myfile >> words;
    } else {
        std::cout << "Error! File can't be opened" << std::endl;
    }
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

    vector_words.push_back(get_list(text));

    for (int i = 0; i < vector_words.size(); i++) {
        prefixes.push_back(vector_words[i]);
    }
}

std::string TextGenerator::get_list(std::string text) {
    std::string delim(" ");
    size_t prev = 0;
    size_t next;
    size_t delta = delim.length();

    while ((next = text.find(delim, prev)) != std::string::npos) {
        std::string str = text.substr(prev, next - prev);
        vector_words.push_back(text.substr(prev, next - prev));
        prev = next + delim.length();
    }
    std::string str = text.substr(prev);
    return str;
}

void TextGenerator::make_dictionary() {
    std::vector<std::string> results;
    for (int k = 1; k < vector_words.size() - 1; k++) {
        for (int j = 1; j < vector_words.size() - 1; j++) {
            if (prefixes[k] == vector_words[j]) {
                results.push_back(vector_words[j + 1]);
            }
        }
        suffix.push_back(results);
        results.clear();
    }
}

void TextGenerator::get_connected() {
    prefix couples;
    for (int i = 0; i < prefixes.size() - 2; i++) {
        couples.push_back(prefixes[i]);
        couples.push_back(prefixes[i + 1]);
        statetab.insert(make_pair(couples, suffix[i]));
        couples.clear();
    }
}

std::string TextGenerator::calculate(int size) {
    std::string text[MAXGEN];
    std::string output;
    prefix two_elem;
    std::vector <std::string> suf;

    text[0] = prefixes[0];
    text[1] = prefixes[1];

    two_elem.push_back(text[0]);
    two_elem.push_back(text[1]);

    output = text[0] + " " + text[1] + " ";

    for (int i = 2; i < size - 2; i++) {
        suf = statetab.at(two_elem);
        if (suf.size() == 0) {
            break;
        }
        std::random_device rd;
        std::default_random_engine e1(rd());
        std::uniform_int_distribution<int> uniform_dist(0, suf.size() - 1);
        int randint = uniform_dist(e1);
        text[i] = suf[randint];
        output += text[i] + " ";
        two_elem.erase(two_elem.begin());
        two_elem.push_back(text[i]);
    }
    return output;
}

void TextGenerator::write(std::string str) {
    std::ofstream out;
    out.open("text.txt");
    if (out.is_open()) {
        out << str << std::endl;
    }
}
