// Copyright 2025 AirFox

#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include "../include/textgen.h"

TEST(TextgenTest, SimpleBuildTest) {
    std::ofstream file("test_input.txt");
    file << "one two three four five";
    file.close();

    std::ifstream in("test_input.txt");
    Chain chain;
    build(in, chain);
    in.close();

    EXPECT_FALSE(chain.empty());
    EXPECT_GT(chain.size(), 0);

    std::remove("test_input.txt");
}

TEST(TextgenTest, GenerateProducesOutput) {
    std::ofstream file("test_input.txt");
    file << "a b c d e f g h";
    file.close();

    std::ifstream in("test_input.txt");
    Chain chain;
    build(in, chain);
    in.close();

    std::ofstream out("test_output.txt");
    generate(out, chain);
    out.close();

    std::ifstream result("test_output.txt");
    std::string line;
    std::getline(result, line);
    result.close();

    EXPECT_FALSE(line.empty());

    std::remove("test_input.txt");
    std::remove("test_output.txt");
}

TEST(TextgenTest, BuildHandlesEmptyInput) {
    std::ofstream file("empty.txt");
    file.close();

    std::ifstream in("empty.txt");
    Chain chain;
    build(in, chain);
    in.close();

    EXPECT_TRUE(chain.empty());

    std::remove("empty.txt");
}
