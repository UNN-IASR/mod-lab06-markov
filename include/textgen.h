// Copyright 2021 GHA Test Team
#pragma once
#include <string>
#include <deque>
#include <map>
#include <vector>

class TextGen {
 public:
typedef std::deque<std::string> prefix;
int NPREF = 2;
int MAXGEN = 1000;
std::vector<std::string> ChooseSuffix(prefix pr);
std::string ChooseAnySuffix(TextGen::prefix pref);
std::vector<std::string> temporary;
std::string CreateText(int wordcount);
std::map<prefix, std::vector<std::string> > statetab;
TextGen(std::string pathToSourceFile, int prefixLength);
void ReadSourceFile(std::string pathToSourceText);
prefix GetPref(int i);
};
