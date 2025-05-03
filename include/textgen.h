#ifndef TEXTGEN_H
#define TEXTGEN_H

#include <deque>
#include <map>
#include <vector>
#include <string>

const int NPREF = 2;
const int MAXGEN = 1000;

typedef std::deque<std::string> prefix;
typedef std::map<prefix, std::vector<std::string>> statetab;

class MarkovTextGenerator {
    private:
        statetab table;

    public:
        MarkovTextGenerator();

        std::string generateText();

        void createTable(std::vector<std::string>& words);
};

#endif // TEXTGEN_H