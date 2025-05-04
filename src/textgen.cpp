#include "textgen.h"
#include <random>
#include <ctime>
#include <fstream>

void TextGenerator::add(prefix& p, const std::string& s) {
    if (p.size() == NPREF) {
        statetab[p].push_back(s);
        p.pop_front();
    }
    p.push_back(s);
}

void TextGenerator::build(std::istream& in) {
    prefix p;
    std::string buf;
    bool initialStored = false;
    bool hasData = false;

    while (in >> buf) {
        hasData = true;
        buf.erase(std::remove_if(buf.begin(), buf.end(),
            [](char c) { return c == '\r' || c == '\n'; }), buf.end());
        if (!buf.empty()) {
            add(p, buf);
            if (!initialStored && p.size() == NPREF) {
                initialPrefix = p;
                initialStored = true;
            }
        }
    }
    if (!hasData) {
        throw std::runtime_error("Empty input");
    }
}

void TextGenerator::generate(int nwords, const std::string& outputFile) {
    std::ofstream out(outputFile);
    if (!out.is_open()) {
        std::cerr << "Error: cannot open output file " << outputFile << std::endl;
        return;
    }

    prefix p;
    std::mt19937 gen(static_cast<unsigned int>(time(nullptr)));

    if (statetab.empty()) {
        std::cerr << "Error: no data available for text generation" << std::endl;
        return;
    }

    p = initialPrefix;
    if (statetab.find(initialPrefix) != statetab.end()) {
        p = initialPrefix;
    }
    else {
        p = statetab.begin()->first;
    }

    for (const auto& word : p) {
        out << word << " ";
    }

    for (int i = 0; i < nwords; ++i) {
        auto it = statetab.find(p);
        if (it == statetab.end() || it->second.empty()) {
            break;
        }

        const std::vector<std::string>& suffixes = it->second;
        std::uniform_int_distribution<size_t> dis(0, suffixes.size() - 1);
        const std::string& w = suffixes[dis(gen)];

        out << w << " ";

        p.pop_front();
        p.push_back(w);
    }

    out << std::endl;
    std::cout << "Text successfully generated and saved to " << outputFile << std::endl;
}