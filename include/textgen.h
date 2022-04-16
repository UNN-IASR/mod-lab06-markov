// Copyright 2022 Open Cascade team
// Author: Semen Smirnov
#pragma once

//STL includes
#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <ctime>
#include <random>
#include <fstream>
#include <map>

class TextGenerator {
 private:
  using prefix = std::deque<std::string>;

 public:
  explicit TextGenerator(const std::string& theFilePath) noexcept;

  TextGenerator(const std::string& theFilePath, const int, const int) noexcept;

  TextGenerator() = delete;

 public:
  void setPrefixLength(const int thePrefixLength) noexcept;
  int getPrefixLength() const noexcept;

  void setGeneratedWordsNumber(const int theGenWordsNumber) noexcept;
  int getGeneratedWordsNumber() const noexcept;

  std::vector<prefix> getPrefix() const noexcept;
  std::map<prefix, std::vector<std::string>> getStateTab() const noexcept;
  std::vector<std::string> getSuffix(const prefix& thePrefix) const noexcept;

 public:
  void generate(const std::string& theFilePath);

 private:
  std::map<prefix, std::vector<std::string>> myStateTab;
  prefix myStart;

  int myPrefixLength = 2;
  int myGeneratedWordsNumber = 1000;
};
