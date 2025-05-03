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
using std::locale;
using std::mt19937;
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
    throw std::invalid_argument("Input file not found");
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

string TextGenerator::generateText() {
  deque<string> prefixes = this->randomStart();
  string text = "";
  for (string prefix : prefixes) {
    text += prefix + " ";
  }

  return text;
}