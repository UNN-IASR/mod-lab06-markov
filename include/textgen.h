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
  const int OUTPUT_LENGTH = 1000;

  map<deque<string>, vector<string>> table;
  mt19937 generator;

  deque<string> randomStart();
  string nextWord();

 public:
  TextGenerator(string filename);

  void printTable();

  string generateText();
  string generateText(string filename);
};