// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include "textgen.h"

class TextGeneratorTest : public ::testing::Test {
 protected:
  TextGenerator generator{2, 1000};
  std::stringstream input;
  std::stringstream output;
};

TEST_F(TextGeneratorTest, FormPrefixTwoWords) {
  input << "word1 word2 word3";
  generator.build(input);
  prefix expected = {"word1", "word2"};
  ASSERT_EQ(generator.get_first_prefix(), expected);
}

TEST_F(TextGeneratorTest, FormPrefixOneWord) {
  TextGenerator gen(1, 1000);
  input << "word1 word2";
  gen.build(input);
  prefix expected = {"word1"};
  ASSERT_EQ(gen.get_first_prefix(), expected);
}

TEST_F(TextGeneratorTest, AddPrefixSuffixPair) {
  input << "word1 word2 word3";
  generator.build(input);
  prefix p = {"word1", "word2"};
  auto it = generator.get_state_tab().find(p);
  ASSERT_NE(it, generator.get_state_tab().end());
  ASSERT_EQ(it->second, std::vector<std::string>{"word3"});
}

TEST_F(TextGeneratorTest, AddMultipleSuffixes) {
  input << "word1 word2 word3 word1 word2 word4";
  generator.build(input);
  prefix p = {"word1", "word2"};
  auto it = generator.get_state_tab().find(p);
  ASSERT_NE(it, generator.get_state_tab().end());
  std::vector<std::string> expected = {"word3", "word4"};
  ASSERT_EQ(it->second, expected);
}

TEST_F(TextGeneratorTest, GetRandomSuffixSingle) {
  std::vector<std::string> suffixes = {"suffix1"};
  std::string result = generator.get_random_suffix(suffixes);
  ASSERT_EQ(result, "suffix1");
}

TEST_F(TextGeneratorTest, GetRandomSuffixMultiple) {
  TextGenerator gen(2, 1000);
  std::vector<std::string> suffixes = {"suffix1", "suffix2", "suffix3"};
  std::string result = gen.get_random_suffix(suffixes);
  ASSERT_TRUE(result == "suffix1" || result == "suffix2" || result == "suffix3");
}

TEST_F(TextGeneratorTest, GenerateTextFixedLength) {
  TextGenerator gen(2, 5);
  input << "word1 word2 word3 word4 word5";
  gen.build(input);
  gen.generate(output);
  std::string result = output.str();
  size_t word_count = std::count(result.begin(), result.end(), ' ') + 1;
  ASSERT_LE(word_count, 5);
}

TEST_F(TextGeneratorTest, GenerateTextWithNewlines) {
  TextGenerator gen(2, 12);
  input << "word1 word2 word3 word4 word5 word6 word7 word8 word9 word10 "
           "word11 word12";
  gen.build(input);
  gen.generate(output);
  std::string result = output.str();
  size_t newline_count = std::count(result.begin(), result.end(), '\n');
  ASSERT_EQ(newline_count, 1);
}

TEST_F(TextGeneratorTest, HandleEmptyInput) {
  generator.build(input);
  ASSERT_TRUE(generator.get_state_tab().empty());
  ASSERT_THROW(generator.generate(output), std::runtime_error);
}

TEST_F(TextGeneratorTest, GenerateTextManualTable) {
  TextGenerator gen(2, 4);
  std::stringstream input;
  input << "word1 word2 word3";
  gen.build(input);
  gen.generate(output);
  std::string result = output.str();
  std::string expected = "word1 word2 word3 ";
  ASSERT_EQ(result, expected);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
