// Copyright 2021 GHA Test Team

#include <gtest/gtest.h>

#include <cstdlib>

#include <algorithm>
#include <fstream>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <string>

#include "textgen.h"

using std::istream_iterator;
using std::istringstream;
using std::ifstream;
using std::remove;
using std::runtime_error;
using std::string;

TEST(TextGeneratorTest, PrefixFormation) {
  TextGenerator generator;
  istringstream input("one two three four");
  generator.build(input);

  ASSERT_EQ(generator.initialPrefix.size(), TextGenerator::NPREF);
}

TEST(TextGeneratorTest, PrefixSuffixEntrySingle) {
  TextGenerator generator;
  istringstream input("one two three");
  generator.build(input);

  TextGenerator::prefix p = {"one", "two"};
  ASSERT_EQ(generator.statetab[p].size(), 1);
  ASSERT_EQ(generator.statetab[p][0], "three");
}

TEST(TextGeneratorTest, PrefixSuffixEntryMultiple) {
  TextGenerator generator;
  istringstream input("one two three one two four one two five");
  generator.build(input);

  TextGenerator::prefix p = {"one", "two"};
  ASSERT_EQ(generator.statetab[p].size(), 3);
}

TEST(TextGeneratorTest, SingleSuffixSelection) {
  TextGenerator generator;
  istringstream input("one two three");
  generator.build(input);

  TextGenerator::prefix p = {"one", "two"};
  string next = generator.statetab[p][0];
  ASSERT_EQ(next, "three");
}

TEST(TextGeneratorTest, MultipleSuffixSelection) {
  TextGenerator generator;
  istringstream input("one two three one two four one two five");
  generator.build(input);

  srand(0);
  TextGenerator::prefix p = {"one", "two"};
  unsigned int seed = time(nullptr);
  size_t index = rand_r(&seed) % generator.statetab[p].size();
  ASSERT_TRUE(index >= 0 && index < generator.statetab[p].size());
}

TEST(TextGeneratorTest, TextGenerationLength) {
  TextGenerator generator;
  istringstream input("one two three four five six seven eight nine ten");
  generator.build(input);

  const string testFile = "test_output.txt";
  generator.generate(5, testFile);

  ifstream in(testFile);
  string generatedText;
  getline(in, generatedText);

  istringstream iss(generatedText);
  int wordCount = distance(istream_iterator<string>(iss),
                           istream_iterator<string>());

  ASSERT_EQ(wordCount, 5 + TextGenerator::NPREF);
  remove(testFile.c_str());
}

TEST(TextGeneratorTest, EmptyInputFile) {
  TextGenerator generator;
  istringstream input("");

  EXPECT_THROW(generator.build(input), runtime_error);
}

TEST(TextGeneratorTest, PunctuationHandling) {
  TextGenerator generator;
  istringstream input("Hello, world! How are you?");
  generator.build(input);

  TextGenerator::prefix p = {"Hello,", "world!"};
  ASSERT_EQ(generator.statetab[p][0], "How");
}

TEST(TextGeneratorTest, RepeatedSequences) {
  TextGenerator generator;
  istringstream input("a b c a b d a b e");
  generator.build(input);

  TextGenerator::prefix p = {"a", "b"};
  ASSERT_EQ(generator.statetab[p].size(), 3);
}

TEST(TextGeneratorTest, FileOutputTest) {
  TextGenerator generator;
  istringstream input("this is a test for file output");
  generator.build(input);

  const string testFile = "test_output.txt";
  generator.generate(5, testFile);

  ifstream in(testFile);
  ASSERT_TRUE(in.good());

  string content;
  getline(in, content);
  ASSERT_FALSE(content.empty());

  remove(testFile.c_str());
}

TEST(TextGeneratorTest, SpecialCharactersHandling) {
  TextGenerator generator;
  istringstream input("word1 $%^ word2 @#$ word3");
  generator.build(input);

  TextGenerator::prefix p = {"word1", "$%^"};
  ASSERT_EQ(generator.statetab[p].size(), 1);
  ASSERT_EQ(generator.statetab[p][0], "word2");
}

TEST(TextGeneratorTest, RepeatedWordsHandling) {
  TextGenerator generator;
  istringstream input("word word word word word");
  generator.build(input);

  TextGenerator::prefix p = {"word", "word"};
  ASSERT_GE(generator.statetab[p].size(), 1);
}