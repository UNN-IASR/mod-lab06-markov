// Copyright 2022 UNN-IASR
#pragma once
#include <vector>
#include <string>

template<typename stream_t>
    std::vector<std::string> read_stream(stream_t(&stream)) {
    std::vector<std::string> result;
    std::string word = "";
    unsigned char ch = stream.get();
    while (!stream.eof()) {
        if (ch > 191 && ch < 224) {
            ch += 32;
        }
        if (ch > 64 && ch < 91) {
            ch += 32;
        }
        if ((ch > 223 && ch <= 255) || (ch > 96 && ch <= 123)) {
            word += ch;
        } else if (word.size() > 0) { result.push_back(word); word = "";}
        ch = stream.get();
    }
    if (word.length()) {
        result.push_back(word);
    }
    return result;
}
