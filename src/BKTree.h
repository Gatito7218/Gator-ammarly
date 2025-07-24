#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <memory>

using namespace std;

struct Node {
    string word;
    unordered_map<int, unique_ptr<Node>> children;
    
    Node(string& w) : word(w) {};
    void addChildren();
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
        vector<string> search(string& w);
};