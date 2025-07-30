#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <memory>
#include <stack>
#include <cctype>

using namespace std;

// I would call it Node but theres already a Node and i dont wanna mix things up
// idk how much of this im gonna do but hopefully a lot
// - Gabriel

struct TrieNode {

    TrieNode* alphabet[26];
    bool wordEnd;

    TrieNode() {

        wordEnd = false;
        for (int i = 0; i < 26; i++) {
            alphabet[i] = nullptr;
        }

    }

};

// Ill make the functions later they dont seem to hard to implement
class Trie {
    private:

    TrieNode* root;

    public:

    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {

    }

    bool search(string word) {
        return false;
    }

    string checkClose(string word) {
        return "";


    }

    void deleteWord(string word) {

    }

    
};