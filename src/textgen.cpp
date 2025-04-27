#include "textgen.h"

#include <algorithm>
#include <codecvt>
#include <deque>
#include <fstream>
#include <locale>
#include <map>
#include <random>
#include <regex>
#include <string>
#include <vector>

// да я знаю что есть stl split, но в симэйке стандарт 17 а там рэнжей нема.
std::vector<std::string> Split(const std::string& string,
                               const std::string& delimiter = " ") {
    std::vector<std::string> out;

    if (string.empty()) {
        return out;
    }

    size_t lastpos1 = 0;
    while (string.find(delimiter, lastpos1) != std::string::npos) {
        size_t lastpos2 = string.find(delimiter, lastpos1);
        out.push_back(string.substr(lastpos1, lastpos2 - lastpos1));
        lastpos1 = lastpos2 + delimiter.size();
    }
    out.push_back(string.substr(lastpos1, string.size() - lastpos1));

    return out;
}

TextGenerator::TextGenerator(size_t pref_len) : NPREF(pref_len) {
}

TextGenerator::TextGenerator(std::ifstream& input_file, size_t pref_len)
    : NPREF(pref_len) {
    // считаем и обработаем входную строку
    std::string prepared = PrepareText_(ReadAllFromFile(input_file));
    auto all_words = Split(prepared);

    prefix current_prefix;
    for (size_t i = 0; i < all_words.size() - NPREF + 1; ++i) {
        current_prefix.push_front(all_words[i]);
        if (current_prefix.size() == NPREF) {
            statetab_[current_prefix].push_back(all_words[i + 1]);
            current_prefix.pop_back();
        }
    }
}

std::string TextGenerator::Generate(size_t size, unsigned int seed) {
    srand(seed);
    size_t current_size = 0;
    std::string text = "";
    prefix start = GetRandomPrefix_(seed);
    while (current_size < size) {
        if (statetab_.find(start) != statetab_.end() &&
            !statetab_[start].empty()) {
            size_t suff_size = statetab_[start].size();
            text += start.back() + " ";
            ++current_size;
            if (current_size % 7 == 0) {
                text += "\n";
            }
            
            start.push_front(statetab_[start][rand_r(&seed) % suff_size]);
            start.pop_back();

        } else {
            start = GetRandomPrefix_(seed);
        }
    }
 
    return text;
}

std::string TextGenerator::ReadAllFromFile(std::ifstream& input) {
    std::string all_text = "";
    while (!input.eof()) {
        std::string word;
        input >> word;
        all_text += word + " ";
    }
    input.close();

    return all_text;
}

void TextGenerator::PrintTable(std::ostream& out) {
    for (const auto& pair : statetab_) {
        for (const auto& pref : pair.first) {
            out << pref << " ";
        }
        out << ": ";
        for (const auto& suff : pair.second) {
            out << suff << ", ";
        }
        out << "\n";
    }
}

std::map<prefix, std::vector<std::string>>& TextGenerator::statetab() {
    return statetab_;
}

prefix TextGenerator::GetRandomPrefix_(unsigned int seed) {
    prefix answer;
    int rnd_index = rand_r(&seed) % statetab_.size();
    for (const auto& pair : statetab_) {
        --rnd_index;
        if (rnd_index == 0) {
            answer = pair.first;
            break;
        }
    }

    return answer;
}

std::string TextGenerator::PrepareText_(const std::string& text) {
    std::regex punctuation_regex("[[:punct:]]");
    auto no_puncts = std::regex_replace(text, punctuation_regex, "");
    std::locale loc("ru_RU.UTF-8");
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    std::wstring wstr = converter.from_bytes(no_puncts);
    std::transform(wstr.begin(), wstr.end(), wstr.begin(),
                   [&](wchar_t c) { return std::tolower(c, loc); });

    return converter.to_bytes(wstr);
}
