// Copyright 2022 UNN-IASR
#pragma once
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <sstream>
#include <fstream>
#include <random>
#include <locale>
#define random rand

typedef std::deque<std::string> prefix;

class TextGenerator {
public:
	int NPREF;
	int MAXGEN;
	std::string NFILE;
	std::string text;
	std::vector<std::string> words;
  std::map<prefix, std::vector<std::string>> stateTab;
	std::string generate();
	void readFile();
	TextGenerator(std::string, int, int);
};
