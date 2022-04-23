// Copyright 2021 GHA Test Team
#pragma once
#include <string>
#include <deque>
#include <map>
#include <vector>

class textgen {
 public:
  typedef std::deque<std::string> prefix;
  std::map<prefix, std::vector<std::string> > statetab;

  int NPREF = 2;
  int MAXGEN = 1000;

  std::vector<std::string> tempWords;

  textgen(std::string pathToSourceFile, int prefixLength);
  void ReadSourceFile(std::string pathToSourceText);
  std::vector<std::string> GetSuff(prefix pr);
  std::string GetCertainSuffix(textgen::prefix pref);
  prefix GetPref(int i);
  std::string CreateText(int wordcount);
};
