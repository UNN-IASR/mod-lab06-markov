// Copyright 2024 Maz
#include <gtest/gtest.h>
#include "../include/textgen.h"

TEST(Test1, MakePref) {
typedef std::deque<std::string> prefix;
const char* st = "Встретились на ";
prefix exp;
std::vector<std::string> strs = chstr_to_vecstr(st);
exp.push_back(strs[0]); exp.push_back(strs[1]);
prefix eq{ "Встретились", "на" };
EXPECT_EQ(exp, eq);
}

TEST(Test2, MakePair) {
typedef std::deque<std::string> prefix;
std::map<prefix, std::vector<std::string> > statetab;
const char* st = "Встретились на дороге ";
prefix exp;
std::vector<std::string> strs = chstr_to_vecstr(st);
exp.push_back(strs[0]); exp.push_back(strs[1]);
statetab.insert({exp, {strs[2]}});
prefix pr{ "Встретились" , "на" };
std::map<prefix , std::vector<std::string> >eq = {
{pr, { "дороге"}} };
EXPECT_EQ(statetab[exp],
eq[pr]);
}

TEST(Test3, OneSuffChoose) {
typedef std::deque<std::string> prefix;
std::map<prefix, std::vector<std::string> > statetab;
statetab = { {{"Встретились", "на"},
{ "дороге"}}, {{"на", "дороге"}, { "барин"}},
{{"дороге", "барин"}, {"и"}}, {{"барин", "и"},
{ "мужик."}} };
std::vector<std::string> eq;
auto item = statetab.begin();
while (item != statetab.end()) {
if (item->second.size() == 1) { eq = item->second; break; }
item = statetab.begin();
std::advance(item, rand() % statetab.size());
}
EXPECT_EQ(eq.size() == 1, true);
}

TEST(Test4, MultSuffChoose) {
typedef std::deque<std::string> prefix;
std::map<prefix, std::vector<std::string> > statetab;
statetab = { {{"Встретились", "на"}, { "дороге", "пути"}} ,
{{"на", "дороге"}, { "барин"}}, { {"дороге", "барин"},
{ "и"}}, { {"барин", "и"}, { "мужик."}} };
std::vector<std::string> eq;
auto item = statetab.begin();
while (item != statetab.end()) {
if (item->second.size() != 1) { eq = item->second; break; }
item = statetab.begin();
std::advance(item, rand() % statetab.size());
}
EXPECT_EQ(eq.size() > 1, true);
}

TEST(Test5, MakeText) {
typedef std::deque<std::string> prefix;
std::map<prefix, std::vector<std::string> > statetab;
int num = 0;
prefix curr { "Встретились", "на" }, all { "Встретились", "на" };
std::map<prefix, std::vector<std::string> >expect = {
{prefix{"Встретились", "на"},
std::vector<std::string>{ "дороге"}} , {prefix{"на", "дороге"},
std::vector<std::string>{ "барин"}},
{prefix{"дороге", "барин"}, std::vector<std::string>{
"и"}}, {prefix{"барин", "и"},
std::vector<std::string>{ "мужик."}} };
while (expect.find(curr) != expect.end() && num < 10) {
all.push_back(expect[curr].at(0));
prefix tmp;
tmp.push_back(curr[1]); tmp.push_back(expect[curr].at(0));
curr = tmp;
num++;
}
std::vector<std::string> vec;
vec.push_back(all[0] +
std::string(" ") + all[1] + std::string(" ") +
all[2] + std::string(" ") + all[3] +
std::string(" ") + all[4] + std::string(" ") +
all[5]);
vec.push_back("Встретились на дороге барин и мужик.");
EXPECT_EQ(vec[0], vec[1]);
}
