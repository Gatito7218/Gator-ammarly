#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <memory>
#include <stack>
#include <cctype>

using namespace std;

//TO-DO: multiple children of the same distance, will use a vector, I don't wanna do that right now tho
//Also I did not account for the word rank yet, just wanted to do the basic code logic of the tree
struct BKNode {
    string word;
    unordered_map<int, vector<unique_ptr<BKNode>>> children;
    int rank; //the file used to train has the frequency of each english language word ranked
    
    BKNode(string& w, int rank) : word(w), rank(rank) {};
    void addChildren(string& inpW, int distance, int rank);
};

//For ease of use for dealing with words of the same distance but different rank
struct outputWord {
    string word;
    int distance;
    int rank;
    outputWord() : word(""), distance(0), rank(0) {};
    outputWord(string& w, int d, int rank) : word(w), distance(d), rank(rank) {};
};


class BKTree {
    private:
        unique_ptr<BKNode> root;
        size_t treeSize;
        int LevenshteinDistance(string& s1, string& s2); //Creates a value that quantifies the difference between 2 strings; this is the main function for dealing with word similarity
    public:
        //it really is nice and simple
        BKTree();
        ~BKTree();
        void insert(string& w, int rank);
        bool contains(string& w); //see if the word already exists within the list
        vector<outputWord> search(string& w, int maxDist);
        int returnSize();
};