#include "BKTree.h"
#include "interface.h"
#include "Trie.h"
#include "ui.h"


int main() {
    Interface CLI;

    string wordFile = "C:/Users/djbik/OneDrive/Desktop/Gator-ammarly/Gator-ammarly/unigram_freq.csv";
    CLI.loadBKTree(wordFile);
    CLI.loadTrie(wordFile);

    bool exit = true;

    string uncorrectedFile;

    cout << "Insert file name: ";
    cin >> uncorrectedFile;
    
    ifstream file(uncorrectedFile);
    cin.ignore();

    if (!file.is_open()) {

        cout << "File did not load properly" << endl;
        return 0;
    }
    else {

        vector<vector<pair<string, bool>>> tokenizedLines;

        string line;

        while (getline(file, line)) {
            tokenizedLines.push_back(tokenize(line));
        }

        for (int i = 0; i < tokenizedLines.size(); i++) {

            vector<pair<string, bool>> tokens = tokenizedLines[i];

            vector<int> replaceIndexes;

            for (int j = 0; j < tokens.size(); j++) {

                //const auto& [word, isWord] = tokens[i];
                string word = tokens[j].first;
                bool isWord = tokens[j].second;
                
                if (!isWord) {

                    continue;
                }

                string noSymbolWord = removeSymbols(word);

                if (!CLI.searchWordTrie(noSymbolWord) && !CLI.searchWordBKTree(word)) {
                    replaceIndexes.push_back(j);
                }

            }

            if (replaceIndexes.empty()) {

                continue;
            }

            cout << "\nLine " << (i + 1) << ":" << endl;

            for (int j = 0; j < tokens.size(); j++) {
                
                if (find(replaceIndexes.begin(), replaceIndexes.end(), j) != replaceIndexes.end()) {
                    
                    cout << underline(tokens[j].first);

                } else {

                    cout << tokens[j].first;
                }
            }

            cout << endl;

            for (int j : replaceIndexes) {
                string word = tokens[j].first;
                cout << "\nProblem word: " << word << endl;

                autocorResult resultBK = CLI.autocorrectBKTree(word, 2);
                vector<pair<string, int>> resultTrie = CLI.autocorrectTrie(word);

                if (!resultBK.suggestions.empty()) {
                    cout << "BKTree suggestions" << endl;
                    cout << "Suggestions: " << "#. word/rank/distance" << endl;

                    auto vec = resultBK.suggestions;

                    for (int k = 0; k < vec.size(); k++) {
                        cout << "b" << (k + 1) << ". " << vec[k].word << " " << vec[k].rank << " " << vec[k].distance << endl;
                    }
                }

                if (!resultTrie.empty()) {

                    cout << "Trie suggestions" << endl;
                    cout << "Suggestions: " << "#. word/rank" << endl;

                    for (int k = 0; k < resultTrie.size(); k++) {
                        cout << "t" << (k + 1) <<  resultTrie[k].first << " " << resultTrie[k].second << endl;
                    }
                }

                cout << "Enter replacement letter/number (e.g. t1 or b4) or 'ignore': ";
                string input;
                getline(cin, input);

                if (input == "ignore") {
                    continue;
                } else if (input.size() == 2 && isdigit(input[1])) {

                    int numChoice = input[1] - '1';

                    if (input[0] == 't' && numChoice >= 0 && numChoice < resultTrie.size()) {

                        cout << "Changed " << word << " into " << resultTrie[numChoice].first << endl;
                        word = resultTrie[numChoice].first;
                        
                    } else if (input[0] == 'b' && numChoice >= 0 && numChoice < resultBK.suggestions.size()) {

                        cout << "Changed " << word << " into " << resultBK.suggestions[numChoice].word << endl;
                        word = resultBK.suggestions[numChoice].word;

                    } else {

                        cout << "Invalid input, skipping." << endl;
                    }

                } else {

                    cout << "Invalid input, skipping." << endl;
                }

            }

            cout << "\nContinue to next line? (y/n): ";
            string answer;
            getline(cin, answer);
            if (answer !=  "y") {
                break;
            }
        }
        
        file.close();

        string correctedFile = uncorrectedFile.substr(0, uncorrectedFile.find_last_of('.')) + "_updated.txt";
        ofstream newFile(correctedFile);

        if (!newFile.is_open()) {
            cout << "Failed to update file for some reason." << endl;
            return -1;
        }

        for (const auto& line : tokenizedLines) {

            for (const auto& [token, useless] : line) {
                newFile << token;
            }
            newFile << '\n';

        }

        cout << "Updated file to" << correctedFile << ", have a good day!" << endl;

    }

    return 0;
}