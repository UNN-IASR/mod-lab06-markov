// Copyright 2025 AirFox

#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <deque>
#include <cstdlib>

#include "../include/textgen.h"

class TextgenTest : public ::testing::Test {
protected:
    const std::string test_input_file = "test_input.txt";
    const std::string test_output_file = "test_output.txt";

    void SetUp() override {
        std::ofstream file(test_input_file);
        file << "one two three four five six\n";
        file.close();
    }

    void TearDown() override {
        std::remove(test_input_file.c_str());
        std::remove(test_output_file.c_str());
    }
};

TEST_F(TextgenTest, SimpleBuildTest) {
    std::ifstream in(test_input_file);
    Chain chain;
    build(in, chain);
    ASSERT_FALSE(chain.empty());
}

TEST_F(TextgenTest, ChainNotEmptyAfterBuild) {
    std::ifstream in(test_input_file);
    Chain chain;
    build(in, chain);
    bool found = false;
    for (auto& [key, value] : chain) {
        if (!value.empty()) found = true;
    }
    ASSERT_TRUE(found);
}

TEST_F(TextgenTest, GenerateProducesOutput) {
    std::ifstream in(test_input_file);
    Chain chain;
    build(in, chain);
    std::ofstream out(test_output_file);
    generate(out, chain);
    out.close();
    std::ifstream inout(test_output_file);
    std::string word;
    inout >> word;
    ASSERT_FALSE(word.empty());
}

TEST_F(TextgenTest, GenerateRespectsChain) {
    std::ifstream in(test_input_file);
    Chain chain;
    build(in, chain);
    std::ofstream out(test_output_file);
    generate(out, chain);
    out.close();
    std::ifstream inout(test_output_file);
    std::string content;
    std::getline(inout, content);
    ASSERT_GT(content.size(), 0);
}

TEST_F(TextgenTest, BuildHandlesEmptyInput) {
    std::ofstream empty("empty.txt");
    empty.close();
    std::ifstream in("empty.txt");
    Chain chain;
    build(in, chain);
    ASSERT_TRUE(chain.empty());
    std::remove("empty.txt");
}

TEST_F(TextgenTest, HandlesRepetition) {
    std::ofstream file("rep.txt");
    file << "a a a a a";
    file.close();
    std::ifstream in("rep.txt");
    Chain chain;
    build(in, chain);
    ASSERT_FALSE(chain.empty());
    std::remove("rep.txt");
}

TEST_F(TextgenTest, ShortInputGeneration) {
    std::ofstream file("short.txt");
    file << "hi there";
    file.close();
    std::ifstream in("short.txt");
    Chain chain;
    build(in, chain);
    std::ofstream out("short_out.txt");
    generate(out, chain);
    out.close();
    std::ifstream inout("short_out.txt");
    std::string content;
    std::getline(inout, content);
    ASSERT_FALSE(content.empty());
    std::remove("short.txt");
    std::remove("short_out.txt");
}

TEST_F(TextgenTest, SuffixMatchesPrefix) {
    std::ifstream in(test_input_file);
    Chain chain;
    build(in, chain);
    for (auto& [key, value] : chain) {
        ASSERT_FALSE(value.empty());
    }
}

TEST_F(TextgenTest, MultipleSuffixes) {
    std::ofstream file("multi.txt");
    file << "a b c\na b d\n";
    file.close();
    std::ifstream in("multi.txt");
    Chain chain;
    build(in, chain);
    int suffix_count = 0;
    for (auto& [key, value] : chain) {
        if (key.back() == "b") suffix_count += value.size();
    }
    ASSERT_GE(suffix_count, 2);
    std::remove("multi.txt");
}

TEST_F(TextgenTest, StableWithRepetitions) {
    std::ofstream file("repeat.txt");
    file << "x y x y x y x y x y";
    file.close();
    std::ifstream in("repeat.txt");
    Chain chain;
    build(in, chain);
    std::ofstream out("repeat_out.txt");
    generate(out, chain);
    out.close();
    std::ifstream inout("repeat_out.txt");
    std::string word;
    inout >> word;
    ASSERT_FALSE(word.empty());
    std::remove("repeat.txt");
    std::remove("repeat_out.txt");
}
