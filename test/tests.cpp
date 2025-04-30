// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include "textgen.h"
#include <sstream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

class TextGenTest : public ::testing::Test {
protected:
    void SetUp() override {
        gen2_.reset(new TextGeneratorMarkov(2));
        gen1_.reset(new TextGeneratorMarkov(1));
        
        createTestFile("test1.txt", "word1 word2 word3 word4");
        createTestFile("test2.txt", "a b c b c a");
        createTestFile("test3.txt", "a b b b b b");
        createTestFile("test4.txt", "a b a c a d");
        createTestFile("test5.txt", "I wish I may I wish I might");
        createTestFile("test6.txt", "a b c");
        createTestFile("test7.txt", "a b c d e f g");
        createTestFile("test8.txt", "a b");
    }

    void TearDown() override {
        for (const auto& entry : fs::directory_iterator(".")) {
            if (entry.path().string().find("test") != std::string::npos) {
                fs::remove(entry.path());
            }
        }
    }

    void createTestFile(const std::string& filename, const std::string& content) {
        std::ofstream out(filename);
        out << content;
        out.close();
    }

    Prefix createPrefix(const std::vector<std::string>& words) {
        Prefix prefix;
        for (const auto& word : words) {
            prefix.push_back(word);
        }
        return prefix;
    }

    std::unique_ptr<TextGeneratorMarkov> gen1_;
    std::unique_ptr<TextGeneratorMarkov> gen2_;
};

TEST_F(TextGenTest, PrefixFormation) {
    gen2_->loadText("test1.txt");
    auto& statetab = gen2_->getStateTable();
    EXPECT_EQ(statetab.size(), 2);
    EXPECT_EQ(statetab.begin()->first.size(), 2);
}

TEST_F(TextGenTest, PrefixSuffixRecord) {
    gen2_->loadText("test2.txt");
    auto& statetab = gen2_->getStateTable();
    
    auto prefix_ab = createPrefix({"a", "b"});
    auto prefix_bc = createPrefix({"b", "c"});
    
    auto it_ab = statetab.find(prefix_ab);
    auto it_bc = statetab.find(prefix_bc);
    
    EXPECT_NE(it_ab, statetab.end());
    EXPECT_NE(it_bc, statetab.end());
    EXPECT_EQ(it_ab->second.size(), 1);
    EXPECT_EQ(it_bc->second.size(), 2);
}

TEST_F(TextGenTest, SingleSuffixSelection) {
    gen1_->loadText("test3.txt");
    auto prefix = createPrefix({"a"});
    EXPECT_EQ(gen1_->getRandomSuffixForTest(prefix), "b");
}

TEST_F(TextGenTest, MultipleSuffixSelection) {
    gen1_->loadText("test4.txt");
    auto prefix = createPrefix({"a"});
    const std::string suffix = gen1_->getRandomSuffixForTest(prefix);
    EXPECT_TRUE(suffix == "b" || suffix == "c" || suffix == "d");
}

TEST_F(TextGenTest, TextGeneration) {
    TextGeneratorMarkov gen(2, 5);
    gen.loadText("test5.txt");
    auto& statetab = gen.getStateTable();
    
    auto prefix_i_wish = createPrefix({"I", "wish"});
    auto prefix_wish_i = createPrefix({"wish", "I"});
    auto prefix_i_may = createPrefix({"I", "may"});
    auto prefix_may_i = createPrefix({"may", "I"});
    
    EXPECT_NE(statetab.find(prefix_i_wish), statetab.end());
    EXPECT_NE(statetab.find(prefix_wish_i), statetab.end());
    EXPECT_NE(statetab.find(prefix_i_may), statetab.end());
    EXPECT_NE(statetab.find(prefix_may_i), statetab.end());
}

TEST_F(TextGenTest, EmptyInput) {
    createTestFile("empty.txt", "");
    gen2_->loadText("empty.txt");
    EXPECT_THROW(gen2_->generateText("test_output.txt"), std::runtime_error);
}

TEST_F(TextGenTest, ShortInput) {
    gen2_->loadText("test6.txt");
    EXPECT_FALSE(gen2_->getStateTable().empty());
    EXPECT_EQ(gen2_->getStateTable().size(), 1);
    
    auto prefix = createPrefix({"a", "b"});
    auto it = gen2_->getStateTable().find(prefix);
    EXPECT_NE(it, gen2_->getStateTable().end());
    EXPECT_EQ(it->second.size(), 1);
    EXPECT_EQ(it->second[0], "c");
}

TEST_F(TextGenTest, SuffixNotFound) {
    gen1_->loadText("test8.txt"); // Префикс размера 1
    
    // Для префикса "a" есть суффикс "b"
    auto prefix_a = createPrefix({"a"});
    EXPECT_NO_THROW(gen1_->getRandomSuffixForTest(prefix_a));
    
    // Для префикса "b" нет суффиксов - должно бросить исключение
    auto prefix_b = createPrefix({"b"});
    EXPECT_THROW(gen1_->getRandomSuffixForTest(prefix_b), std::runtime_error);
}

TEST_F(TextGenTest, DifferentPrefixSizes) {
    TextGeneratorMarkov gen1(1);
    TextGeneratorMarkov gen2(2);
    
    gen1.loadText("test1.txt");
    gen2.loadText("test1.txt");
    
    EXPECT_EQ(gen1.getStateTable().size(), 3);
    EXPECT_EQ(gen2.getStateTable().size(), 2);
}

TEST_F(TextGenTest, OutputLength) {
    TextGeneratorMarkov gen(1, 10);
    gen.loadText("test7.txt");
    
    const std::string outputFile = "test_output.txt";
    gen.generateText(outputFile);

    std::ifstream in(outputFile);
    std::string word;
    int wordCount = 0;
    
    while (in >> word) {
        wordCount++;
    }
    
    EXPECT_EQ(wordCount, 10) << "Generated text should contain exactly 10 words";
    fs::remove(outputFile);
}
