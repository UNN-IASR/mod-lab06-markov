//  Copyright 2024 Teodor

#include "textgen.h"

bool is_separator(char c) {
    return c == ' ' || c == '\n';
}

std::vector<std::string> Split(std::string in_string) {
    std::vector<std::string> out_words_vector;
    std::string word = "";
    int i = 0;
    while (i < in_string.length()) {
        if (is_separator(in_string[i])) {
            out_words_vector.push_back(word);
            word = "";
        } else {
            word+=in_string[i];
        }
        i++;
    }
    if (word.length() != 0) {
        out_words_vector.push_back(word);
        word = "";
    }
    return out_words_vector;
}

std::vector<std::string> Split_file_lines(std::string name_of_file) {
    std::ifstream file(name_of_file);
    std::string s;
    std::vector<std::string> words;
    while (std::getline(file, s)) {
        std::vector<std::string> split_line = Split(s);
        words.insert(words.end(), split_line.begin(), split_line.end());
    }
    file.close();
    return words;
}

prefix get_pref(std::vector<std::string> words, int NPREF) {
    prefix pre;
    for (int i = 0; i < NPREF; i++) {
         pre.push_back(words[i]);
    }
    return pre;
}

void add_new_row(std::map<prefix, postfix> &statetab,
                prefix& pre,
                const std::vector<std::string>& words,
                int i) {
    pre.pop_front();
    pre.push_back(words[i]);
    if (statetab.find(pre) != statetab.end()) {
        statetab[pre].push_back(words[i+1]);
    } else {
        postfix post = {words[i+1]};
        statetab[pre] = post;
    }
}

bool add_new_string(std::map<prefix, postfix> &statetab,
prefix& pre, std::vector<std::string>& out_string) {
    std::random_device rd;
    std::mt19937 gen(rd());
    if (statetab.find(pre) != statetab.end()) {
            std::uniform_int_distribution<> dist(0, statetab[pre].size()-1);
            int t = dist(gen);
            out_string.push_back(statetab[pre][t]);
            pre.push_back(statetab[pre][t]);
            pre.pop_front();
            return true;
    }
    return false;
}

std::map<prefix, postfix> create_statetab(const std::vector<std::string> &words,
                                            int NPREF) {
    prefix pre;
    postfix post;
    std::map<prefix, postfix> statetab;
    pre = get_pref(words, NPREF);
    post.push_back(words[NPREF]);
    statetab[pre] = post;

    for (int i = NPREF; i < words.size() - 1; i++) {
        add_new_row(statetab, pre, words, i);
    }
    return statetab;
}

std::vector<std::string> get_text(std::map<prefix, postfix> &statetab,
        const std::vector<std::string> &words, int NPREF, int MAXGEN) {
    prefix pre;
    std::vector<std::string> out_string;
    for (int i = 0; i < NPREF; i++) {
        pre.push_back(words[i]);
        out_string.push_back(words[i]);
    }

    for (int i = 0; i < MAXGEN; i++) {
        if (add_new_string(statetab, pre, out_string) == false) {
            break;
        }
    }
    return out_string;
}

std::vector<std::string> Generating_text(std::string name_of_file,
                                            int NPREF,
                                            int MAXGEN) {
    std::vector<std::string> words = Split_file_lines(name_of_file);
    std::map<prefix, postfix> statetab = create_statetab(words, NPREF);
    std::vector<std::string> out_string =
        get_text(statetab, words, NPREF, MAXGEN);
    return out_string;
}
