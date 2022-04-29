// Copyright 2022 UNN-IASR
#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>

class textgen {
 private:
int index;
int prelen;
int reslength;
    std::string path;
    std::string res;

 public:
std::vector < std::vector < std::string>> table;
textgen(std::string path) {
this->path = path;
index = -1;
prelen = 1;
res = "";
table = std::vector<std::vector <std::string>>();
}
void setprelen(int);
int getprelen();
std::string getall();
void generate();
std::string getpre();
std::string getsuf();
void randomizeindex();
void getnewindex(std::vector<std::string>);
void readfile();
void checkpre(std::vector<std::string>);
std::string getreslength();
std::string getres();
std::string getsuf(int);
std::string getsuf(int, int);
void generate(int);
bool isEqual(std::string, std::string);
};
