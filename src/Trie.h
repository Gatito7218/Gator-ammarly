#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <memory>
#include <stack>
#include <cctype>
#include <utility>
#include <unordered_set>

using namespace std;


struct TrieNode {

    TrieNode* alphabet[26];
    int wordRank;
    bool wordEnd;

    TrieNode() {

        wordRank = -1;
        wordEnd = false;

        for (int i = 0; i < 26; i++) {

            alphabet[i] = nullptr;
        }
    }

};


class Trie {
    private:

    TrieNode* root;
    unordered_map<char, string> keys;

    int wordCountRec(TrieNode* node) {
        if (node == nullptr) {
            return 0;
        }

        int count = 0;

        if (node->wordEnd) {
            count++;
        }

        for (auto letter : node->alphabet) {
            count += wordCountRec(letter);
        }

        return count;
    }
    //implemented by David to fix a bug; Rank wasn't being properly inserted into the checkClose function
    int getRank(const string& word) {
        TrieNode* tempNode = root;
        for (char c : word) {
            int idx = (char) tolower(c) - 'a';
            if (tempNode->alphabet[idx] == nullptr) {
                return -1;
            }
            tempNode = tempNode->alphabet[idx];
        }
        return tempNode->wordEnd ? tempNode->wordRank : -1;
    }

    public:

    Trie() {

        root = new TrieNode();
        
        keys = {
            {'a', "qwsz"}, {'b', "vghn"}, {'c', "xdfv"}, {'d', "ersfcx"},
            {'e', "wsdr"}, {'f', "rtgdvc"}, {'g', "tyfhvb"}, {'h', "yugjnb"},
            {'i', "ujko"}, {'j', "uikhmn"}, {'k', "jiolm"}, {'l', "kop"},
            {'m', "njk"}, {'n', "bhjm"}, {'o', "iklp"}, {'p', "ol"},
            {'q', "wa"}, {'r', "edft"}, {'s', "awedxz"}, {'t', "rfgy"},
            {'u', "yhji"}, {'v', "cfgb"}, {'w', "qase"}, {'x', "zsdc"},
            {'y', "tghu"}, {'z', "asx"}
        };  
    }

    ~Trie() {};

    void insert(const string& insertWord, int rank) {

        // Creates new node to iterate through to get to end of word
        TrieNode* tempNode = root;

        // Iterates through the inserted word, with c as each character
        for (char c : insertWord) {

            // Takes the character and subtracts 'a', getting a number between 0 and 25
            int index = (char) tolower(c) - 'a';

            // Checks if a node exists at the index, if not, create a new node there.
            if (tempNode->alphabet[index] == nullptr) {

                tempNode->alphabet[index] = new TrieNode();
            }

            // Moves node/letter to next letter in word.
            tempNode = tempNode->alphabet[index];
        }

        // Marks the last letter in the word to be the word end, therefore showing a valid word.
        tempNode->wordEnd = true;
        tempNode->wordRank = rank;
    }

    bool search(const string&  searchWord) {

        // Creates new node to iterate through to get to end of word
        TrieNode* tempNode = root;

        // Iterates through the inserted word, with c as each character
        for (char c : searchWord) {

            // Takes the character and subtracts 'a', getting a number between 0 and 25
            int index = (char) tolower(c) - 'a';

            // Checks if a node exists at the index, if not, return false.
            if (tempNode->alphabet[index] == nullptr) {

                return false;
            }

            // Moves node/letter to next letter in word.
            tempNode = tempNode->alphabet[index];
        }

        // Returns if last letter, if exists, is the end of a word.
        return tempNode->wordEnd;
    }

    vector<pair<string, int>> checkClose(const string& checkWord) {
        vector<pair<string, int>> closeWords;
        unordered_set<string> seen;
        TrieNode* tempNode = root;
        //Checks for issues of missplaced letters within a word
        for (int i = checkWord.length() - 1; i >= 0; i--) {

                char orig = tolower(checkWord[i]);
                if (keys.find(orig) == keys.end()) continue;

                for (char c : keys[orig]) {
                    string cand = checkWord;
                    cand[i] = c;
                    if (seen.count(cand)) continue;
                    seen.insert(cand);
                    if (search(cand)) {
                        int rank = getRank(cand);
                        closeWords.emplace_back(cand, rank);
                    }
                }
            }
        //heavy checking within search is needed or else it does. not. work.
        sort(closeWords.begin(), closeWords.end(), [](const pair<string, int>& a, const pair<string, int>& b) { 
            if (a.second == -1 && b.second == -1) return a.first < b.first;
            if (a.second == -1) return false;
            if (b.second == -1) return true;
            return a.second < b.second;
        });

        if (closeWords.size() > 5) { //Don;t want too many suggestions
            closeWords.resize(5);
        }

        return closeWords;
    }

    int returnSize() {
        return wordCountRec(root);
    }
    
};