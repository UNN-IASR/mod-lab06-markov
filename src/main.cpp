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


int main() {
    std::string line;
    std::string text = "text.txt";
    genText gn = genText(text, 2, 1000);
    std::string answer = gn.getText();
    std::cout << answer;
}
