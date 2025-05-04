// Copyright 2022 UNN-IASR
// Copyright 2024 Your Name
#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_

#include <deque>
#include <map>
#include <string>
#include <vector>
#include <memory>

typedef std::deque<std::string> Prefix;

class TextGenerator {
 public:
    TextGenerator(const std::string& file_path, size_t prefix_length);
    explicit TextGenerator(size_t prefix_length);
    
    std::string GenerateText(size_t text_length = 1000) const;
    void AddTransition(const Prefix& pref, const std::string& word);
    Prefix GetEndPrefix() const { return end_prefix_; }

 private:
    const size_t prefix_length_;
    Prefix initial_prefix_;
    Prefix end_prefix_;
    std::map<Prefix, std::vector<std::string>> state_table_;
    
    void AnalyzeText(const std::string& file_path);
    std::string GenerateSuffix(const Prefix& pref) const;
};

#endif  // INCLUDE_TEXTGEN_H_