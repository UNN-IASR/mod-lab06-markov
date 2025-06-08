#ifndef TEXTGEN_H
#define TEXTGEN_H

#include <deque>
#include <map>
#include <string>
#include <vector>
#include <istream>

typedef std::deque<std::string> prefix;
typedef std::map<prefix, std::vector<std::string>> statetab_t;

// Builds the prefix-to-suffix map from the input stream.
// npref: number of words in the prefix.
void build_prefix_map(std::istream& in, statetab_t& statetab, int npref);

// Generates up to maxgen words based on the state table.
// Returns a vector of generated words.
std::vector<std::string> generate_text(const statetab_t& statetab, int npref, int maxgen);

#endif // TEXTGEN_H
