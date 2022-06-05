// Copyright 2022 UNN-IASR
#include <gtest/gtest.h>
#include "textgen.h"

TEST(task1, test1) {
    TextGenerator gentext = TextGenerator("test1.txt", 2, 1000);
    gentext.readFile();
    ASSERT_EQ(generator.words.size(), 6);
}
