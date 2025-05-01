// Copyright 2025 UNN
#include "textgen.h"
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<deque>
#include<queue>

TextGen::TextGen(std::string& filename) {
    std::string str;
    std::ifstream in ("../dataset/" + filename);
    prefix que;
    if (in.is_open()) {
        while (!in.eof()) {
            in >> str;
            if (que.size() == NPREF) {
                statetab[que].push_back(str);
                que.pop_front();
            }
            que.push_back(str);
        }
    } else {
        throw std::runtime_error("incorrect name of file");
    }
    in.close();
}

void TextGen::Generate (std::string& filename, const int seed, const int MaxX) {
    srand(seed);
    prefix que;
    std::string nexT;

    que = (*statetab.begin()).first;

    std::ofstream out ("../result/" + filename);
    if (out.is_open()) {
        int cntWords = que.size();
        for (auto e : que) {
            out << e << " ";
        }
        while (cntWords < MAXGEN && (cntWords < MaxX || MaxX == -1)) {
            if(statetab.find(que) == statetab.end()) {
                que = (*statetab.begin()).first;
            }
            nexT = statetab[que][rand() % statetab[que].size()];
            cntWords++;
            out << nexT << " ";
            que.pop_front();
            que.push_back(nexT);
        }
    }
    out.close(); 
}
