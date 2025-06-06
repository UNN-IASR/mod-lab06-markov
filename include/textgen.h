// Copyright 2022 UNN-IASR
#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_

#include <deque>
#include <map>
#include <vector>
#include <string>
#include <random>

typedef std::deque<std::string> prefix;
typedef std::map<prefix, std::vector<std::string>> StateTab;

class TextGenerator {
 public:
  explicit TextGenerator(int npref = 2, int maxgen = 1000);
  void build(std::istream& in);
  void generate(std::ostream& out);

  const prefix& get_first_prefix() const { return first_prefix; }
  const StateTab& get_state_tab() const { return state_tab; }
  std::string get_random_suffix(const std::vector<std::string>& suffixes);

 private:
  int NPREF;
  int MAXGEN;
  StateTab state_tab;
  prefix first_prefix;

  std::mt19937 gen;

  void add_suffix(const prefix& p, const std::string& s);
};

#endif  // INCLUDE_TEXTGEN_H_
