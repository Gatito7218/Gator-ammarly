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

//Ease of use for using the autocorrect
struct autocorResult {
    string originalWord;
    vector<outputWord> suggestions;
    bool requiresCorrect;

    autocorResult(string& w) : originalWord(w), requiresCorrect(false) {};
};

class Interface {
    private:
        BKTree bkTreeImplement;
        Trie trieImplement;

    public:

    //inserting the common word data set into the trees
    //CSV file 2 columns, 1st is word, 2nd is frequency; its already sorted so disregard frequency and attach rank based on order
    //seperated by comma
    bool loadBKTree(string& filename);
    bool loadTrie(string& filename);

    //inserting into trees
    void insertResultBKTree(string& word, int rank);
    void insertResultTrie(string& word, int rank);

    bool searchWordBKTree(string& word);
    bool searchWordTrie(string& word);


    //Core of the structure, returns the autocorrect suggestions
    autocorResult autocorrectBKTree(string& word, int maxDist);
    vector<pair<string, int>> autocorrectTrie(string& word);
    


    void basicCLI(); //testing
};