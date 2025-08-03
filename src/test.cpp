#include "BKTree.h"
#include "interface.h"
#include "Trie.h"

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
        vector<string> resultTrie = CLI.autocorrectTrie(word);


        cout << "Problem word: " << resultBK.originalWord << endl;
        cout << "BKTree suggestions" << endl;
        cout << "Suggestions: " << "word/rank/distance" << endl;
        auto vec = resultBK.suggestions;
        for (int i = 0; i < vec.size(); i++) {
            cout << vec[i].word << " " << vec[i].rank << " " << vec[i].distance << endl;
        }

        cout << "Trie suggestions" << endl;
        int rnk = 1;
        for (int i = 0; i < resultTrie.size(); i++) {
            cout << rnk << ". " << resultTrie[i] << endl;
            rnk++;
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