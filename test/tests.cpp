// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include <ctime>
#include <iostream>
#include "textgen.h"
TEST(TEST1, TrueOrFalse) {
textgen text = textgen("Test1.txt");
srand(time(NULL));
text.setprefixlength(1);
text.readfile();
EXPECT_EQ("Hi ; evetyone ; my ; name ; is ; Ilya ; and ; there ; "
"the ; first ; test ; for ; this ; lab ; ", text.getprefix());
}
TEST(TEST2, TrueOrFalse) {
textgen text = textgen("Test1.txt");
srand(time(NULL));
text.setprefixlength(3);
text.readfile();
EXPECT_EQ("Hi evetyone my ; evetyone my name ; "
"my name is ; name is Ilya ; "
"is Ilya and ; Ilya and there ; and "
"there is ; there is the ; "
"is the first ; the first test ; first "
"test for ; test for "
"this ; for this lab ; this lab Hi ; "
"lab Hi evetyone ; ", text.getprefix());
}
TEST(TEST3, TrueOrFalse) {
textgen text = textgen("Test2.txt");
srand(time(NULL));
text.setprefixlength(1);
text.readfile();
EXPECT_EQ("Hi - everyone ; "
"everyone - this ; this - text ; "
"text - was ; was - created ; "
"created - for ; for - first "
"second third forth ; first - test ; "
"test - for for for Hi ; "
"second - test ; third - "
"test ; forth - test ; ", text.getall());
}
TEST(TEST4, TrueOrFalse) {
textgen text = textgen("Test1.txt");
srand(time(NULL));
text.setprefixlength(1);
text.readfile();
EXPECT_EQ("name", text.getsuffix(3));
}
TEST(TEST5, TrueOrFalse) {
textgen text = textgen("Test2.txt");
srand(time(NULL));
text.setprefixlength(1);
text.readfile();
EXPECT_EQ("third", text.getsuffix(7, 3));
}
