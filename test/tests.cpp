// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include "textgen.h"
#include <gtest/gtest.h>
#include <sstream>
#include <fstream>

class TextGenTest : public ::testing::Test {
 protected:
    void SetUp() override {
        gen2 = new TextGenerator(2);
        gen1 = new TextGenerator(1);

        createFileForTest("test1.txt", "word1 word2 word3 word4");
        createFileForTest("test2.txt", "a b c d b c e");
        createFileForTest("test3.txt", "a b a b a b");
        createFileForTest("test4.txt", "a b a c a d");
        createFileForTest("test5.txt", "one two three four five six seven eight nine ten");
        createFileForTest("test6.txt", "");
        createFileForTest("test7.txt", "a b");
        createFileForTest("test8.txt", "a b a c a d");
        createFileForTest("test9.txt", "a b c a b d a b e");
    }

    void TearDown() override {
        delete gen2;
        delete gen1;
    }

    void createFileForTest(const std::string &filename, const std::string &content) {
        std::ofstream out(filename);
        out << content;
        out.close();
      }

    TextGenerator* gen2;
    TextGenerator* gen1;
};

// Тест 1: Формирование префикса из заданного числа слов
TEST_F(TextGenTest, PrefixFormation) {
    gen2->learnFromText("test1.txt");
    EXPECT_EQ(gen2->GetAllPrefixes().size(), 3);
}

// Тест 2: Формирование записи "префикс-суффикс"
TEST_F(TextGenTest, PrefixSuffixRecord) {
    gen2->learnFromText("test2.txt");
    Prefix testPrefix = {"b", "c"};
    EXPECT_EQ(gen2->GetTable()[testPrefix].size(), 2);
}

// Тест 3: Выбор единственного суффикса
TEST_F(TextGenTest, SingleSuffixSelection) {
    gen1->learnFromText("test3.txt");
    Prefix testPrefix = {"a"};
    EXPECT_EQ(gen1->GetTable()[testPrefix][0], "b");
}

// Тест 4: Выбор из нескольких суффиксов
TEST_F(TextGenTest, MultipleSuffixSelection) {
    gen1->learnFromText("test4.txt");
    Prefix testPrefix = {"a"};
    EXPECT_EQ(gen1->GetTable()[testPrefix].size(), 3);
}

// Тест 5: Формирование текста заданной длины
TEST_F(TextGenTest, TextGenerationLength) {
    gen2->learnFromText("test5.txt");
    gen2->generateText(5, "test_output.txt");
    
    std::ifstream in("test_output.txt");
    std::string word;
    int count = 0;
    while (in >> word) count++;
    
    EXPECT_GE(count, 5);
}

// Тест 6: Обработка пустого ввода
TEST_F(TextGenTest, EmptyInput) {
    std::stringstream ss("");
    gen2->learnFromText("test6.txt");
    EXPECT_THROW(gen2->generateText(1000, "output_test.txt"), std::runtime_error);
}

// Тест 7: Обработка слишком короткого ввода
TEST_F(TextGenTest, ShortInput) {
    TextGenerator gen3(3);
    gen3.learnFromText("test7.txt");
    EXPECT_TRUE(gen3.GetAllPrefixes().empty());
}

// Тест 8: Проверка случайного выбора суффикса
TEST_F(TextGenTest, RandomSuffixSelection) {
    gen1->learnFromText("test8.txt");
    Prefix testPrefix = {"a"};
    
    int bCount = 0, cCount = 0, dCount = 0;
    for (int i = 0; i < 1000; i++) {
        std::string suffix = gen1->GetTable()[testPrefix][std::rand() % gen1->GetTable()[testPrefix].size()];
        if (suffix == "b") bCount++;
        else if (suffix == "c") cCount++;
        else if (suffix == "d") dCount++;
    }
    
    EXPECT_GT(bCount, 0);
    EXPECT_GT(cCount, 0);
    EXPECT_GT(dCount, 0);
}

// Тест 9: Проверка количество слов в выходном файле
TEST_F(TextGenTest, OutputWordCount) {
    TextGenerator gen(1);
    gen.learnFromText("test2.txt");
  
    const std::string outputFile = "test_output.txt";
    gen.generateText(10, outputFile);
  
    std::ifstream in(outputFile);
    std::string word;
    int wordCount = 0;
  
    while (in >> word) {
      wordCount++;
    }
  
    EXPECT_EQ(wordCount, 10) << "Generated text should contain exactly 10 words";
  }

// Тест 10: Проверка переноса строки каждые 15 слов
TEST_F(TextGenTest, LineBreaksAfter15Words) {
    std::stringstream ss;
    for (int i = 0; i < 50; i++) {
        ss << "word" << i << " ";
    }
    
    gen2->learnFromText(INPUT_FILE_PATH);
    gen2->generateText(30, "line_breaks_test.txt");
    
    std::ifstream in("line_breaks_test.txt");
    std::string line;
    int lineCount = 0;
    
    while (std::getline(in, line)) {
        std::istringstream lineStream(line);
        std::string word;
        int wordsInLine = 0;
        
        while (lineStream >> word) {
            wordsInLine++;
        }
        
        if (lineCount == 0) {
            EXPECT_GE(wordsInLine, 2);
        } else {
            EXPECT_LE(wordsInLine, 15);
        }
        lineCount++;
    }
    
    EXPECT_GE(lineCount, 2);
}
