#include "textgen.h"

#include <deque>
#include <exception>
#include <fstream>
#include <iostream>
#include <locale>
#include <random>
#include <regex>

using std::advance;
using std::cout;
using std::endl;
using std::ifstream;
using std::invalid_argument;
using std::locale;
using std::mt19937;
using std::ofstream;
using std::regex;
using std::regex_replace;
using std::string;
using std::tolower;
using std::transform;
using std::uniform_int_distribution;

TextGenerator::TextGenerator(string filename) {
  this->generator = mt19937(std::random_device{}());

  ifstream file(filename);
  if (!file.is_open()) {
    throw invalid_argument("Input file not found");
  }

  deque<string> words;
  string word;

  while (file >> word) {
    if (words.size() == this->PREFIX_LENGTH) {
      this->table[words].push_back(word);
      words.pop_front();
    }
    words.push_back(word);
  }

  file.close();
}

void TextGenerator::printTable() {
  for (const auto& [prefixes, suffixes] : this->table) {
    for (const auto& prefix : prefixes) {
      cout << prefix << " ";
    }
    cout << " = ";
    for (const auto& suffix : suffixes) {
      cout << suffix << " ";
    }
    cout << endl;
  }
}

deque<string> TextGenerator::randomStart() {
  uniform_int_distribution<size_t> dist(0, this->table.size() - 1);
  auto it = this->table.begin();
  advance(it, dist(this->generator));
  return it->first;
}

string TextGenerator::nextWord(deque<string> prefixes) {
  vector<string> variants = this->table[prefixes];
  if (variants.size() == 0) {
    return this->randomStart()[0];
  }
  uniform_int_distribution<size_t> dist(0, variants.size() - 1);
  return variants[dist(this->generator)];
}

string TextGenerator::generateText(int length) {
  deque<string> prefixes = this->randomStart();
  string text = "";
  for (string prefix : prefixes) {
    text += prefix + " ";
  }

  for (int i = 0; i < length - this->PREFIX_LENGTH; i++) {
    string suffix = this->nextWord(prefixes);
    prefixes.pop_front();
    prefixes.push_back(suffix);
    text += suffix + " ";
  }

  return text;
}

string TextGenerator::generateText(string filename, int length) {
  ofstream file(filename);
  if (!file) {
    throw invalid_argument("Output file create error");
  }

  string data = this->generateText(length);
  file << data;
  file.close();

  return data;
}