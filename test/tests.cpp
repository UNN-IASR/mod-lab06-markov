// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <set>
#include <string>

#include "textgen.h"

TEST(TextGenTest, PrefixFormationTwoWords) {
  TextGenerator generator;
  std::vector<std::string> words = {"word1", "word2", "word3"};
  prefix pref;
  for (int j = 0; j < 2; j++) pref.push_back(words[j]);
  ASSERT_EQ(pref.size(), 2);
  ASSERT_EQ(pref[0], "word1");
  ASSERT_EQ(pref[1], "word2");
}

TEST(TextGenTest, PrefixFormationThreeWords) {
  TextGenerator generator;
  std::vector<std::string> words = {"word1", "word2", "word3", "word4"};
  prefix pref;
  for (int j = 0; j < 3; j++) pref.push_back(words[j]);
  ASSERT_EQ(pref.size(), 3);
  ASSERT_EQ(pref[2], "word3");
}

TEST(TextGenTest, PrefixSuffixEntrySingleSuffix) {
  TextGenerator generator;
  prefix pref = {"a", "b"};
  statetab table;
  table[pref].push_back("c");
  ASSERT_EQ(table[pref].size(), 1);
  ASSERT_EQ(table[pref][0], "c");
}

TEST(TextGenTest, PrefixSuffixEntryMultipleSuffixes) {
  TextGenerator generator;
  prefix pref = {"x", "y"};
  statetab table;
  table[pref].push_back("z1");
  table[pref].push_back("z2");
  ASSERT_EQ(table[pref].size(), 2);
}

TEST(TextGenTest, SingleSuffixSelection) {
  TextGenerator generator;
  prefix pref = {"one", "two"};
  statetab table;
  table[pref].push_back("three");

  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist(
      0, table[pref].size() - 1);

  std::string nextWord = table[pref][dist(rng)];
  ASSERT_EQ(nextWord, "three");
}

TEST(TextGenTest, MultipleSuffixSelection) {
  TextGenerator generator;
  prefix pref = {"a", "b"};
  statetab table;
  table[pref] = {"c", "d", "e"};

  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist(
      0, table[pref].size() - 1);

  std::string nextWord = table[pref][dist(rng)];
  ASSERT_TRUE(nextWord == "c" || nextWord == "d" || nextWord == "e");
}

TEST(TextGenTest, TextGenerationFixedLength) {
  TextGenerator generator;

  generator.table[{"start", "text"}] = {"next"};
  generator.table[{"text", "next"}] = {"next2"};
  generator.table[{"next", "next2"}] = {"next3"};
  generator.table[{"next2", "next3"}] = {"next4"};
  generator.table[{"next3", "next4"}] = {"next5"};
  generator.table[{"next4", "next5"}] = {"next6"};
  generator.firstPrefix = {"start", "text"};

  std::stringstream outStream;
  std::streambuf* oldCout = std::cout.rdbuf(outStream.rdbuf());

  generator.generateText(5, "test_output.txt");
  std::cout.rdbuf(oldCout);

  std::ifstream inFile("test_output.txt");
  std::string content((std::istreambuf_iterator<char>(inFile)),
                      std::istreambuf_iterator<char>());

  std::istringstream iss(content);
  int wordCount = 0;
  std::string word;
  while (iss >> word) {
    wordCount++;
    std::cout << word << " ";
  }
  std::cout << std::endl;

  ASSERT_EQ(wordCount, 6);
}

TEST(TextGenTest, EmptyFileHandling) {
  TextGenerator generator;
  ASSERT_THROW(generator.createTable("nonexistent.txt", 2), std::runtime_error);
}

TEST(TextGenTest, ShortTextHandling) {
  TextGenerator generator;
  std::ofstream out("short.txt");
  out << "one two";
  out.close();

  ASSERT_THROW(generator.createTable("short.txt", 3), std::runtime_error);
}

TEST(TextGenTest, FirstPrefixSuffixPair) {
  TextGenerator generator;
  std::ofstream out("test.txt");
  out << "a b c d e f";
  out.close();

  generator.createTable("test.txt", 2);
  prefix expectedPrefix = {"a", "b"};
  ASSERT_EQ(generator.table[expectedPrefix][0], "c");
}

