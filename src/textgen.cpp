#include "textgen.h"

#include <unicode/unistr.h>

#include <deque>
#include <exception>
#include <fstream>
#include <iostream>
#include <locale>
#include <regex>

using icu::UnicodeString;
using std::cout;
using std::endl;
using std::ifstream;
using std::locale;
using std::regex;
using std::regex_replace;
using std::string;
using std::tolower;
using std::transform;

TextGenerator::TextGenerator(string filename) {
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
  for (const auto& [prefix, suffixes] : this->table) {
    cout << prefix[0] << " + " << prefix[1] << " = ";
    for (const auto& suffix : suffixes) {
      cout << suffix << " ";
    }
    cout << endl;
  }
}