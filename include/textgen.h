// include/textgen.h
#ifndef TEXTGEN_H
#define TEXTGEN_H

#include <deque>
#include <map>
#include <vector>
#include <string>
#include <random>

class TextGeneratorMarkov {
public:
    TextGeneratorMarkov(int prefixSize = 2, int maxWords = 1000);
    void loadText(const std::string& filename);
    void generateText(const std::string& outputFile);
    
private:
    typedef std::deque<std::string> Prefix;
    std::map<Prefix, std::vector<std::string>> statetab;
    int NPREF;
    int MAXGEN;
    std::mt19937 gen;
    
    void createStateTable(std::istream& input);
    void addSuffix(const Prefix& prefix, const std::string& suffix);
    std::string getRandomSuffix(const Prefix& prefix);
};

#endif // TEXTGEN_H
