#include <deque>
#include <map>
#include <random>
#include <string>
#include <vector>

using std::deque;
using std::map;
using std::mt19937;
using std::string;
using std::vector;

class TextGenerator {
 private:
  const int PREFIX_LENGTH = 2;

  map<deque<string>, vector<string>> table;
  mt19937 generator;

  deque<string> randomStart();
  string nextWord(deque<string> prefixes);

 public:
  TextGenerator(string filename);

  string getTable();

  string generateText(int length);
  string generateText(string filename, int length);
};