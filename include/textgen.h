// Copyright [year] <Copyright Owner>
#pragma once
#include <deque>
#include <string>
#include <map>
#include <vector>

typedef std::deque<std::string> prefix;

class Text_Gen {
 private:
    std::map<prefix, std::vector<std::string>> statetab;
    prefix f_prefix;
 public:
    void set(std::map<prefix, std::vector<std::string>> states);
    void Prefixes(const std::string& inpstr, int prefnum);
    std::map<prefix, std::vector<std::string>> get();
    std::string Text(int generation_seed, int prefixes_amount);
};
