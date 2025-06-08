// src/textgen.cpp
#include "textgen.h"
#include <cstdlib>
#include <iterator>

void build_prefix_map(std::istream& in,
                      statetab_t& statetab,
                      int npref) {
    std::deque<std::string> pref;
    std::string word;
    for (int i = 0; i < npref; ++i) {
        if (!(in >> word)) return;
        pref.push_back(word);
    }
    while (in >> word) {
        statetab[pref].push_back(word);
        pref.pop_front();
        pref.push_back(word);
    }
}

std::vector<std::string> generate_text(
    const statetab_t& statetab,
    int npref,
    int maxgen) {
    std::vector<std::string> output;
    if (statetab.empty() || maxgen < 0) return output;

    // Стартовый префикс — первый ключ в таблице
    auto it_start = statetab.begin();
    prefix pref = it_start->first;
    // Сразу добавляем его слова в вывод
    for (const auto& w : pref) {
        output.push_back(w);
    }
    // Генерация ровно maxgen следующих слов
    for (int i = 0; i < maxgen; ++i) {
        auto it = statetab.find(pref);
        // Если нет суффиксов — берём случайный префикс с непустым списком
        if (it == statetab.end() || it->second.empty()) {
            do {
                auto it2 = statetab.begin();
                std::advance(it2, std::rand() % statetab.size());
                it = it2;
            } while (it->second.empty());
            pref = it->first;
        }
        const auto& suffixes = it->second;
        int idx = std::rand() % static_cast<int>(suffixes.size());
        const std::string& next = suffixes[idx];
        output.push_back(next);
        pref.pop_front();
        pref.push_back(next);
    }
    return output;
}
