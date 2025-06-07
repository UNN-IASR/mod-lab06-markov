// Copyright 2025 <A-Sabu>

#include "textgen.h"

#include <map>
#include <string>
#include <vector>

Markov::Markov(int npref, int maxgen) : NPREF(npref), MAXGEN(maxgen) {}

Markov::Markov() : NPREF(2), MAXGEN(1000) {}

void Markov::learnFromFile(const std::string& inputFileName) {
  std::ifstream input(inputFileName);
  if (!input)
    throw std::runtime_error("Cannot open input file: " + inputFileName);

  std::string word;
  Prefix prefix;

  for (int i = 0; i < NPREF; ++i)
    prefix.push_back("\n");

  while (input >> word) {
    statetab[prefix].push_back(word);
    prefix.pop_front();
    prefix.push_back(word);
  }

  statetab[prefix].push_back("\n");
}

void Markov::learnFromString(const std::string& inputString) {
  std::istringstream input(inputString);
  std::string word;
  Prefix prefix;

  for (int i = 0; i < NPREF; ++i)
    prefix.push_back("\n");

  while (input >> word) {
    statetab[prefix].push_back(word);
    prefix.pop_front();
    prefix.push_back(word);
  }

  statetab[prefix].push_back("\n");
}

void Markov::generateText() {
  generatedText = "";
  std::srand(std::time(nullptr));
  Prefix prefix;

  for (int i = 0; i < NPREF; ++i)
    prefix.push_back("\n");

  for (int i = 0; i < MAXGEN; ++i) {
    std::vector<std::string>& sufix = statetab[prefix];
    if (sufix.empty())
      break;

    const std::string& next = sufix[std::rand() % sufix.size()];
    if (next == "\n")
      break;

    generatedText += next + " ";
    prefix.pop_front();
    prefix.push_back(next);
  }
}

void Markov::recordGeneratedTextToFile(const std::string& outputFileName) {
  std::ofstream output(outputFileName);
  if (!output)
    throw std::runtime_error("Cannot open output file: " + outputFileName);

  output << generatedText << std::endl;
}

std::map<Markov::Prefix, std::vector<std::string>>& Markov::getStateTable() {
  return statetab;
}

std::string& Markov::getGeneratedText() {
  return generatedText;
}
