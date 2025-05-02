// Copyright 2025 sdanils
#include "textgen.h"

#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <unordered_set>
#include <vector>

using std::deque;
using std::map;
using std::mt19937;
using std::random_device;
using std::string;
using std::unordered_set;
using std::vector;

void TextGenerator::fillState(vector<string> words) {
  deque<string> prefix(words.begin(), words.begin() + PREFIX_LEN);

  string word;
  for (int i = PREFIX_LEN; i < words.size(); i++) {
    word = words[i];
    state_table[prefix].push_back(word);
    prefix.pop_front();
    prefix.push_back(word);
  }
  for (int i = 0; i < PREFIX_LEN; i++) {
    word = words[i];
    state_table[prefix].push_back(word);
    updatePreffix(prefix, word);
  }
}

TextGenerator::TextGenerator(const string& file_name) {
  vector<string> words = TextReader::getFileText(file_name);
  if (words.size() <= PREFIX_LEN) {
    throw std::runtime_error("недостаточно длины текста.");
  }

  fillState(words);

  mt19937 gen_(rd());
  gen = gen_;
}

TextGenerator::TextGenerator(
    const map<deque<string>, vector<string>>& state_table_) {
  state_table = state_table_;
}

string TextGenerator::generateText() {
  deque<string> prefix = state_table.begin()->first;
  string text;

  for (int i = 0; i < TEXT_LEN; i++) {
    string word = generateSuffix(prefix);

    text += " " + word;
    updatePreffix(prefix, word);
  }

  return text;
}

string TextGenerator::generateSuffix(deque<string> prefix) {
  if (prefix.size() < PREFIX_LEN) {
    throw std::runtime_error("Некорректный перфикс");
  }

  vector<string> suffixs = state_table[prefix];
  size_t number_siffix = suffixs.size();

  std::uniform_int_distribution<int> dist(0, number_siffix - 1);
  int choise = dist(gen);
  return suffixs[choise];
}

void TextGenerator::updatePreffix(deque<string>& prefix, string& suffix) {
  prefix.pop_front();
  prefix.push_back(suffix);
}

void TextReader::saveText(const string& text, const string& file_name) {
  std::ofstream out_file(file_name);
  if (!out_file.is_open()) {
    throw std::runtime_error("Не удалось создать фаил");
  }

  out_file << text;

  out_file.close();
}

string TextReader::readText(const string& file_name) {
  std::ifstream file(file_name);
  if (!file.is_open()) {
    throw std::runtime_error("Не удалось открыть файл: ");
  }
  return string((std::istreambuf_iterator<char>(file)),
                std::istreambuf_iterator<char>());
}

string TextReader::removePunctuation(const string& text) {
  string result;
  unordered_set<char> punct = {',', '.', '!', '?', ':', ';', '"'};
  for (char ch : text)
    if (punct.find(ch) == punct.end()) result += ch;

  return result;
}

vector<string> TextReader::splitWords(const string& text) {
  vector<string> words;
  string current_word;
  unordered_set<char> punct = {' ', '\t', '\n'};

  for (char ch : text) {
    if (punct.find(ch) != punct.end()) {
      if (!current_word.empty()) {
        words.push_back(current_word);
        current_word.clear();
      }
    } else {
      current_word += ch;
    }
  }

  if (!current_word.empty()) words.push_back(current_word);

  return words;
}

vector<string> TextReader::getFileText(const string& file_name) {
  string text = readText(file_name);
  text = removePunctuation(text);
  return splitWords(text);
}
