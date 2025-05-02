// Copyright 2025 sdanils
#pragma once

#include <deque>
#include <map>
#include <random>
#include <string>
#include <vector>

using std::deque;
using std::map;
using std::mt19937;
using std::random_device;
using std::string;
using std::vector;

class TextGenerator {
 private:
  map<deque<string>, vector<string>> state_table;
  random_device rd;
  mt19937 gen;

  const int PREFIX_LEN = 2;
  const int TEXT_LEN = 1000;

  void fillState(vector<string> words);

 public:
  TextGenerator(const string& file_name = "../../source_text.txt");

  TextGenerator(const map<deque<string>, vector<string>>& state_table_);

  string generateText();

  string generateSuffix(deque<string> prefix);

  void updatePreffix(deque<string>& prefix, string& suffix);
};

class TextReader {
 public:
  static void saveText(const string& text,
                       const string& file_name = "../../result/gen.txt");

  static string readText(const string& file_name);

  static string removePunctuation(const string& text);

  static vector<string> splitWords(const string& text);

  static vector<string> getFileText(const string& file_name);
};
