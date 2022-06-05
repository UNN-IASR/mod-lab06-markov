#include "textgen.h"

int main() {
    Generator gen = Generator("...\\Text.txt");
    std::cout << gen.newText() << std::endl;
}
