// Copyright 2022 UNN-IASR
#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_

#include <string>
#include <deque>
#include <vector>
#include <map>

typedef std::deque<std::string> prefix;

class TextGenerator {
 private:
	int NPREF;
	int MAXGEN;
	std::map<prefix, std::vector<std::string>> statetab;
 public:
	prefix firstPrefix;
	TextGenerator(int NPREF, int MAXGEN);
	void gatherData(std::string filename);
	void generateText(std::ostream& outStream);
	std::vector<std::string> getSuffixes(prefix prefx);
	int getPrefixesCount();
	void addRecord(prefix prefx, std::string suffix);
};

#endif  // INCLUDE_TEXTGEN_H_
