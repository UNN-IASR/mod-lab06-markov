#include "textgen.h"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    try {
        TextGenerator tg("data.txt", 2);
        
        std::string text = tg.genText(1000, 1500);
        
        std::ofstream out("../result/gen.txt");
        out << text;
        
        int word_count = std::count(text.begin(), text.end(), ' ') + 1;
        std::cout << "Words generation: " << word_count 
                  << " (Needed: 1000-1500)\n";
        
    } catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}