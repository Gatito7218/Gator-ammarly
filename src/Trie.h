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

// Considering adding a way to find distance of keys from eachother
// to get nearby typos

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

    void insert(string insertWord) {

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
    }

    bool search(string searchWord) {

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

    vector<string> checkClose(string checkWord) {
        vector<string> closeWords;
        TrieNode* tempNode = root;

        for (int i = checkWord.length() - 1; i >= 0; i--) {

            vector<string> tempWords;

                for (char c : keys[(char) tolower(checkWord[i])]) {

                    tempWords.push_back(checkWord.substr(0, i) + c + checkWord.substr(i + 1));
                }

                for (auto word : tempWords) {

                    if (search(word)) {

                        closeWords.push_back(word);

                        if (closeWords.size() >= 3) {

                            return closeWords;
                        }
                    }
                }
            }

        return closeWords;
    }

    int returnSize() {
        return wordCountRec(root);
    }
    
};