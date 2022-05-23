#include <string>
#include <deque>
#include <vector>
#include <map>
using namespace std;
class PROG
{
private:
    string data;
    vector<string> words;
    typedef deque<string> prefix;
    map<prefix, vector<string> > statetab;
    int NPREF;
    int MAXPROG;
public:
    PROG(string arr, int val1, int val2);
    string getText();
    PROG(map<prefix, vector<string> > val, vector<string> words, int val1, int val2);
};
