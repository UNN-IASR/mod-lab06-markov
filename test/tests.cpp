#include <gtest/gtest.h>
#include "textgen.h"

class MarkovTest : public ::testing::Test {
protected:
    void SetUp() override {
        generator = Markov;
    }
    Markov generator;
};

TEST(MarkovTest, PrefixSizeOne) {
    Markov generator(1, 100);
    generator.learnFromString("Проворный кот в сапогах");
    auto table = generator.getStateTable();
    EXPECT_EQ(table.begin()->first.size(), 1);
}

TEST(MarkovTest, PrefixSizeTwo) {
    generator.learnFromString("Проворный кот в сапогах");
    auto table = generator.getStateTable();
    EXPECT_EQ(table.begin()->first.size(), 2);
}

TEST(MarkovTest, FirstSufix) {
    generator.learnFromString("Проворный кот в сапогах");
    auto it = generator.getStateTable().begin();
    std::string sufix = it->second[0];
    EXPECT_EQ(sufix, "кот");
}

TEST(MarkovTest, SingleSufix) {
    generator.learnFromString("Проворный кот");
    auto table = generator.getStateTable();
    std::string actual = table.begin()->second[0];
    EXPECT_EQ(actual, "кот");
}

TEST(MarkovTest, FirstOfMultipleSufixes) {
    generator.learnFromString("Проворный кот хитрый кот");
    auto sufixes = generator.getStateTable().begin()->second;
    std::string chosen = sufixes[0];
    EXPECT_EQ(chosen, "кот");
}

TEST(MarkovTest, GenerateTextOfFixedLength) {
    Markov specGenerator(2, 7);
    specGenerator.learnFromString("Это был самый хитрый и проворный кот в сапогах");
    specGenerator.generateText();
    std::string output = specGenerator.getGeneratedText();
    int wordCount = std::count(output.begin(), output.end(), ' ');
    EXPECT_EQ(wordCount, 7);
}

TEST(MarkovTest, EmptyInputResultsInEmptyMap) {
    generator.learnFromString("");
    int actual = generator.getStateTable().size();
    EXPECT_EQ(actual, 0);
}

TEST(MarkovTest, GeneratedStringNotEmpty) {
    generator.learnFromString("Проворный кот в сапогах");
    generator.generateText();
    int actual = generator.getGeneratedText().empty() ? 0 : 1;
    EXPECT_EQ(actual, 1);
}

TEST(MarkovTest, LastSufix) {
    generator.learnFromString("Проворный кот в сапогах");
    generator.generateText();
    bool hasMarker = generator.getGeneratedText().find("\n") != std::string::npos;
    EXPECT_EQ(hasMarker, true);
}

TEST(MarkovTest, LearningTwiceChangesTable) {
    generator.learnFromString("Проворный кот в сапогах");
    int size1 = generator.getStateTable().size();
    generator.learnFromString("Неуловимый гусь");
    int size2 = generator.getStateTable().size();
    bool changed = (size1 != size2);
    EXPECT_EQ(changed, true);
}
