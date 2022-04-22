// Copyright 2022 UNN-IASR
#include <iostream>
#include "textgen.h"

int main() {
    TextGenerator generator = TextGenerator("in.txt", "out.txt", 2, 1);
    generator.generate();
}
