#include <gtest/gtest.h>

#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <unordered_set>
#include <vector>

#include "textgen.h"

using std::deque;
using std::map;
using std::mt19937;
using std::random_device;
using std::string;
using std::unordered_set;
using std::vector;

TEST(text_generator_test, update_preffix_one) {
  map<deque<string>, vector<string>> state_table = {{{"1", "2"}, {"3"}},
                                                    {{"2", "3"}, {"4"}},
                                                    {{"3", "4"}, {"5"}},
                                                    {{"4", "5"}, {"1"}},
                                                    {{"5", "1"}, {"2"}}};

  TextGenerator gt(state_table);
  deque<string> prefix = {"1", "2"};
  string word = gt.generateSuffix(prefix);
  gt.updatePreffix(prefix, word);
  deque<string> expected = {"2", "3"};
  EXPECT_EQ(expected, prefix);
}
TEST(text_generator_test, update_preffix_two) {
  map<deque<string>, vector<string>> state_table = {{{"1", "2"}, {"3"}},
                                                    {{"2", "3"}, {"4"}},
                                                    {{"3", "4"}, {"5"}},
                                                    {{"4", "5"}, {"1"}},
                                                    {{"5", "1"}, {"2"}}};

  TextGenerator gt(state_table);
  deque<string> prefix = {"4", "5"};

  string word = gt.generateSuffix(prefix);
  gt.updatePreffix(prefix, word);
  deque<string> expected = {"5", "1"};
  EXPECT_EQ(expected, prefix);

  string word = gt.generateSuffix(prefix);
  gt.updatePreffix(prefix, word);
  deque<string> expected = {"1", "2"};
  EXPECT_EQ(expected, prefix);
}
TEST(text_generator_test, update_preffix_three) {
  map<deque<string>, vector<string>> state_table = {
      {{"asd", "word"}, {"asdf"}},
      {{"word", "asdf"}, {"asd"}},
      {{"asdf", "asd"}, {"word"}},
  };

  TextGenerator gt(state_table);
  deque<string> prefix = {"asd", "word"};

  string word = gt.generateSuffix(prefix);
  gt.updatePreffix(prefix, word);
  deque<string> expected = {"word", "asdf"};
  EXPECT_EQ(expected, prefix);

  string word = gt.generateSuffix(prefix);
  gt.updatePreffix(prefix, word);
  deque<string> expected = {"asdf", "asd"};
  EXPECT_EQ(expected, prefix);
}
TEST(text_generator_test, test_preffix_one) {
  map<deque<string>, vector<string>> state_table = {{{"1", "2"}, {"3"}},
                                                    {{"2", "3"}, {"4"}},
                                                    {{"3", "4"}, {"5"}},
                                                    {{"4", "5"}, {"1"}},
                                                    {{"5", "1"}, {"2"}}};

  TextGenerator gt(state_table);
  deque<string> prefix = {"1", "2"};
  string word = gt.generateSuffix(prefix);
  EXPECT_EQ("3", word);

  deque<string> prefix = {"4", "5"};
  string word = gt.generateSuffix(prefix);
  EXPECT_EQ("1", word);
}
TEST(text_generator_test, test_preffix_two) {
  map<deque<string>, vector<string>> state_table = {
      {{"1", "2"}, {"3"}},
      {{"2", "3"}, {"1"}},
      {{"3", "1"}, {"2"}},
  };

  TextGenerator gt(state_table);
  deque<string> prefix = {"1", "2"};
  string word = gt.generateSuffix(prefix);
  EXPECT_EQ("3", word);

  deque<string> prefix = {"3", "1"};
  string word = gt.generateSuffix(prefix);
  EXPECT_EQ("2", word);
}

TEST(text_generator_test, test_preffix_three) {
  map<deque<string>, vector<string>> state_table = {
      {{"asd", "word"}, {"asdf"}},
      {{"word", "asdf"}, {"asd"}},
      {{"asdf", "asd"}, {"word"}},
  };

  TextGenerator gt(state_table);
  deque<string> prefix = {"word", "asdf"};
  string word = gt.generateSuffix(prefix);
  EXPECT_EQ("asd", word);

  deque<string> prefix = {"asdf", "asd"};
  string word = gt.generateSuffix(prefix);
  EXPECT_EQ("word", word);
}

TEST(text_generator_test, test_preffix_four) {
  map<deque<string>, vector<string>> state_table = {
      {{"1", "2"}, {"3", "4"}}, {{"2", "3"}, {"4"}}, {{"2", "4"}, {"5"}},
      {{"3", "4"}, {"5"}},      {{"4", "5"}, {"1"}}, {{"5", "1"}, {"2"}}};

  TextGenerator gt(state_table);
  deque<string> prefix = {"1", "2"};

  vector<string> expected_values = {"3", "4"};

  EXPECT_TRUE(find(expected_values.begin(), expected_values.end(),
                   gt.generateSuffix(prefix)) != expected_values.end());
}

TEST(text_generator_test, test_preffix_five) {
  map<deque<string>, vector<string>> state_table = {
      {{"asd", "word"}, {"asdf", "asd"}},
      {{"word", "asdf"}, {"asd"}},
      {{"asdf", "asd"}, {"word"}},
      {{"word", "asd"}, {"word"}}};

  TextGenerator gt(state_table);
  deque<string> prefix = {"asd", "word"};

  vector<string> expected_values = {"asdf", "asd"};

  EXPECT_TRUE(find(expected_values.begin(), expected_values.end(),
                   gt.generateSuffix(prefix)) != expected_values.end());
}

TEST(text_generator_test, test_gen_text) {
  map<deque<string>, vector<string>> state_table = {
      {{"1", "2"}, {"3"}},
      {{"2", "3"}, {"1"}},
      {{"3", "1"}, {"2"}},
  };

  TextGenerator gt(state_table);
  string text = gt.generateText();
  vector<string> words = TextReader::splitWords(text);

  EXPECT_EQ("3", word[0]);
  EXPECT_EQ("1", word[1]);
  EXPECT_EQ("2", word[2]);
}

TEST(text_generator_test, test_gen_text) {
  map<deque<string>, vector<string>> state_table = {
      {{"asd", "word"}, {"asdf", "asd"}},
      {{"word", "asdf"}, {"asd"}},
      {{"asdf", "asd"}, {"word"}},
      {{"word", "asd"}, {"word"}}};

  TextGenerator gt(state_table);
  string text = gt.generateText();
  vector<string> words = TextReader::splitWords(text);

  vector<string> expected_values = {"asdf", "asd"};
  EXPECT_TRUE(find(expected_values.begin(), expected_values.end(), words[0]) !=
              expected_values.end());

  vector<string> expected_values_two = {"word", "asd"};
  EXPECT_TRUE(find(expected_values.begin(), expected_values.end(), words[1]) !=
              expected_values.end());
}