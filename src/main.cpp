// Copyright 2022 UNN-IASR
#include <iostream>
#include "textgen.h"

int main() {
    TextGenerator Gen = TextGenerator("FileIn.txt", "Solution.txt", 2, 1);
    Gen.generate();
}
