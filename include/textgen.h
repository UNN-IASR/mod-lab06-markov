#include <deque>
#include <map>
#include <string>
#include <vector>

using std::deque;
using std::map;
using std::string;
using std::vector;

class TextGenerator {
 private:
  const int PREFIX_LENGTH = 2;
  const int OUTPUT_LENGTH = 1000;

  map<deque<string>, vector<string>> table;

  void generateTable(string filename);

 public:
  TextGenerator(string filename);

  string generateText();
  string generateText(string filename);
};