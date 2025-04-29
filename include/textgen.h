#ifndef INCLUDE_TEXTGENERATOR_H_
#define INCLUDE_TEXTGENERATOR_H_
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <random>
#include <deque>
#include <random>

const int NPREF = 2;
const int MAXGEN = 1000;

typedef std::deque<std::string> prefix;

class TextGeneratorClass
{
public:
    TextGeneratorClass(std::string Filepath);
    std::string generateText();

private:
    std::vector<std::string> readWords(std::string Filepath);
    std::map < prefix, std::vector<std::string>> stateTab;
    std::map < prefix, std::vector<std::string>> buildStateTab(std::vector<std::string> words);
    prefix start_prefix;
};

#endif