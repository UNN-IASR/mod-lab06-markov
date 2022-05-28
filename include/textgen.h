// Copyright 2022 UNN-IASR
#pragma once

#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<deque>
#include<string>
#include<ctime>

class MarkovTextGenerator{
 public:
  typedef std::deque<std::string> prefix;
  std::map<prefix, std::vector<std::string> > statetab;
  std::deque<std::string> start;
  std::deque<std::string> next;
  int NPREF;
  int MAXGEN;
  int countWords = 0;

  MarkovTextGenerator(int kolvo, int size);
  void readFromFile(std::string path);
  void generateNewText();
};
