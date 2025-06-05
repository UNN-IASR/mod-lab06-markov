#ifndef TEXTGEN_H
#define TEXTGEN_H

#include <deque>
#include <map>
#include <vector>
#include <string>

typedef std::deque<std::string> prefix;

class TextGenerator {
private:
    int prefix_len;
    prefix init_pref;
    prefix end_pref;
    std::map<prefix, std::vector<std::string>> statetab;

public:
    TextGenerator(std::string FilePath, int prefix_le);
    explicit TextGenerator(int prefix_le);
    std::string genText(int text_len = 1000, int max_len = 1500);
    std::string genSuffix(prefix pref);
    void addTransition(prefix pref, std::string word);
    prefix getEnd() { return end_pref; }

private:
    void analyzeText(std::string FilePath);
};

#endif // TEXTGEN_H