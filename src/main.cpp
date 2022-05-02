#include "textgen.h"
#include <fstream>
#include <iostream>

int main()
{
    ifstream fin;
    fin.open("text.txt");
    if (!fin.is_open())
    {
        cout << "Error!";
        exit(0);
    }
    vector<string> words;
    string word;
    while (!fin.eof())
    {
        fin >> word;
        words.push_back(word);
    }
    fin.close();

    Markov Gen(words, 2, 1000);
    string line = Gen.TextGen();

    ofstream fout;
    fout.open("output.txt");
    if (!fout.is_open())
    {
        cout << "Error";
        exit(0);
    }
    fout.clear();
    fout << line;
    fout.close();

    return 1;
}
