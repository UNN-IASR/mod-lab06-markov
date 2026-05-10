#include "../include/textgen.h"

TextGenerator::TextGenerator() {}

void TextGenerator::train(const std::vector<std::string>& text) {
    if (text.size() <= NPREF) {
        return; // Текст слишком короткий для анализа
    }

    prefix current_prefix;

    // Заполняем начальный префикс первыми NPREF словами
    for (int i = 0; i < NPREF; ++i) {
        current_prefix.push_back(text[i]);
    }
    starting_prefix = current_prefix;

    // Проходим по остальному тексту и строим таблицу
    for (size_t i = NPREF; i < text.size(); ++i) {
        statetab[current_prefix].push_back(text[i]);
        current_prefix.pop_front();
        current_prefix.push_back(text[i]);
    }
}

std::string TextGenerator::generate(int max_words) {
    if (statetab.empty()) {
        return "";
    }

    std::string result = "";
    prefix current_prefix = starting_prefix;

    // Добавляем начальный префикс в результат
    for (size_t i = 0; i < current_prefix.size(); ++i) {
        result += current_prefix[i] + (i == current_prefix.size() - 1 ? "" : " ");
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    int words_generated = NPREF;

    while (words_generated < max_words) {
        // Если для текущего префикса нет продолжения - завершаем
        if (statetab.find(current_prefix) == statetab.end() || statetab[current_prefix].empty()) {
            break;
        }

        // Выбираем случайный суффикс
        const std::vector<std::string>& suffixes = statetab[current_prefix];
        std::uniform_int_distribution<> dist(0, suffixes.size() - 1);
        std::string chosen_suffix = suffixes[dist(gen)];

        result += " " + chosen_suffix;
        words_generated++;

        // Сдвигаем префикс
        current_prefix.pop_front();
        current_prefix.push_back(chosen_suffix);
    }

    return result;
}

std::map<prefix, std::vector<std::string>> TextGenerator::getStatetab() const {
    return statetab;
}

prefix TextGenerator::getStartingPrefix() const {
    return starting_prefix;
}