#include <gtest/gtest.h>
#include <deque>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

typedef std::deque<std::string> prefix;
typedef std::map<prefix, std::vector<std::string>> statetab;

prefix make_prefix(const std::vector<std::string>& words);
void build_table(std::ifstream& input, statetab& table, int npref);
std::string choose_suffix(const std::vector<std::string>& suffixes, std::mt19937& gen);
void generate_text(statetab& table, int npref, int maxgen);

prefix make_prefix(const std::vector<std::string>& words) {
    prefix p;
    for (const auto& word : words) {
        p.push_back(word);
    }
    return p;
}

std::string choose_suffix(const std::vector<std::string>& suffixes, std::mt19937& gen) {
    if (suffixes.empty()) return "";
    std::uniform_int_distribution<> dis(0, suffixes.size() - 1);
    return suffixes[dis(gen)];
}

class TextGenTest : public ::testing::Test {
protected:
    std::mt19937 gen;
    statetab table;

    TextGenTest() : gen(42) {}
};

TEST_F(TextGenTest, CreatePrefixSize2) {
    std::vector<std::string> words = { "hello", "world" };
    prefix p = make_prefix(words);
    EXPECT_EQ(p.size(), 2);
    EXPECT_EQ(p[0], "hello");
    EXPECT_EQ(p[1], "world");
}

TEST_F(TextGenTest, CreatePrefixSize3) {
    std::vector<std::string> words = { "a", "b", "c" };
    prefix p = make_prefix(words);
    EXPECT_EQ(p.size(), 3);
    EXPECT_EQ(p[0], "a");
    EXPECT_EQ(p[1], "b");
    EXPECT_EQ(p[2], "c");
}

TEST_F(TextGenTest, BuildTableSinglePair) {
    std::istringstream input("a b c");
    build_table(input, table, 2);
    prefix p = make_prefix({ "a", "b" });
    EXPECT_NE(table.find(p), table.end());
    EXPECT_EQ(table[p].size(), 1);
    EXPECT_EQ(table[p][0], "c");
}

TEST_F(TextGenTest, BuildTableMultipleSuffixes) {
    std::istringstream input("a b c a b d");
    build_table(input, table, 2);
    prefix p = make_prefix({ "a", "b" });
    EXPECT_NE(table.find(p), table.end());
    EXPECT_EQ(table[p].size(), 2);
    EXPECT_TRUE(table[p][0] == "c" || table[p][1] == "c");
    EXPECT_TRUE(table[p][0] == "d" || table[p][1] == "d");
}

TEST_F(TextGenTest, ChooseSuffixSingle) {
    std::vector<std::string> suffixes = { "end" };
    std::string result = choose_suffix(suffixes, gen);
    EXPECT_EQ(result, "end");
}

TEST_F(TextGenTest, ChooseSuffixMultipleDeterministic) {
    std::vector<std::string> suffixes = { "x", "y", "z" };
    std::string result1 = choose_suffix(suffixes, gen);
    std::string result2 = choose_suffix(suffixes, gen);
    std::string result3 = choose_suffix(suffixes, gen);
    EXPECT_EQ(result1, "y");
    EXPECT_EQ(result2, "x");
    EXPECT_EQ(result3, "z");
}

TEST_F(TextGenTest, GenerateTextFixedLength) {
    prefix p1 = make_prefix({ "start", "word" });
    table[p1] = { "next" };
    prefix p2 = make_prefix({ "word", "next" });
    table[p2] = { "end" };

    std::ostringstream output_stream;
    std::streambuf* oldbuf = std::cout.rdbuf();
    std::cout.rdbuf(output_stream.rdbuf());

    generate_text(table, 2, 5);

    std::cout.rdbuf(oldbuf);
    std::string output = output_stream.str();
    EXPECT_TRUE(output.find("start word next end") != std::string::npos);
}

TEST_F(TextGenTest, GenerateTextStopsOnMissingPrefix) {
    prefix p = make_prefix({ "a", "b" });
    table[p] = { "c" };
    prefix p2 = make_prefix({ "b", "c" });
    // p2 not in table

    std::ostringstream output_stream;
    std::streambuf* oldbuf = std::cout.rdbuf();
    std::cout.rdbuf(output_stream.rdbuf());

    generate_text(table, 2, 10);

    std::cout.rdbuf(oldbuf);
    std::string output = output_stream.str();
    EXPECT_EQ(output, "a b c ");
}

TEST_F(TextGenTest, GenerateTextEmptyTable) {
    std::ostringstream output_stream;
    std::streambuf* oldbuf = std::cout.rdbuf();
    std::cout.rdbuf(output_stream.rdbuf());

    generate_text(table, 2, 10);

    std::cout.rdbuf(oldbuf);
    std::string output = output_stream.str();
    EXPECT_EQ(output, "");
}

TEST_F(TextGenTest, PrefixSizeMatchesNpref) {
    std::istringstream input("a b c d");
    build_table(input, table, 2);
    for (const auto& pair : table) {
        EXPECT_EQ(pair.first.size(), 2);
    }
}
