#include "BKTree.h"
#include "Trie.h"
#include "ui.h"
#include "interface.h"
#include <iostream>

class CLI {
    private:
        Interface interface;
        string dataFile = "C:/Users/djbik/OneDrive/Desktop/Gator-ammarly/Gator-ammarly/unigram_freq.csv";
        bool alrLoaded = false; //if the data is already loaded into the trees (so it doesn't do it again)
        void printHeader() {
            cout << "========================================" << endl;
            cout << "              GATOR-AMMARLY             " << endl;
            cout << "       BK-Tree vs Trie Performance      " << endl;
            cout << "========================================" << endl;
        };
        void printMenu() {
            cout << "Choose an option:" << endl;
            cout << "1. Load Dictionary" << endl;
            cout << "2. Check individual words" << endl;
            cout << "3. Load text file" << endl;
            cout << "4. Exit" << endl;
            cout << "Enter choice: " << endl;
        }

        void loadData() {
            if (alrLoaded) {
                cout << "Data is already loaded!" << endl;
                return;
            }
            //by defualt we should just use the file already put in here but ill still give an option to manually type it in
            string data;

            cout << "Enter the filepath: ";
            getline(cin, data);
            if (dataFile2.empty()) {
                cout << "Using default" << endl;
                data = dataFile;
            }

            interface.loadBKTree(data);
            interface.loadTrie(data);

            alrLoaded = true;

            cout << "Trees loaded! Press enter to continue" << endl;
            cin.get();
        }

        void checkIndividualWrd() {
            if (!alrLoaded) {
                cout << "Please load the trees first!" << endl;
                cout << "Press enter to continue" << endl;
                cin.get();
                return;
            }

            cout << "Type in a word to check!" << endl;

            string word;
            while (true) {
                cout << "Enter word (type 123 to go back to menu): " << endl;
                getline(cin, word);

                if (word == "123") break;
                if (word.empty()) continue;

                string firstclean = removeSymbols(word);
                string cleanString = lowercase(firstclean);

                bool inBKTree = interface.searchWordBKTree(cleanString); 
                bool inTrie = interface.searchWordTrie(cleanString);

                if (inBKTree && inTrie) {
                    cout << "Word found in dictionary!" << endl;
                }
                else {
                    cout << "Word not found in dictionary! :(" << endl;
                }
                //calling these functions also returns the lookup speed
                autocorResult resultBK = interface.autocorrectBKTree(cleanString, 2); //don't want more than a distance of 2
                vector<pair<string, int>> resultTrie = interface.autocorrectTrie(cleanString);

                if (!resultBK.suggestions.empty()) {
                    cout << "BK-Tree suggestions: word/rank/distance" << endl;
                    auto vec = resultBK.suggestions;
                    for (int i = 0; i < vec.size(); i++) {
                        cout << vec[i].word << " " << vec[i].rank << " " << vec[i].distance << endl;
                    }
                }
                else {cout << "No suggestions found for BK-Tree" << endl;};
                if (!resultTrie.empty()) {
                    cout << "Trie suggestions: ";
                    for (int i = 0; i < resultTrie.size(); i++) {
                        cout << " " << (i + 1) << ". " << resultTrie[i].first << "rank: " << resultTrie[i].second << endl;
                    }
                }
                else { cout << "No suggestions found for Trie" << endl;};
            }

        }

        void checkTextFile() {
            if (!alrLoaded) {
                cout << "Please load the trees first!" << endl;
                cout << "Press enter to continue" << endl;
                cin.get();
                return;
            }

            
        }


    public:
        CLI() {};

        void mainLoop() {
            int choice;

            while (true) {
                printHeader();
                printMenu();

                if (!(cin >> choice)) {
                    cout << "Invalid input, please enter a numeric value." << endl;
                    cout << "Press enter to continue." << endl;
                    cin.get();
                    continue;  
                }


                switch (choice) {
                    case 1:
                        loadData();
                        break;
                    case 2:
                        checkIndividualWrd();
                        break;
                    case 3:

                    case 4:
                        cout << "Bye Bye!" << endl;
                        return;
                    default:
                        cout << "Invalid input, please use a number from 1-4" << endl;
                        cout << "Press enter to continue." << endl;
                        cin.get();
                }
            }
        }

};