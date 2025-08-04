#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <cctype>

using namespace std;

struct wrongWord {

    int lineIndex;
    int tokenIndex;
    string ogWord;
};

string underline(const string& word) {
    // red, underline, text, underline, red
    //cout << "\033[1;31m" << "\033[4m" << "This text will be underlined." << "\033[24m" << "\033[0m" << endl; 

    return ("\033[1;31m\033[4m" + word + "\033[24m\033[0m");
}

string removeSymbols(const string& word) {
    
    string result;

    for (char c : word) {

        if (isalnum(c)) {
            result += c;
        }
    }

    return result;
}

vector<pair<string, bool>> tokenize(const string& line) {

    vector<pair<string, bool>> tokens;

    regex word_regex("(\\w+(?:['’`-]\\w+)*|\\W+)");

    for (auto it = sregex_iterator(line.begin(), line.end(), word_regex); it != sregex_iterator(); it++) {

        string token = it->str();
        bool isWord = regex_match(token, regex("\\w+(?:['’`-]\\w+)*"));
        tokens.push_back({token, isWord});

    }

    return tokens;

}