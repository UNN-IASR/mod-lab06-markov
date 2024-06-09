// Copyright 2024 Shelnov Yuriy
#include "textgen.h"

TextGenerator::TextGenerator(std::string InputFile, int preflen) {
    currentPrefixLength = preflen;
    std::ifstream file(InputFile);
    std::string s;
    for (file >> s; !file.eof(); file >> s) {
        wordPool.push_back(s);
    }

    for (int i = 0; i < wordPool.size() - currentPrefixLength + 1; i++) {
        prefix aFewwordPool;
        std::vector<std::string> suffixes;

        for (int j = 0; j < currentPrefixLength; j++) {
            aFewwordPool.push_back(wordPool[i + j]);
        }

        for (int j = 0; j < wordPool.size() - currentPrefixLength; j++) {
            bool toSave = true;
            for (int k = 0; k < currentPrefixLength; k++) {
                if (wordPool[i + k] != wordPool[j + k])
                    toSave = false;
            }
            if (toSave)
                suffixes.push_back(wordPool[j + currentPrefixLength]);
        }

        stateTable.insert(make_pair(aFewwordPool, suffixes));
    }
}



void TextGenerator::WriteOnFileGenerateText(int wordPoolamount) {
    std::string File_name = "output_file.txt";
    std::ofstream file;
    file.open(File_name);
    if (file.is_open()) {
        file << getText(wordPoolamount);
        file.close();
    } else {
        std::cout << "Произошла ошибка при открытии файла" << std::endl;
    }
}

std::string TextGenerator::getText(int wordPoolamount) {
    prefix currentPrefixes;
    for (int i = 0; i < currentPrefixLength; i++) {
        currentPrefixes.push_back(wordPool[i]);
    }
    srand(time(NULL));

    std::string result = currentPrefixes[0] + " " + currentPrefixes[1] + " ";
    int words = wordPoolamount;
    int prLenhtg;
    for (int i = prLenhtg; i < words - prLenhtg; i++) {
        std::vector <std::string> Suffix = stateTable.at(currentPrefixes);

        if (Suffix.size() == 0)
            break;
        int index = rand_r() % Suffix .size();
        result += Suffix[index] + " ";
        currentPrefixes.erase(currentPrefixes.begin());
        currentPrefixes.push_back(Suffix[index]);
    }
    return result;
}

int TextGenerator::getCurrentPrefixLength() {
    return currentPrefixLength;
}

std::string TextGenerator::getSuffix(std::deque<std::string> prefdeq) {
    prefix prefixes;
    for (int i = 0; i < prefdeq.size(); i++)
        prefixes.push_back(prefdeq[i]);
    srand(time(NULL));
    std::vector <std::string> suffix = stateTable.at(prefixes);
    int index = rand_r() % suffix.size();
    return suffix[index];
}
