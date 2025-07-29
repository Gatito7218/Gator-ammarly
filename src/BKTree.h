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
struct Node {
    string word;
    unordered_map<int, unique_ptr<Node>> children;
    
    Node(string& w) : word(w) {};
    void addChildren(string& inpW, int distance);
};


class BKTree {
    private:
        unique_ptr<Node> root;
        size_t treeSize;
        int LevenshteinDistance(string& s1, string& s2); //Creates a value that quantifies the difference between 2 strings; this is the main function for dealing with word similarity
    public:
        //it really is nice and simple
        BKTree();
        ~BKTree();
        void insert(string& w);
        bool contains(string& w); //see if the word already exists within the list
        vector<string> search(string& w, int maxDist);
        int returnSize();
};