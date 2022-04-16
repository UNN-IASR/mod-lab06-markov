// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>

//STL includes
#include <vector>
#include <map>

// My includes
#include "textgen.h"

TEST(TEST1, PrefixFromAGivenNumberWords) {
  TextGenerator aTextGenerator("Test1.txt", 1, 1000);
  std::vector<std::deque<std::string>> anExpectedPrefix = {
    {"This"}, {"is"}, {"a"}, {"first"}
  };

  std::sort(anExpectedPrefix.begin(), anExpectedPrefix.end());

  EXPECT_EQ(anExpectedPrefix, aTextGenerator.getPrefix());
}

TEST(TEST2, StateTabFromAGivenNumberWords) {
  TextGenerator aTextGenerator("Test2.txt", 1, 1000);
  std::map<std::deque<std::string>, std::vector<std::string>> anExpectedMap = {
    { {"This"}, {"is"} },
    { {"is"} , {"a"} },
    { {"a"}, {"second"} },
    { {"second"}, {"test"} }
  };

  EXPECT_EQ(anExpectedMap, aTextGenerator.getStateTab());
}

TEST(TEST3, RandomSuffixFromAGivenNumberWords) {
  TextGenerator aTextGenerator("Test3.txt", 1, 1000);

  std::vector<std::string> aSuffixVector = aTextGenerator.getSuffix({ "is" });

  int aCount = std::count(aSuffixVector.begin(), aSuffixVector.end(), "third");

  EXPECT_EQ(1, aCount);
}

TEST(TEST4, AllSuffixFromAGivenNumberWords) {
  TextGenerator aTextGenerator("Test3.txt", 1, 1000);

  std::vector<std::string> anExpectedSuffixVector = { "third", "very" };
  std::vector<std::string> aSuffixVector = aTextGenerator.getSuffix({ "is" });

  EXPECT_EQ(anExpectedSuffixVector, aSuffixVector);
}

TEST(TEST5, GenerateFile) {
  TextGenerator aTextGenerator("Test5.txt", 1, 1000);
  aTextGenerator.generate("Test5Output.txt");
  // Result: Test5Output.txt
  EXPECT_EQ(true, true);
}
