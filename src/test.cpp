#include "BKTree.h"
#include "interface.h"
#include "Trie.h"

int main() {
    Interface CLI;

    cout << "Basic testing" << endl;

    string filename = "";
    string test = "datecting";
    CLI.loadBKTree(filename);
    CLI.loadTrie(filename);

    autocorResult result = CLI.autocorrectBKTree(test, 3);
    
    cout << "Problem word: " << result.originalWord << endl;
    cout << "Suggestions: " << "word/rank/distance" << endl;
    auto vec = result.suggestions;
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i].word << " " << vec[i].rank << " " << vec[i].distance << endl;;
    }
}