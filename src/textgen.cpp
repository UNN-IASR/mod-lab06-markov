// Copyright 2022 UNN-IASR
#include "textgen.h"

#define random rand

TextGenerator::TextGenerator(std::string Nfile, int Npref, int Maxgen) {
    setlocale(LC_ALL, "Russian");
    NPREF = Npref;
    MAXGEN = Maxgen;
    NFILE = Nfile;
}

void TextGenerator::readFile() {
    std::ifstream in(NFILE);
    std::string line;
    std::string textfile = "";
    if (in.is_open()) {
        while (getline(in, line)) {
            textfile = textfile + line + " ";
        }
    }
    in.close();
    text = textfile;

    int i = 0;
    int j = 0;
    int n = 0;

    while (textfile[i] != '\0') {
        if (j == 0 && textfile[i] != ' ') {
            j = 1;
            words.push_back("");
            words[n] = words[n] + textfile[i];
            n++;
        } else if (j == 1 && (textfile[i] == ' ')) {
            j = 0;
        } else if (j == 1 && textfile[i] != ' ') {
            words[n - 1] = words[n - 1] + textfile[i];
        }
        i++;
    }

    for (int i = 0; i < words.size() - NPREF + 1; i++) {
        prefix pref;
        for (int j = 0; j < NPREF; j++) {
            pref.push_back(words[i + j]);
        }
        if (i + NPREF < words.size()) {
            stateTab[pref].push_back(words[i + NPREF]);
        } else {
            stateTab[pref].push_back("end_file");
        }
    }
}

std::string TextGenerator::generate() {
    setlocale(LC_ALL, "Russian");
    readFile();

    prefix pref;
    std::string text = "";
    int n = 1;
    for (int i = 0; i < NPREF; i++) {
        pref.push_back(words[i]);
    }
    for (int i = 0; i < NPREF; i++) {
        text = text + pref[i] + ' ';
    }

    while (text.size() < MAXGEN) {
        int veroyatnost;

        if (stateTab[pref].size() == 1 && stateTab[pref][0] == "end_file") {
            break;
        }

        if (stateTab[pref].size() == 0) {
            break;
        }

        veroyatnost = random() % stateTab[pref].size();

        if (stateTab[pref][stateTab[pref].size() - 1] == "end_file") {
            veroyatnost = random() % (stateTab[pref].size() - 1);
        }

        text = text + stateTab[pref][veroyatnost] + ' ';

        std::string a = stateTab[pref][veroyatnost];
        for (int i = 0; i < NPREF - 1; i++) {
            pref[i] = pref[i + 1];
        }
        pref[NPREF - 1] = a;

        if (n == 15) {
            text = text + '\n';
            n = 1;
        }
        n++;
    }
    return text;
}
