// include/textgen.h
#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_

#include <deque>
#include <map>
#include <string>
#include <vector>
#include <istream>

typedef std::deque<std::string> prefix;
typedef std::map<prefix, std::vector<std::string>> statetab_t;

// Builds the prefix-to-suffix map from the input stream.
void build_prefix_map(
    std::istream &in,
    statetab_t &statetab,
    int npref);

// Generates up to maxgen words based on the state table.
std::vector<std::string> generate_text(
    const statetab_t &statetab,
    int npref,
    int maxgen);

#endif  // INCLUDE_TEXTGEN_H_
