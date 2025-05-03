#include "textgen.h"

#include <deque>
#include <map>
#include <vector>
#include <string>

void MarkovTextGenerator::createTable(std::vector<std::string>& words) {
    prefix currPref;

    for (int i = 0; i < NPREF; i++) {
        currPref.push_back(words[i]);
    }
    
    for (int i = NPREF; i < words.size(); i++) {
        std::string& suffix = words[i];

        table[currPref].push_back(suffix);

        currPref.pop_front();
        currPref.push_back(suffix);
    }

}

std::string MarkovTextGenerator::generateText() {
    
}