// Copyright 2024 Danil Volkov

#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_

#include <deque>
#include <string>
#include <map>
#include <vector>

typedef std::deque<std::string> Prefix;

class MarkovChain {
 public:
    std::map<Prefix, std::vector<std::string>> stateTable;

    MarkovChain();
    ~MarkovChain();

    void train(const std::string&, int);
    std::string generate(int, unsigned int = 0);
    void trainFromStateTable(
        const std::map<Prefix,
        std::vector<std::string>>&);

 private:
    std::vector<std::string> splitText(const std::string&);
    Prefix startWord;
};

#endif  // INCLUDE_TEXTGEN_H_
