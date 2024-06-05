#include "textgen.h"
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <random>
#include  <iterator>

//Copyright 2024

std::vector<std::string>::iterator TextGen::select_randomly
(std::vector<std::string>::iterator start,
std::vector<std::string>::iterator end, std::mt19937 g) {
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(g));
    return start;
}

std::vector<std::string>::iterator TextGen::select_randomly
(std::vector<std::string>::iterator start,
 std::vector<std::string>::iterator end) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return select_randomly(start, end, gen);
}

TextGen::TextGen(std::string filePath) {
    std::string line;

    std::ifstream in(filePath);
    if (in.is_open()) {
        while (std::getline(in, line)) {}
    } else {
        std::cout << "cant open" << "\n";
    }
    in.close();     // закрываем файл

    char separator = ' ';
    int i = 0;

    std::vector<std::string> words;

    // Temporary string used to split the string.
    std::string s;
    while (line[i] != '\0') {
        if (line[i] != separator) {
            // Append the char to the temp string.
            s += line[i];
        } else {
            words.push_back(s);
            s.clear();
        }
        i++;
    }

    words.push_back("end");
    auto it = words.insert(words.begin(), "start");

    for (int i = 0; i < words.size() - 1; i++) {
        std::string elem = words[i];
        if (states.count(elem) == 0) {
            states[elem] = std::vector<std::string>();
            states[elem].push_back(words[i+1]);
        } else {
            states[elem].push_back(words[i+1]);
        }
    }

    states["end"] = std::vector<std::string>();
}

std::string TextGen::Generate(int n) {
    std::string result;
    std::string curr = "start";

    for (int i = 0; i < n;) {
        curr = *select_randomly(states[curr].begin(), states[curr].end());
        if (curr == "end") {
            curr = "start";
        } else {
            result += " ";
            result += curr;
            i++;
        }
    }
    return result;
}
