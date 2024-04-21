//  Copyright 2024 Teodor

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <deque>
#include  "textgen.h"

int main() {
    const int NPREF = 2;
    const int MAXGEN = 1000;
    std::vector<std::string> out = Generating_text("text.txt", NPREF, MAXGEN);
    for (int i = 0; i < out.size(); i++) {
        std::cout << out[i] << " ";
    }
    return 0;
}
