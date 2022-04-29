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
for (int j = 0; j < this->prelen; j++) {
str = str + this->table[i][j] + " ";
}
str = str + "- ";
for (int j = prelen; j < this->table[i].size(); j++) {
str = str + this->table[i][j] + " ";
}
str = str + "; ";
}
return str;
}
void textgen::setprelen(int length) {
this->prelen = length;
}
void textgen::randomizeindex() {
int suf = rand_r() % (this->table[this->index].size() - prelen)
+ prelen;
res += this->table[this->index][suf] + " ";
reslength++;
std::vector<std::string> buffer = std::vector<std::string>();
for (int i = 1; i < this->prelen; i++) {
buffer.insert(buffer.end(), this->table[this->index][i]);
}
buffer.insert(buffer.end(), this->table[this->index][suf]);
getnewindex(buffer);
}
void textgen::getnewindex(std::vector<std::string> buffer) {
int i = 0;
int k = 0;
for (i = 0; i < this->table.size(); i++) {
k = 0;
for (int j = 0; j < this->prelen; j++) {
if (isEqual(this->table[i][j], buffer[j])) {
k++;
}
}
if (k == this->prelen)
break;
}
this->index = i;
}
int textgen::getprelen() {
return this->prelen;
}
void textgen::generate() {
if (index == -1) {
for (int i = 0; i < this->prelen; i++)
res = res + this->table[0][i] + " ";
index = 0;
this->reslength += this->prelen;
} else {
randomizeindex();
}
}
std::string textgen::getpre() {
    std::string pre = "";
for (int i = 0; i < this->table.size(); i++) {
for (int j = 0; j < this->prelen; j++) {
pre = pre + table[i][j] + " ";
}
pre = pre + "; ";
}
return pre;
}
std::string textgen::getsuf() {
    std::string suf = "";
suf = "";
for (int i = 0; i < this->table.size(); i++) {
for (int j = this->prelen; j < this->table[i].size(); j++) {
suf = suf + table[i][j] + " ";
}
suf = suf + "; ";
}
return suf;
}
void textgen::checkpre(std::vector<std::string> presuf) {
int k = 0;
bool intable = false;
for (int i = 0; i < this->table.size(); i++) {
k = 0;
for (int j = 0; j < this->prelen; j++) {
if (isEqual(this->table[i][j], presuf[j])) {
k++;
}
}
if (k == prelen) {
this->table[i].push_back(presuf.back());
intable = true;
break;
}
}
if (!intable) this->table.insert(this->table.end(), presuf);
}
std::string textgen::getres() {
return this->res;
}
std::string textgen::getreslength() {
return std::to_string(reslength);
}
std::string textgen::getsuf(int steps) {
for (int i = 0; i < steps; i++)
generate();
return this->table[index][1];
}
std::string textgen::getsuf(int steps, int suf) {
for (int i = 0; i < steps; i++)
generate();
return this->table[index][suf];
}
void textgen::generate(int steps) {
for (int i = 0; i < steps - this->prelen + 1; i++)
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
void textgen::readfile() {
std::ifstream fin;
fin.open(this->path);
std::vector<std::string> buffer = std::vector<std::string>();
    std::string str = "";
if (!fin.is_open()) {
std::cout << "File not opened";
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
if (i < buffer.size() - this->prelen) {
for (int j = i; j < i + this->prelen + 1; j++) {
bufferfor.insert(bufferfor.end(), buffer[j]);
}
} else {
for (int j = i; j < buffer.size(); j++) {
bufferfor.insert(bufferfor.end(), buffer[j]);
}
for (int j = 0; j < this->prelen - (buffer.size() - i - 1); j++) {
bufferfor.insert(bufferfor.end(), buffer[j]);
}
}
checkpre(bufferfor);
}
}
