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

    // Recursive function to get number of words in trie.
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
    // Gets the rank of the word being checked.
    int getRank(const string& word) {

        // Node for checking
        TrieNode* tempNode = root;

        // Iterates to find the word in the trie.
        for (char c : word) {
            int idx = (char) tolower(c) - 'a';
            if (tempNode->alphabet[idx] == nullptr) {
                return -1;
            }
            tempNode = tempNode->alphabet[idx];
        }

        // If its a word end, return its rank. otherwise, return -1.
        return tempNode->wordEnd ? tempNode->wordRank : -1;
    }

    public:

    // Constructor
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

        // Vector to keep the close words to the typo.
        vector<pair<string, int>> closeWords;
        // Set to keep the seen words.
        unordered_set<string> seen;
        // Node to be used.
        TrieNode* tempNode = root;
        // Checks for issues of missplaced letters within a word

        // Iterates through the entire word.
        for (int i = checkWord.length() - 1; i >= 0; i--) {

            // Makes each letter lowercase before checking.
            char orig = tolower(checkWord[i]);
            
            // Continues if ket isnt in keys.
            if (keys.find(orig) == keys.end()) continue;

            // Iterates through all the letters around the checked letter.
            for (char c : keys[orig]) {

                // Testing word to be checked and added to closeWords.
                string cand = checkWord;
                // Replaces the letter at each position to the letter.
                cand[i] = c;

                // If the word has already been seen, continue.
                if (seen.count(cand)) continue;

                // If not, insert it into seen.
                seen.insert(cand);

                // Check if the word is a valid word.
                if (search(cand)) {

                    // Get rank and add to closeWords if so.
                    int rank = getRank(cand);
                    closeWords.emplace_back(cand, rank);
                }
            }
        }

        // Sorts the words by rank.
        // Heavy checking within search is needed or else it does. not. work.
        sort(closeWords.begin(), closeWords.end(), [](const pair<string, int>& a, const pair<string, int>& b) { 
            if (a.second == -1 && b.second == -1) return a.first < b.first;
            if (a.second == -1) return false;
            if (b.second == -1) return true;
            return a.second < b.second;
        });

        // Reduces number of suggestions.
        if (closeWords.size() > 5) {
            closeWords.resize(5);
        }

        return closeWords;
    }

    // Returns the number of words in the trie.
    int returnSize() {
        return wordCountRec(root);
    }
    
};