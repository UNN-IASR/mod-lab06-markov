// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include <time.h>
#include <stdexcept>
#include <iostream>
#include <string>
#include "textgen.h"

TEST(test1, prefixSize) {
    TextGenerator g = TextGenerator("test1.txt", "", 3, 1000);
    g.readFromFile();
    ASSERT_EQ(g.start.size(), 3);
}

