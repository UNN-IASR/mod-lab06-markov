#include "textgen.h"

TextGeneratorClass::TextGeneratorClass(std::string Filepath)
{
    std::vector<std::string> words = readWords(Filepath);
    stateTab = buildStateTab(words);
}

std::vector<std::string> TextGeneratorClass::readWords(std::string Filepath)
{
    std::vector<std::string> words;
    std::string word;
    std::ifstream file(Filepath);
    while (file >> word)
    {
        words.push_back(word);
    }
    return words;
}

std::map<prefix, std::vector<std::string>> TextGeneratorClass::buildStateTab(std::vector<std::string> words)
{
    std::map<prefix, std::vector<std::string>> newStateTab;
    if (words.size() < NPREF)
        return newStateTab;
    prefix curPrefix(words.begin(), words.begin() + NPREF);
    start_prefix = curPrefix;
    for (int i = NPREF; i < words.size(); ++i)
    {
        newStateTab[curPrefix].push_back(words[i]);
        curPrefix.pop_front();
        curPrefix.push_back(words[i]);
    }
    return newStateTab;
}

std::string TextGeneratorClass::generateText()
{
    std::string genText = "";
    if (stateTab.empty())
        return genText;
    prefix curPrefix = start_prefix;
    for (int i = 0; i < curPrefix.size(); ++i)
    {
        genText += curPrefix[i] + " ";
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    for (int count = NPREF; count < MAXGEN; ++count)
    {
        auto it = stateTab.find(curPrefix);
        if (it == stateTab.end() || it->second.empty())
            break;
        std::vector<std::string> suffixes = it->second;
        std::uniform_int_distribution<> dis(0, suffixes.size() - 1);
        std::string nextWord = suffixes[dis(gen)];
        genText += nextWord + " ";
        if (count % 10 == 0)
            genText += "\n";
        curPrefix.pop_front();
        curPrefix.push_back(nextWord);
    }
    return genText;
}