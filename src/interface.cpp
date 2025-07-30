#include "interface.h"

//BKTREE CLI FUNCTIONS
void Interface::loadBKTree(string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        cout << "Did not load properly";
    }

    auto start = chrono::high_resolution_clock::now();
    vector<pair<string, int>> words;
    string line;
    int rank = 1;
    while (getline(file, line)) {
        if (!line.empty()) {
            size_t comma = line.find(','); //csv is seperated by single comma
            if (comma != string::npos) {
                string word = line.substr(0, comma);
                insertResultBKTree(word, rank);
            }
            rank++;
        }
    }

    file.close();
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "BKTree loaded";
    cout << "Size: " << bkTreeImplement.returnSize() << endl;
    cout << "Load length" << duration.count() << "ms" << endl;
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