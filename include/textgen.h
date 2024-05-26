// Copyright 2024 UNN-IASR
#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>
#include <map>
#include <vector>
#include <random>
#include <ctime>
#include <string>

// Константы для количества слов в префиксе
// и максимального количества генерируемых слов
const int NPREF = 2;
const int MAXGEN = 1000;

// Определение типа для префикса
typedef std::deque<std::string> prefix;

// Таблица состояний для префиксов и суффиксов
extern std::map<prefix, std::vector<std::string>> statetab;

// Функция для построения таблицы префиксов и суффиксов из входного файла
void build(const std::string& filename, int NPREF);

// Функция для генерации текста заданной
// длины на основе таблицы префиксов и суффиксов
std::string generate_text(int max_words);

#endif  // INCLUDE_TEXTGEN_H_
