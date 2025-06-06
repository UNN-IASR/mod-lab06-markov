#include <deque>
#include <map>
#include <vector>
#include <string>
#include <random>

typedef std::deque<std::string> prefix;
typedef std::map<prefix, std::vector<std::string>> statetab;

class TextGenerator {
public:
    TextGenerator(int npref = 2, int maxgen = 1000);
    void build(std::istream& in);
    void generate(std::ostream& out);

private:
    int NPREF;
    int MAXGEN;
    statetab statetab;
    prefix first_prefix;

    std::mt19937 gen;

    void add_suffix(const prefix& p, const std::string& s);
    std::string get_random_suffix(const std::vector<std::string>& suffixes);
};
