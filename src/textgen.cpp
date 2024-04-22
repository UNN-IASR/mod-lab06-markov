// Copyright 2024 Maz
#include "../include/textgen.h"

const int NPREF = 2;
const int MAXGEN = 1000;

prefix cur;

std::vector<std::string> chstr_to_vecstr(const char* chtext) {
  std::vector<std::string> exp;
  std::stringstream s = std::stringstream(chtext);
  const char* const delimeter = " ";
  char* words = new char[sizeof(s)];
  s.read(words, sizeof(s));
  char* token = std::strtok(words, delimeter);
  while (token != NULL) {
  exp.push_back(token);
  token = std::strtok(nullptr, delimeter);
  }
  return exp;
}

void finput(std::deque<std::string>* arr) {
std::ifstream input("data.txt");
std::deque<std::string> tmp;
char* ch = new char[100];
while (input >> ch) {
tmp.push_back(std::string(ch));
ch = new char[100];
}
*arr = tmp;
}
void foutput(std::deque<std::string> arr) {
std::ofstream output("out.txt");
for (int i = 0; i < arr.size(); i++) {
output << arr[i] << " ";
if (i % 10 == 0 && i != 0) output << std::endl;
}
output.close();
}

void generate(std::map<prefix, std::vector<std::string> > state_tab) {
std::map<prefix, std::vector<std::string> > st = state_tab;
std::deque<std::string> arr;
int num = 0, invec = 0;
std::random_device os_seed;
const u32 seed = os_seed();
engine generator(seed);
for (int i = 0; i < NPREF; i++) {
arr.push_back(cur[i]);
}
while (st.find(cur) != st.end() && num < MAXGEN-2) {
std::uniform_int_distribution< u32 > distribute(0, st[cur].size()-1);
invec = distribute(generator);
arr.push_back(st[cur].at(invec));
prefix tmp;
for (int j = 1; j < NPREF; j++)tmp.push_back(cur[j]);
tmp.push_back(st[cur].at(invec));
cur = tmp;
num++;
}
foutput(arr);
}

std::map<prefix, std::vector<std::string> > make_statetab() {
std::map<prefix, std::vector<std::string> > st;
std::deque<std::string> words;
finput(&words);
prefix Prefix;
for (int i = 0; i < NPREF + 1; i++) {
if (i != NPREF) { Prefix.push_back(words[i]); cur.push_back(words[i]);
} else { st[Prefix].push_back(words[i]); }
}
Prefix.pop_front();
Prefix.push_back(words[NPREF]);
for (int i = NPREF+1; i < words.size(); i++) {
st[Prefix].push_back(words[i]);
Prefix.pop_front();
Prefix.push_back(words[i]);
}
return st;
}
