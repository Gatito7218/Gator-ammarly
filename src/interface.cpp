#include "interface.h"


bool Interface::loadBKTree(string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        cout << "BK Tree did not load properly - file not found: " << filename << endl;
        return false;
    }

    auto start = chrono::high_resolution_clock::now();
    vector<pair<string, int>> words;
    string line;
    int rank = 1;
    int numLoaded = 0;
    
    while (getline(file, line) && numLoaded < 150000) {
        if (!line.empty()) {
            size_t comma = line.find(','); //csv is seperated by single comma!
            if (comma != string::npos) {
                string word = line.substr(0, comma);
                // Clean the word and remove any extra whitespace or quotes
                word.erase(remove_if(word.begin(), word.end(), [](char c) {
                    return c == '"' || c == '\r' || c == '\n' || isspace(c);
                }), word.end());
                
                //convert to lowercase for consistency
                transform(word.begin(), word.end(), word.begin(), ::tolower);
                
                if (!word.empty() && all_of(word.begin(), word.end(), ::isalpha)) {
                    insertResultBKTree(word, rank);
                    numLoaded++;
                }
            }
            rank++;
        }
    }

    file.close();
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "BKTree loaded successfully!" << endl;
    cout << "Size: " << bkTreeImplement.returnSize() << endl;
    cout << "Load time: " << duration.count() << "ms" << endl;
    return true;
}

void Interface::insertResultBKTree(string& word, int rank) {
    bkTreeImplement.insert(word, rank);
}

autocorResult Interface::autocorrectBKTree(string& w, int maxDist) {
    auto start = chrono::high_resolution_clock::now();

    autocorResult res(w);
    if (bkTreeImplement.contains(w)) {
        res.requiresCorrect = false;
    }
    else {
        vector<outputWord> suggestion = bkTreeImplement.search(w, maxDist);
        res.suggestions = suggestion;
        res.requiresCorrect = true;
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "BKTree Result took: " << duration.count() << "ms" << endl;
    return res;
}

// Code adapted from earlier loadBKTree, credits to David Miranda
bool Interface::loadTrie(string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        cout << "Trie did not load properly - file not found: " << filename << endl;
        return false;
    }

    int numLoaded = 0;
    auto start = chrono::high_resolution_clock::now();
    vector<pair<string, int>> words;
    string line;
    int rank = 1;
    
    while (getline(file, line) && numLoaded < 150000) {
        if (!line.empty()) {
            size_t comma = line.find(','); //csv is seperated by single comma
            if (comma != string::npos) {
                string word = line.substr(0, comma);
                //Cleaning the word
                word.erase(remove_if(word.begin(), word.end(), [](char c) {
                    return c == '"' || c == '\r' || c == '\n' || isspace(c);
                }), word.end());
                
                // Convert to lowercase for consistency
                transform(word.begin(), word.end(), word.begin(), ::tolower);
                
                if (!word.empty() && all_of(word.begin(), word.end(), ::isalpha)) {
                    insertResultTrie(word, rank);
                    numLoaded++;
                }
            }
        }
        rank++;
    }

    file.close();
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Trie loaded successfully!" << endl;
    cout << "Size: " << trieImplement.returnSize() << endl;
    cout << "Load time: " << duration.count() << "ms" << endl;
    return true;
}

void Interface::insertResultTrie(string& word, int rank) {
    trieImplement.insert(word, rank);
}

vector<pair<string, int>> Interface::autocorrectTrie(string& wrd) {
    auto start = chrono::high_resolution_clock::now();

    //If word is found, return empty vector 
    if (trieImplement.search(wrd)) {
        return {};
    }
    
    //Get suggestions for misspelled word
    vector<pair<string, int>> res = trieImplement.checkClose(wrd);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    cout << "Trie Result took: " << duration.count() << "ns" << endl;

    return res;
}

bool Interface::searchWordBKTree(string& word) {
    return bkTreeImplement.contains(word);
}

bool Interface::searchWordTrie(string& word) {
    return trieImplement.search(word); //Fixed search() returns bool, not int <=== BIGGEST PROBLEM OH MY GOOOOOD
}