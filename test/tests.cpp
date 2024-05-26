// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include "../include/textgen.h"

// Вспомогательная функция для вывода таблицы состояний
void print_statetab() {
    for (const auto &entry : statetab) {
        for (const auto &word : entry.first) {
            std::cout << word << " ";
        }
        std::cout << ": ";
        for (const auto &suffix : entry.second) {
            std::cout << suffix << " ";
        }
        std::cout << std::endl;
    }
}

// Тест 1: Формирование префикса из заданного числа слов
TEST(TextGenTest, PrefixGeneration) {
    // Очистка таблицы
    statetab.clear();

    // Запись тестового файла
    std::ofstream test_file("test_input.txt");
    test_file << "слово1 слово2 слово3 слово4 слово5";
    test_file.close();

    // Проверка для NPREF = 2
    build("test_input.txt", 2);
    ASSERT_EQ(statetab.size(), 3);
    ASSERT_EQ(statetab[prefix({"слово1", "слово2"})],
    std::vector<std::string>({"слово3"}));
    ASSERT_EQ(statetab[prefix({"слово2", "слово3"})],
    std::vector<std::string>({"слово4"}));
    ASSERT_EQ(statetab[prefix({"слово3", "слово4"})],
    std::vector<std::string>({"слово5"}));

    // Очистка таблицы
    statetab.clear();

    // Проверка для NPREF = 3
    build("test_input.txt", 3);
    ASSERT_EQ(statetab.size(), 2);
    ASSERT_EQ(statetab[prefix({"слово1", "слово2", "слово3"})],
    std::vector<std::string>({"слово4"}));
    ASSERT_EQ(statetab[prefix({"слово2", "слово3", "слово4"})],
    std::vector<std::string>({"слово5"}));
}

// Тест 2: Формирование записи "префикс-суффикс"
TEST(TextGenTest, PrefixSuffixRecord) {
    statetab.clear();
    prefix pref = {"слово1", "слово2"};
    statetab[pref].push_back("слово3");
    ASSERT_EQ(statetab[pref].size(), 1);
    ASSERT_EQ(statetab[pref][0], "слово3");
}

// Тест 3: Выбор единственного суффикса из вектора
TEST(TextGenTest, SingleSuffixSelection) {
    statetab.clear();
    prefix pref = {"слово1", "слово2"};
    statetab[pref].push_back("слово3");
    std::string next_word = statetab[pref][0];
    ASSERT_EQ(next_word, "слово3");
}

// Тест 4: Выбор суффикса из вектора, содержащего несколько вариантов
TEST(TextGenTest, MultipleSuffixSelection) {
    statetab.clear();
    prefix pref = {"слово1", "слово2"};
    statetab[pref] = {"слово3", "слово4", "слово5"};
    ASSERT_EQ(statetab[pref].size(), 3);
}

// Тест 5: Формирование текста заданной длины
TEST(TextGenTest, TextGeneration) {
    // Очистка и заполнение таблицы вручную
    statetab.clear();
    prefix pref1 = {"слово1", "слово2"};
    statetab[pref1].push_back("слово3");
    prefix pref2 = {"слово2", "слово3"};
    statetab[pref2].push_back("слово4");
    prefix pref3 = {"слово3", "слово4"};
    statetab[pref3].push_back("слово5");

    std::string text = generate_text(5);
    std::cout << "Generated text: " << text << std::endl;
    ASSERT_FALSE(text.empty());
}
