// Copyright 2021 GHA Test Team

#include "textgen.h"

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::istream;
using std::mt19937;
using std::ofstream;
using std::remove_if;
using std::runtime_error;
using std::string;
using std::uniform_int_distribution;
using std::vector;

const int TextGenerator::NPREF = 2;

void TextGenerator::add(prefix& p, const string& s) {
  if (p.size() == NPREF) {
    statetab[p].push_back(s);
    p.pop_front();
  }
  p.push_back(s);
}

void TextGenerator::build(istream& in) {
  prefix p;
  string buf;
  bool initialStored = false;
  bool hasData = false;

  while (in >> buf) {
    hasData = true;
    buf.erase(remove_if(buf.begin(), buf.end(),
        [](char c) { return c == '\r' || c == '\n'; }), buf.end());
    if (!buf.empty()) {
      add(p, buf);
      if (!initialStored && p.size() == NPREF) {
        initialPrefix = p;
        initialStored = true;
      }
    }
  }
  if (!hasData) {
    throw runtime_error("Empty input");
  }
}

void TextGenerator::generate(int nwords, const string& outputFile) {
  ofstream out(outputFile);
  if (!out.is_open()) {
    cerr << "Error: cannot open output file " << outputFile << endl;
    return;
  }

  prefix p;
  mt19937 gen(static_cast<unsigned int>(time(nullptr)));

  if (statetab.empty()) {
    cerr << "Error: no data available for text generation" << endl;
    return;
  }

  p = initialPrefix;
  if (statetab.find(initialPrefix) != statetab.end()) {
    p = initialPrefix;
  } else {
    p = statetab.begin()->first;
  }

  for (const auto& word : p) {
    out << word << " ";
  }

  for (int i = 0; i < nwords; ++i) {
    auto it = statetab.find(p);
    if (it == statetab.end() || it->second.empty()) {
      break;
    }

    const vector<string>& suffixes = it->second;
    uniform_int_distribution<size_t> dis(0, suffixes.size() - 1);
    const string& w = suffixes[dis(gen)];

    out << w << " ";

    p.pop_front();
    p.push_back(w);
  }

  out << endl;
  cout << "Text successfully generated and saved to " << outputFile << endl;
}
