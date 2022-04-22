  // Copyright 2022 Irina
#include <stdio.h>
#include <string.h>
#include <string>
#include <deque>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include "textgen.h"
#define rand_r rand

genText::genText(std::string filename, int i1, int i2) {
    setlocale(LC_ALL, "Russian");
    srand(4561);
    NPREF = i1;
    MAXGEN = i2;
    int i = 0;
    int F = 0;
    int count = -1;

    std::ifstream in(filename);
    std::string line;
    std::string textfile = "";
    if (in.is_open()) {
        while (getline(in, line)) {
            textfile = textfile + line + " ";
        }
    }
    in.close();
    data = textfile;

    while (textfile[i] != '\0') {
        if (F == 0 && textfile[i] != ' ') {
            F = 1;
            count++;
            words.push_back("");
            words[count] = words[count] + textfile[i];
        } else if (F == 1 && (textfile[i] == ' ')) {
            F = 0;
        } else if (F == 1 && textfile[i] != ' ') {
            words[count] = words[count] + textfile[i];
        }
        i++;
    }

    for (int i = 0; i < words.size() - NPREF + 1; i++) {
        prefix prf;
        for (int j = 0; j < NPREF; j++)
            prf.push_back(words[i + j]);
        if (i + NPREF < words.size())
            statetab[prf].push_back(words[i + NPREF]);
        else
            statetab[prf].push_back("end_file");
    }
}


std::string genText::getText() {
    setlocale(LC_ALL, "Russian");
    srand(4561);
    prefix pre;
    for (int i = 0; i < NPREF; i++) pre.push_back(words[i]);

    std::string text = "";
    int kol = 1;

    for (int i = 0; i < NPREF; i++)
        text = text + pre[i] + ' ';

    while (text.size() < MAXGEN) {
        int veroyatnost;

        if (statetab[pre].size() == 1 && statetab[pre][0] == "end_file")
            break;

        if (statetab[pre].size() == 0)
            break;

        veroyatnost = rand_r() % statetab[pre].size();

        if (statetab[pre][statetab[pre].size() - 1] == "end_file")
          veroyatnost = rand_r() % (statetab[pre].size() - 1);

        text = text + statetab[pre][veroyatnost] + ' ';

        std::string a = statetab[pre][veroyatnost];
        for (int i = 0; i < NPREF - 1; i++)
            pre[i] = pre[i + 1];
        pre[NPREF - 1] = a;

        if (kol == 15) {
            text = text + '\n';
            kol = 1;
        }
        kol++;
    }
    return text;
}
