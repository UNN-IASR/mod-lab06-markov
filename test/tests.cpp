// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include "textgen.h"
#include <cstdlib>

class TextGeneratorTest : public ::testing::Test {
protected:

    const std::string test_file_path = "test_input.txt";

    void SetUp() override {
        std::ofstream file(test_file_path);
        file << "Жил старик со своею старухой\n";
        file << "У самого синего моря;\n";
        file << "Они жили в ветхой землянке\n";
        file << "Ровно тридцать лет и три года.\n";
        file.close();
    }

    void TearDown() override {
        std::remove(test_file_path.c_str());
    }
};

TEST(TestCaseName, TestName) {
    EXPECT_EQ(1, 2);
}

TEST_F(TextGeneratorTest, CreateStateTableTest) {
    TextGenerator tg;
    size_t prefix_length = 2;

    tg.__create_state_table__(test_file_path, prefix_length);

    const statetab& table = tg.__get_state_table__();

    ASSERT_FALSE(table.empty());

    prefix test_prefix = { "Жил", "старик" };
    auto it = table.find(test_prefix);
    ASSERT_NE(it, table.end());

    ASSERT_FALSE(it->second.empty());
}

TEST_F(TextGeneratorTest, CreateStateTableWithPrefixLengthTest) {
    TextGenerator tg;

    size_t prefix_length_1 = 1;
    tg.__create_state_table__(test_file_path, prefix_length_1);
    const statetab& table_1 = tg.__get_state_table__();

    ASSERT_FALSE(table_1.empty());

    size_t prefix_length_2 = 2;
    tg.__create_state_table__(test_file_path, prefix_length_2);
    const statetab& table_2 = tg.__get_state_table__();

    ASSERT_FALSE(table_2.empty());

    size_t prefix_length_3 = 3;
    tg.__create_state_table__(test_file_path, prefix_length_3);
    const statetab& table_3 = tg.__get_state_table__();

    ASSERT_FALSE(table_3.empty());
}

TEST_F(TextGeneratorTest, CheckPrefixAndSuffixContentTest) {
    TextGenerator tg;
    size_t prefix_length = 2;
    tg.__create_state_table__(test_file_path, prefix_length);
    const statetab& table = tg.__get_state_table__();

    prefix test_prefix = { "старик", "со" };
    auto it = table.find(test_prefix);

    ASSERT_NE(it, table.end());

    const std::vector<std::string>& suffixes = it->second;
    ASSERT_EQ(suffixes.size(), 1);
    ASSERT_EQ(suffixes[0], "своею");
}

TEST_F(TextGeneratorTest, HandleMissingPrefixInStateTableTest) {
    TextGenerator tg;
    size_t prefix_length = 2;
    tg.__create_state_table__(test_file_path, prefix_length);
    const statetab& table = tg.__get_state_table__();

    prefix missing_prefix = { "несуществующий", "префикс" };

    auto it = table.find(missing_prefix);
    ASSERT_EQ(it, table.end());
}

TEST_F(TextGeneratorTest, StateTablePrefixToSuffixMappingTest) {
    TextGenerator tg;
    size_t prefix_length = 2;
    tg.__create_state_table__(test_file_path, prefix_length);
    const statetab& table = tg.__get_state_table__();

    prefix p1 = { "Жил", "старик" };
    auto it1 = table.find(p1);
    ASSERT_NE(it1, table.end());
    ASSERT_EQ(it1->second.size(), 1);
    EXPECT_EQ(it1->second[0], "со");

    prefix p2 = { "старик", "со" };
    auto it2 = table.find(p2);
    ASSERT_NE(it2, table.end());
    ASSERT_EQ(it2->second.size(), 1);
    EXPECT_EQ(it2->second[0], "своею");

    prefix p3 = { "со", "своею" };
    auto it3 = table.find(p3);
    ASSERT_NE(it3, table.end());
    ASSERT_EQ(it3->second.size(), 1);
    EXPECT_EQ(it3->second[0], "старухой");
}

