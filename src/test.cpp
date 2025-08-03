#include "BKTree.h"
#include "interface.h"
#include "Trie.h"

/* This is just so i can test cus my c++ is weird.
#include "BKTree.cpp"
#include "interface.cpp"
//*/

int main() {
    Interface CLI;

    cout << "Basic testing" << endl;

    string filename = "";
    CLI.loadBKTree(filename);
    CLI.loadTrie(filename);

    bool exit = false;

    while (true) {
        string word;
        cout << "Enter a word: ";
        cin >> word;

        autocorResult resultBK = CLI.autocorrectBKTree(word, 2);
        vector<pair<string, int>> resultTrie = CLI.autocorrectTrie(word);


        cout << "Problem word: " << resultBK.originalWord << endl;
        cout << "BKTree suggestions" << endl;
        cout << "Suggestions: " << "word/rank/distance" << endl;
        auto vec = resultBK.suggestions;
        for (int i = 0; i < vec.size(); i++) {
            cout << vec[i].word << " " << vec[i].rank << " " << vec[i].distance << endl;
        }

        cout << "Trie suggestions" << endl;
        for (int i = 0; i < resultTrie.size(); i++) {
            cout << resultTrie[i].first << " " << resultTrie[i].second << endl;
        }
        string option;
        cout << "continue?" << endl;
        cout << "1. yes" << " 2. no ";
        cin >> option;
        if (option == "2") {
            break;
        }
    }

    return 0;
}