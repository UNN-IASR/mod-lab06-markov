// Copyright 2024 Annenko Misha
//#include <ctime>

//#include "textgen.h"
#include "../include/textgen.h"

//Разбиение на слова
std::vector<std::string> textgen::Split(const std::string& str) {
    std::vector<std::string> words;
    size_t pos = 0;
    size_t next_space = 0;

    while ((next_space = str.find(' ', pos)) != std::string::npos) {
        words.push_back(str.substr(pos, next_space - pos));
        pos = next_space + 1;
    }

    words.push_back(str.substr(pos));
    return words;
}

//npref - количество слов в префиксе
//input_text - входной текст
void textgen::memorization(const std::string& input_text, int npref) {
    std::string copy_text = input_text;
    std::vector<std::string> words = Split(copy_text);
    // Заполнение начального префикса
    int k = 0;
    while (k < npref) {
        FirstPref.push_back(words[k]);
        k++;
    }
    // Запоолнение всех префиксов и суффиксов
    int i = 0;
    while (i < words.size() - npref) {
        prefix Prefix;
        int index = 0;
        while (index < 2) {
            Prefix.push_back(words[i + index]);
            ++index;
        }
        statetab[Prefix].push_back(words[i + npref]);
        i++;
    }
}

std::string textgen::generate__text(int maxgen, int npref) {
    return generate_text(maxgen, npref,
        std::default_random_engine::default_seed);
}

std::string textgen::generate_text(int maxgen, int npref, int seed) {
    /*srand(time(0));*/
    if (statetab.empty()) {
        return "EMPTY statetab";
    } else if (FirstPref.empty()) {
        return "EMPTY FirstPref";
    }
    std::default_random_engine _random_(seed);
    prefix Prefix = FirstPref;
    std::string output_text;

    int k = 0;
    while (k < npref) {
        output_text += FirstPref[k] + " ";
        k++;
    }
    while (output_text.size() < maxgen) {
        if (statetab.find(Prefix) != statetab.end()) {
            const std::vector<std::string>& suffixes_in_Prefix
                = statetab[Prefix];
            if (suffixes_in_Prefix.empty()) {
                break;
            } else if (!suffixes_in_Prefix.empty()) {
                std::uniform_int_distribution<>
                    dist(0, statetab[Prefix].size() - 1);
                int Index_Rand = dist(_random_);

                //int Index_Rand = rand() % (statetab[Prefix].size());

                output_text += suffixes_in_Prefix[Index_Rand] + " ";

                Prefix.pop_front();
                Prefix.push_back(suffixes_in_Prefix[Index_Rand]);
            }
        } else {
            break;
        }
    }

    if (output_text.size() > 0 && output_text.back() == ' ') {
        output_text.pop_back();
    }

    std::string copy_text = output_text;
    std::vector<std::string> words = Split(copy_text);

    if (words.size() > maxgen) {
        output_text.clear();
        for (const std::string& word : words) {
            output_text += word + " ";
        }
        output_text.pop_back();
        return output_text + "\n\n";
    }
    return output_text + "\n\n";
}

void textgen::Manual_Table(
    const std::map<prefix,
    std::vector<std::string>>& state) {

    statetab = state;

    if (!statetab.empty()) {
        FirstPref = state.begin() -> first;
    }
}
