// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include "textgen.h"

TEST(task1, test1) {
    TextGenerator gentext = TextGenerator("test1.txt", 2, 1000);
    gentext.generate();
    ASSERT_EQ(gentext.words.size(), 6);
}
