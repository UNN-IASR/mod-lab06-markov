// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include "textgen.h"

TEST(task1, test1) {
    TextGenerator gtext = TextGenerator("test1.txt", 2, 1000);
    gtext.readFile();
    ASSERT_EQ(gtext.words.size(), 6);
}
