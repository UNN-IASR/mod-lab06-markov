#include"textgen.h"

using namespace std;

Gen::Gen(string arr, int val1, int val2)
{
    srand(4561);
    NPREF = val1;
    MAXGEN = val2;
    data = arr;
    int i = 0, state = 0, count = -1;
    while (arr[i] != '\0')
    {
        if (state == 0 && arr[i] != ' ' && arr[i] != '\r' && arr[i] != '\n')
        {
            state = 1;
            count++;
            words.push_back("");
            words[count] = words[count] + arr[i];
        }
        else if (state == 1 && (arr[i] == ' ' || arr[i] == '\r' || arr[i] == '\n'))
        {
            state = 0;
        }
        else if (state == 1 && arr[i] != ' ' && arr[i] != '\r' && arr[i] != '\n')
        {
            words[count] = words[count] + arr[i];
        }
        i++;
    }
    for (int i = 0; i < words.size() - NPREF + 1; i++)
    {
        prefix prf;
        for (int j = 0; j < NPREF; j++) prf.push_back(words[i + j]);
        if (i + NPREF < words.size())
            statetab[prf].push_back(words[i + NPREF]);
        else statetab[prf].push_back("END_OF_FILE");
    }
}
string Gen::getText()
{
    prefix str;
    for (int i = 0; i < NPREF; i++) str.push_back(words[i]);
    string answer = "";
    int count = 1;
    while (answer.size() < MAXGEN)
    {
        if (answer.size() == 0)
        {
            for (int i = 0; i < NPREF; i++)
                answer = answer + str[i] + ' ';
        }
        int val;
        if (statetab[str].size() == 1 && statetab[str][0] == "END_OF_FILE") break;
        if (statetab[str].size() == 0) break;
        val = rand() % statetab[str].size();
        if (statetab[str][statetab[str].size() - 1] == "END_OF_FILE") val = rand() % (statetab[str].size() - 1);
        answer = answer + statetab[str][val] + ' ';
        if (count * 100 - answer.size() < 0 || count * 100 - answer.size() > 100)
        {
            count++;
            answer = answer + '\n';
        }
        string tmp = statetab[str][val];
        for (int i = 0; i < NPREF - 1; i++) str[i] = str[i + 1];
        str[NPREF - 1] = tmp;
    }
    return answer;
}
Gen::Gen(map<prefix, vector<string> > val, vector<string> word, int val1, int val2)
{
    NPREF = val1;
    MAXGEN = val2;
    statetab = val;
    words = word;
}
