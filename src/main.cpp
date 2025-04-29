#include "textgen.h"

int main()
{
    TextGeneratorClass tg("C:/VScode/mod-lab06-markov/src/data.txt");
    std::string text = tg.generateText();
    std::ofstream file("C:/VScode/mod-lab06-markov/result/gen.txt");
    file << text;
    std::cout << text;
    file.close();
    return 0;
}