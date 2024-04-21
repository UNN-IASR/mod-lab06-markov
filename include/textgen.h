// Copyright 2024 StatsenkoArs

#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_


#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <ctime>
#include <random>

const int NPREF = 2;  // количество слов в префиксе
const int MAXGEN = 1000;  // объем текста на выходе
typedef std::deque<std::string> prefix;  // очередь префиксов

class Markov {
 public:
    Markov();

    ~Markov();

    std::map<prefix, std::vector<std::string>> statetab;  // префикс-суффиксы

    std::vector<std::string> mySplit(std::string, char);

    std::string gen(std::string text);

    void gen_tab(std::string, int);

    prefix gen_pre(std::vector<std::string>, int, int);

    std::string gen_text(int);

    std::string pick_next(prefix);

    std::string prefixToString(prefix);
};

#endif  // INCLUDE_TEXTGEN_H_