TEST(TextGenTest, AllPrefixSuffixPairs) {
  TextGenerator generator;
  std::ofstream out("test.txt");
  out << "a b c d e f";
  out.close();

  generator.createTable("test.txt", 2);

  prefix p1 = {"a", "b"};
  prefix p2 = {"b", "c"};
  prefix p3 = {"c", "d"};
  prefix p4 = {"d", "e"};

  ASSERT_EQ(generator.table[p1][0], "c");
  ASSERT_EQ(generator.table[p2][0], "d");
  ASSERT_EQ(generator.table[p3][0], "e");
  ASSERT_EQ(generator.table[p4][0], "f");
}

TEST(TextGenTest, OutputFileCreation) {
  TextGenerator generator;
  std::ofstream out("test.txt");
  out << "a b c d e f";
  out.close();

  generator.createTable("test.txt", 2);
  generator.generateText(10, "output.txt");

  std::ifstream in("output.txt");
  ASSERT_TRUE(in.good());

  std::string content;
  std::getline(in, content);
  ASSERT_FALSE(content.empty());
}

TEST(TextGenTest, MissingPrefixHandling) {
  TextGenerator generator;
  std::ofstream out("test.txt");
  out << "a b c d e f";
  out.close();

  generator.createTable("test.txt", 2);
  prefix missingPrefix = {"x", "y"};
  ASSERT_TRUE(generator.table[missingPrefix].empty());
}

TEST(TextGenTest, MaxLengthTextGeneration) {
  TextGenerator generator;
  std::ofstream out("test.txt");
  out << "a b c d e f g h i j k l m n o p q r s t u v w x y z";
  out.close();

  generator.createTable("test.txt", 2);
  generator.generateText(100, "max_output.txt");

  std::ifstream in("max_output.txt");
  std::string content;
  std::getline(in, content);

  std::istringstream iss(content);
  int wordCount = 0;
  std::string word;
  while (iss >> word) wordCount++;

  ASSERT_LT(wordCount, 101);
}

TEST(TextGenTest, UniquePrefixesInTable) {
  TextGenerator generator;
  std::ofstream out("test.txt");
  out << "a b c a b d a b e";
  out.close();

  generator.createTable("test.txt", 2);
  prefix p = {"a", "b"};
  ASSERT_EQ(generator.table[p].size(), 3);
}

TEST(TextGenTest, MultipleSuffixesForPrefix) {
  TextGenerator generator;
  std::ofstream out("test.txt");
  out << "a b c a b d a b e";
  out.close();

  generator.createTable("test.txt", 2);
  prefix p = {"a", "b"};

  std::set<std::string> expected = {"c", "d", "e"};
  std::set<std::string> actual;
  for (const auto& word : generator.table[p]) {
    actual.insert(word);
  }

  ASSERT_EQ(actual, expected);
}

TEST(TextGenTest, ThreeWordPrefixGeneration) {
  TextGenerator generator;
  std::ofstream out("test.txt");
  out << "one two three four five six seven eight";
  out.close();

  generator.createTable("test.txt", 3);
  generator.generateText(5, "three_prefix.txt");

  std::ifstream in("three_prefix.txt");
  std::string content;
  std::getline(in, content);

  std::istringstream iss(content);
  int wordCount = 0;
  std::string word;
  while (iss >> word) wordCount++;

  ASSERT_EQ(wordCount, 8);
}

TEST(TextGenTest, RepeatedWordsHandling) {
  TextGenerator generator;
  std::ofstream out("test.txt");
  out << "word word word word word";
  out.close();

  generator.createTable("test.txt", 2);
  prefix p = {"word", "word"};
  ASSERT_EQ(generator.table[p].size(), 3);
}

TEST(TextGenTest, DifferentWhitespaceHandling) {
  TextGenerator generator;
  std::ofstream out("test.txt");
  out << "word1\tword2\nword3  word4 \t\nword5";
  out.close();

  generator.createTable("test.txt", 2);
  std::string word3 = generator.table[{"word1", "word2"}][0];
  std::string word4 = generator.table[{"word2", "word3"}][0];
  std::string word5 = generator.table[{"word3", "word4"}][0];
  ASSERT_EQ(word3, "word3");
  ASSERT_EQ(word4, "word4");
  ASSERT_EQ(word5, "word5");
}
