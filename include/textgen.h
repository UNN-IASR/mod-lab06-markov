// Copyright 2022 UNN-IASR
#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_

#include <deque>
#include <map>
#include <random>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

typedef std::deque<std::string> prefix;
typedef std::map<prefix, std::vector<std::string>> statetab;

class TextGenerator {
private:

	statetab _table;

	prefix _first_prefix;

	std::vector<std::string> __get_words_from_file__(const std::string& file_path);

	statetab __generate_state_table__(const std::vector<std::string>& words, size_t prefix_length);

	std::string __generate_text__(size_t max_words);

	void __write_text_to_file__(const std::string& file_path, const std::string& text);

public:

	void __create_state_table__(const std::string& file_path, size_t prefix_length);

	void __generate_text_and_write_to_file__(size_t max_words, const std::string& file_path);

	const statetab& __get_state_table__();
};

#endif