// Copyright 2022 UNN-IASR
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "textgen.h"
#define rand_r rand
std::string textgen::getall() {
    std::string str = "";
for (int i = 0; i < this->table.size(); i++) {
for (int j = 0; j < this->prefixlength; j++) {
str = str + this->table[i][j] + " ";
}
str = str + "- ";
for (int j = prefixlength; j < this->table[i].size(); j++) {
str = str + this->table[i][j] + " ";
}
str = str + "; ";
}
return str;
}
void textgen::setprefixlength(int length) {
this->prefixlength = length;
}
int textgen::getprefixlength() {
return this->prefixlength;
}
void textgen::generate() {
if (index == -1) {
for (int i = 0; i < this->prefixlength; i++)
result = result + this->table[0][i] + " ";
index = 0;
this->resultlength += this->prefixlength;
} else {
randomizeindex();
}
}
void textgen::randomizeindex() {
int suffix = rand_r() % (this->table[this->index].size() - prefixlength)
+ prefixlength;
result += this->table[this->index][suffix] + " ";
resultlength++;
std::vector<std::string> buffer = std::vector<std::string>();
for (int i = 1; i < this->prefixlength; i++) {
buffer.insert(buffer.end(), this->table[this->index][i]);
}
buffer.insert(buffer.end(), this->table[this->index][suffix]);
getnewindex(buffer);
}
void textgen::getnewindex(std::vector<std::string> buffer) {
int i = 0;
int k = 0;
for (i = 0; i < this->table.size(); i++) {
k = 0;
for (int j = 0; j < this->prefixlength; j++) {
if (isEqual(this->table[i][j], buffer[j])) {
k++;
}
}
if (k == this->prefixlength)
break;
}
this->index = i;
}
std::string textgen::getprefix() {
    std::string prefix = "";
for (int i = 0; i < this->table.size(); i++) {
for (int j = 0; j < this->prefixlength; j++) {
prefix = prefix + table[i][j] + " ";
}
prefix = prefix + "; ";
}
return prefix;
}
std::string textgen::getsuffix() {
    std::string suffix = "";
suffix = "";
for (int i = 0; i < this->table.size(); i++) {
for (int j = this->prefixlength; j < this->table[i].size(); j++) {
suffix = suffix + table[i][j] + " ";
}
suffix = suffix + "; ";
}
return suffix;
}
void textgen::checkprefix(std::vector<std::string> prefixsuffix) {
int k = 0;
bool intable = false;
for (int i = 0; i < this->table.size(); i++) {
k = 0;
for (int j = 0; j < this->prefixlength; j++) {
if (isEqual(this->table[i][j], prefixsuffix[j])) {
k++;
}
}
if (k == prefixlength) {
this->table[i].push_back(prefixsuffix.back());
intable = true;
break;
}
}
if (!intable) this->table.insert(this->table.end(), prefixsuffix);
}
void textgen::readfile() {
std::ifstream fin;
fin.open(this->path);
std::vector<std::string> buffer = std::vector<std::string>();
    std::string str = "";
if (!fin.is_open()) {
std::cout << "Ошибка открытия файла";
} else {
while (!fin.eof()) {
fin >> str;
buffer.push_back(str);
}
}
fin.close();
std::vector<std::string> bufferfor = std::vector<std::string>();
for (int i = 0; i < buffer.size(); i++) {
bufferfor.clear();
if (i < buffer.size() - this->prefixlength) {
for (int j = i; j < i + this->prefixlength + 1; j++) {
bufferfor.insert(bufferfor.end(), buffer[j]);
}
} else {
for (int j = i; j < buffer.size(); j++) {
bufferfor.insert(bufferfor.end(), buffer[j]);
}
for (int j = 0; j < this->prefixlength - (buffer.size() - i - 1); j++) {
bufferfor.insert(bufferfor.end(), buffer[j]);
}
}
checkprefix(bufferfor);
}
}
std::string textgen::getresult() {
return this->result;
}
std::string textgen::getresultlength() {
return std::to_string(resultlength);
}
std::string textgen::getsuffix(int steps) {
for (int i = 0; i < steps; i++)
generate();
return this->table[index][1];
}
std::string textgen::getsuffix(int steps, int suffix) {
for (int i = 0; i < steps; i++)
generate();
return this->table[index][suffix];
}
void textgen::generate(int steps) {
for (int i = 0; i < steps - this->prefixlength + 1; i++)
generate();
}
bool textgen::isEqual(std::string s1, std::string s2) {
bool isEqual = true;
if (s1.length() == s2.length()) {
for (int i = 0; i < s1.length(); i++) {
if (s1[i] != s2[i]) {
isEqual = false;
}
}
return isEqual;
} else {
return false;
}
}