TEST(TextGeneratorSimpleTest, MultipleSuffixesForPrefixTest) {
    const std::string tmp_file = "multi_suffix_input.txt";
    std::ofstream file(tmp_file);
    file << "мы пошли домой\n";
    file << "мы пошли гулять\n";
    file.close();

    TextGenerator tg;
    tg.__create_state_table__(tmp_file, 2);
    const statetab& table = tg.__get_state_table__();

    prefix p = { "мы", "пошли" };
    auto it = table.find(p);
    ASSERT_NE(it, table.end());

    const auto& suffixes = it->second;
    ASSERT_EQ(suffixes.size(), 2);
    EXPECT_TRUE(std::find(suffixes.begin(), suffixes.end(), "домой") != suffixes.end());
    EXPECT_TRUE(std::find(suffixes.begin(), suffixes.end(), "гулять") != suffixes.end());

    std::remove(tmp_file.c_str());
}

TEST(TextGeneratorSimpleTest, SingleSuffixForPrefixTest) {
    const std::string tmp_file = "single_suffix_input.txt";
    std::ofstream file(tmp_file);
    file << "один два три\n";
    file.close();

    TextGenerator tg;
    size_t prefix_length = 2;

    tg.__create_state_table__(tmp_file, prefix_length);

    const statetab& table = tg.__get_state_table__();

    prefix p = { "один", "два" };
    auto it = table.find(p);
    ASSERT_NE(it, table.end());

    const auto& suffixes = it->second;
    ASSERT_EQ(suffixes.size(), 1);

    EXPECT_EQ(suffixes[0], "три");

    std::remove(tmp_file.c_str());
}

TEST(TextGenTest, MaxLengthTextGeneration) {
    std::ofstream out("test.txt");
    out << "a b c d e f";
    out.close();

    TextGenerator tg;

    tg.__create_state_table__("test.txt", 2);

    tg.__generate_text_and_write_to_file__(50, "output.txt");

    std::ifstream in("output.txt");
    std::string content;
    std::getline(in, content);

    std::istringstream iss(content);
    int words_count = 0;
    std::string word;
    while (iss >> word) {
        words_count++;
    }

    ASSERT_LT(words_count, 50);

    std::remove("test.txt");
    std::remove("output.txt");
}

TEST(TextGenTest, CorrectPrefixInGeneratedText) {
    std::ofstream out("test.txt");
    out << "a b c d e f g h i j k l m n o p q r s t u v w x y z";
    out.close();

    TextGenerator generator;

    generator.__create_state_table__("test.txt", 2);

    generator.__generate_text_and_write_to_file__(10, "generated_text.txt");

    std::ifstream in("generated_text.txt");
    std::string content;
    std::getline(in, content);

    ASSERT_TRUE(content.find("a b") == 0);

    std::remove("test.txt");
    std::remove("generated_text.txt");
}

TEST(TextGenTest, CorrectTextGenerationWithKnownData) {
    std::ofstream out("test.txt");
    out << "one two three four five six seven eight nine ten";
    out.close();

    TextGenerator generator;

    generator.__create_state_table__("test.txt", 2);

    generator.__generate_text_and_write_to_file__(6, "generated_text.txt");

    std::ifstream in("generated_text.txt");
    std::string content;
    std::getline(in, content);

    ASSERT_TRUE(content.find("one two") == 0);

    std::vector<std::string> expected_words = { "one", "two", "three", "four", "five", "six" };
    std::istringstream iss(content);
    std::string word;
    int word_index = 0;

    while (iss >> word && word_index < expected_words.size()) {
        ASSERT_EQ(word, expected_words[word_index]);
        word_index++;
    }

    ASSERT_EQ(word_index, expected_words.size());

    std::remove("test.txt");
    std::remove("generated_text.txt");
}