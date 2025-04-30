#ifndef TEXTGEN_H
#define TEXTGEN_H

#include <deque>
#include <map>
#include <vector>
#include <string>

using Prefix = std::deque<std::string>;

using StateTable = std::map<Prefix, std::vector<std::string>>;

class TextGenerator {
 private:
    StateTable table;
    Prefix currentPrefix;
    int prefixLength;
    std::vector<Prefix> allPrefixes;

 public:
    TextGenerator(int length = 2);
    void learnFromText(const std::string& filename);
    void generateText(int wordCount, const std::string& outputFile);
    std::vector<Prefix> GetAllPrefixes() {
        return allPrefixes;
    }
    StateTable GetTable() {
        return table;
    }
};

#endif