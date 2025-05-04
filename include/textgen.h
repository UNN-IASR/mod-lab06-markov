// Copyright 2021 GHA Test Team

#ifndef TEXTGEN_H_
#define TEXTGEN_H_

#include <deque>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class TextGenerator {
 public:
  static const int NPREF = 2;
  static const int MAXGEN = 1000;

  void build(std::istream& in);
  void generate(int nwords, const std::string& outputFile = "gen.txt");
    
  typedef std::deque<std::string> prefix;
  std::map<prefix, std::vector<std::string>> statetab;
  prefix initialPrefix;

  void add(prefix& p, const std::string& s);
};

#endif  // TEXTGEN_H_
