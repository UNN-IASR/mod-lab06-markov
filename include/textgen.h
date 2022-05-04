#include <string>
#include <deque>
#include <vector>
#include <map>
using namespace std;
class Gen
{
private:
    string data;
    vector<string> words;
    typedef deque<string> prefix;
    map<prefix, vector<string> > statetab;
    int NPREF;
    int MAXGEN;
public:
    Gen(string arr, int val1, int val2);
    string getText();
    Gen(map<prefix, vector<string> > val, vector<string> words, int val1, int val2);
};
