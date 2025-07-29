#include "BKTree.h"
#include "Trie.h"
#include "interface.h"




int main() {
    Interface CLI;

    cout << "Basic testing" << endl;

    string filename = "";
    string test = "datecting";
    CLI.loadBKTree(filename);

    autocorResult result = CLI.autocorrectBKTree(test, 3);
    
    cout << "Problem word: " << result.originalWord;
    cout << "Suggestions" << "word/rank/distance";
    auto vec = result.suggestions;
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i].word << " " << vec[i].rank << " " << vec[i].distance;
    }


}