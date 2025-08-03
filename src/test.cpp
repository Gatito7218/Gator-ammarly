#include "BKTree.h"
#include "interface.h"




int main() {
    Interface CLI;

    cout << "Basic testing" << endl;

    string filename = "C:/Users/djbik/OneDrive/Desktop/Gator-ammarly/unigram_freq.csv";
    CLI.loadBKTree(filename);

    bool exit = false;

    while (true) {
        string word;
        cout << "Enter a word: ";
        cin >> word;

        autocorResult result = CLI.autocorrectBKTree(word, 2);

        cout << "Problem word: " << result.originalWord << endl;
        cout << "Suggestions: " << "word/rank/distance" << endl;
        auto vec = result.suggestions;
        for (int i = 0; i < vec.size(); i++) {
            cout << vec[i].word << " " << vec[i].rank << " " << vec[i].distance << endl;
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