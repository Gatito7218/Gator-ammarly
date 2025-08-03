#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <chrono>
#include "BKTree.h"
#include "Trie.h"


using namespace std;

//string lowercase(string& inpstr) {
//    string outstr = inpstr;
//    std::transform(outstr.begin(), outstr.end(), outstr.begin(), ::tolower);
//    return outstr;
//};

//Ease of use for using the autocorrect
struct autocorResult {
    string originalWord;
    vector<outputWord> suggestions;
    bool requiresCorrect;

    autocorResult(string& w) : originalWord(w), requiresCorrect(false) {};
};

struct trieAutocorResult {
    string originalWord;
    vector<string> suggestions;
    bool requiresCorrect;

    trieAutocorResult(string& w) : originalWord(w), requiresCorrect(false) {};
};

class Interface {
    private:
        BKTree bkTreeImplement;
        Trie trieImplement;

    public:
    //Create some funcion for word regex and extracting words; changing to lower case etc.
    //Initialize the BKTree and the trie here as well and train them on the data set (will be added later)

    //inserting the common word data set into the trees
    //CSV file 2 columns, 1st is word, 2nd is frequency; its already sorted so disregard frequency and attach rank based on order
    //seperated by comma
    void loadBKTree(string& filename);
    void loadTrie(string& filename);

    //inserting into trees
    void insertResultBKTree(string& word, int rank);
    void insertResultTrie(string& word);


    //use regex to get words from the textfile
    vector<string> wordExtraction(string& text);

    //TO-DO: probably better to have a function that just returns a vector of the results
    autocorResult autocorrectBKTree(string& word, int maxDist);
    vector<string> autocorrectTrie(string& word);
    


    void basicCLI(); //testing
};