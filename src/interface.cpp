#include "interface.h"

//BKTREE CLI FUNCTIONS
void Interface::loadBKTree(string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        cout << "BK Tree did not load properly" << endl;
    }

    auto start = chrono::high_resolution_clock::now();
    vector<pair<string, int>> words;
    string line;
    int rank = 1;
    int numLoaded = 0;
    while (getline(file, line) && numLoaded <= 300000) {
        if (!line.empty()) {
            size_t comma = line.find(','); //csv is seperated by single comma
            if (comma != string::npos) {
                string word = line.substr(0, comma);
                insertResultBKTree(word, rank);
            }
            rank++;
            numLoaded++;
        }
    }

    file.close();
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "BKTree loaded";
    cout << "Size: " << bkTreeImplement.returnSize() << endl;
    cout << "Load time: " << duration.count() << "ms" << endl;
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
    cout << "Result took: " << duration.count() << "ms" << endl;
    return res;
}

void Interface::basicCLI() {
    //probably don't need I'll just do everything in the test file
}


// Code adapted from earlier loadBKTree, credits to David Miranda
void Interface::loadTrie(string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        cout << "Trie did not load properly" << endl;
    }

    auto start = chrono::high_resolution_clock::now();
    vector<pair<string, int>> words;
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            size_t comma = line.find(','); //csv is seperated by single comma
            if (comma != string::npos) {
                string word = line.substr(0, comma);
                trieImplement.insert(word);
            }
        }
    }

    file.close();
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Trie loaded";
    cout << "Size: " << trieImplement.returnSize() << endl;
    cout << "Load length: " << duration.count() << "ms" << endl;
}