// Copyright 2025 UNN
#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<queue>

class TextGen{
    private:
    typedef std::deque<std::string> prefix;
    std::map<prefix, std::vector<std::string>> statetab;
    const int NPREF=2; // количество слов в префиксе
    const int MAXGEN=1000; //объем текста на выходе

    public:
    TextGen(std::string& filename);
    TextGen(std::map<prefix, std::vector<std::string>>& table) : statetab(table) {}
    void Generate(std::string& filename, const int seed, const int MaxX = -1);
};
#endif // INCLUDE_TEXTGEN_H_