// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>

#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <string>
#include <random>
#include "textgen.h"

TEST(TextGeneratorTest, FileNotFoundThrowsException) {
    TextGenerator generator(2, 100);
    EXPECT_THROW(generator.gatherData("non_existent_file.txt"), 
        std::runtime_error);
}

TEST(TextGeneratorTest, SingleWordPrefix) {
    TextGenerator generator(1, 100);
    std::ofstream out("test1.txt");
    out << "one two three two five four";
    out.close();
    generator.gatherData("test1.txt");
    EXPECT_EQ(generator.getPrefixesCount(), 4);
    prefix firstPrefix = { "one" };
    EXPECT_EQ(generator.firstPrefix, firstPrefix);
}

TEST(TextGeneratorTest, NotEnoughWordsInFile) {
    TextGenerator generator(2, 100);
    std::ofstream out("test2.txt");
    out << "one";
    out.close();
    generator.gatherData("test2.txt");
    EXPECT_EQ(generator.getPrefixesCount(), 0);
}

TEST(TextGeneratorTest, PrefixSuffixRecordFormation) {
    TextGenerator generator(2, 100);
    std::ofstream out("test3.txt");
    out << "one two three two three four one two";
    out.close();
    generator.gatherData("test3.txt");
    prefix prefx = { "two", "three" };
    std::vector<std::string> suffixes = generator.getSuffixes(prefx);
    EXPECT_EQ(suffixes.size(), 2);
    EXPECT_EQ(suffixes[0], "two");
    EXPECT_EQ(suffixes[1], "four");
}

TEST(TextGeneratorTest, MaxGenLimit) {
    const int MAXGEN = 5;
    TextGenerator generator(2, MAXGEN);
    generator.firstPrefix = { "one", "two" };
    generator.addRecord({ "one", "two" }, "three");
    generator.addRecord({ "two", "three" }, "one");
    generator.addRecord({ "three", "one" }, "two");
    std::stringstream strStream;
    generator.generateText(strStream);
    std::istringstream iss(strStream.str());
    int wordCount = 0;
    std::string word;
    while (iss >> word) {
        wordCount++;
    }
    EXPECT_EQ(wordCount, 2 + MAXGEN);
}

TEST(TextGeneratorTest, SelectRandomSingleSuffix) {
    TextGenerator generator(2, 100);
    std::ofstream out("test3.txt");
    out << "one two three two three four one two";
    out.close();
    generator.gatherData("test3.txt");
    prefix prefx = { "four", "one" };
    std::vector<std::string> suffix = generator.getSuffixes(prefx);
    EXPECT_EQ(suffix.size(), 1);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, suffix.size() - 1);
    std::string nextWord = suffix[dist(gen)];
    EXPECT_EQ(nextWord, "two");
}

TEST(TextGeneratorTest, SelectRandomSuffix) {
    TextGenerator generator(2, 100);
    std::ofstream out("test3.txt");
    out << "one two three two three four one two";
    out.close();
    generator.gatherData("test3.txt");
    prefix prefx = { "two", "three" };
    std::vector<std::string> suffix = generator.getSuffixes(prefx);
    EXPECT_EQ(suffix.size(), 2);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, suffix.size() - 1);
    std::string nextWord = suffix[dist(gen)];
    std::vector<std::string> variants = { "two", "four" };
    EXPECT_NE(std::find(variants.begin(), variants.end(), nextWord), 
        variants.end());
}

TEST(TextGeneratorTest, VariousWhitespaceHandling) {
    TextGenerator generator(2, 100);
    std::ofstream out("test4.txt");
    out << "one\ttwo  three\nfour \t five\nsix";
    out.close();
    generator.gatherData("test4.txt");
    EXPECT_EQ(generator.getPrefixesCount(), 4);
    EXPECT_EQ(generator.getSuffixes({ "three", "four" })[0], "five");
}

TEST(TextGeneratorTest, ThreeWordPrefix) {
    TextGenerator generator(3, 100);
    std::ofstream out("test3.txt");
    out << "one two three two three four one two";
    out.close();
    generator.gatherData("test3.txt");
    EXPECT_EQ(generator.getPrefixesCount(), 5);
    prefix expectedFirst = { "one", "two", "three" };
    EXPECT_EQ(generator.firstPrefix, expectedFirst);
    prefix testPrefix = { "three", "two", "three" };
    std::vector<std::string> suffixes = generator.getSuffixes(testPrefix);
    EXPECT_EQ(suffixes.size(), 1);
    EXPECT_EQ(suffixes[0], "four");
}

TEST(TextGeneratorTest, NonExistentPrefixHandling) {
    TextGenerator generator(2, 100);
    std::ofstream out("test3.txt");
    out << "one two three two three four one two";
    out.close();
    generator.gatherData("test3.txt");
    std::vector<std::string> suffixes = 
        generator.getSuffixes({ "apple", "orange" });
    EXPECT_TRUE(suffixes.empty());
}
