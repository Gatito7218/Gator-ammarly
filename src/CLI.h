#include "BKTree.h"
#include "Trie.h"
#include "ui.h"
#include "interface.h"
#include <iostream>
#include <limits>

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
            
            cin >> data;
            if (data == "default") {
                cout << "Using default" << endl;
                data = dataFile;
            }
            //calling these functions will return the load time of the trees
            bool bkLoaded = interface.loadBKTree(data);
            bool trieLoaded = interface.loadTrie(data);

            if (bkLoaded && trieLoaded) {
                alrLoaded = true;
                cout << "Trees Loaded!" << endl;
            }
            else {
                cout << "Error in tree loading" << endl;
            }

            cout << "Press enter to continue" << endl;
            cin.ignore();
            cin.get();
        }

        void checkIndividualWrd() {
            if (!alrLoaded) {
                cout << "Please load the trees first!" << endl;
                cout << "Press enter to continue" << endl;
                cin.ignore();
                cin.get();
                return;
            }

            cout << "Type in a word to check!" << endl;

            string word;
            while (true) {
                cout << "Enter word (type 123 to go back to menu): " << endl;
                cin >> word;

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
                    cout << "Trie suggestions: " << endl;
                    for (int i = 0; i < resultTrie.size(); i++) {
                        cout << " " << (i + 1) << ". " << resultTrie[i].first << ". rank: " << resultTrie[i].second << endl;
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

            cout << "Enter file path to check: ";
            string filename;
            cin.ignore();
            getline(cin, filename);

            if (filename.empty()) {
                cout << "No file typed in erm" << endl;
                cout << "Press enter to continue" << endl;
                cin.get();
                return;
            }

            ifstream file(filename);
            if (!file.is_open()) {
                cout << "Error: File could not open" << endl;
                cout << "Press enter to continue" << endl;
                cin.get();
                return;
            }

            vector<vector<pair<string, bool>>> tokenizedLines;
            string line;

            cout << "Reading file..." << endl;
            while (getline(file, line)) {
                tokenizedLines.push_back(tokenize(line));
            }
            file.close();
            
            //see if a line has errors
            for (int i = 0; i < tokenizedLines.size(); i++) {
                auto& tokens = tokenizedLines[i];
                bool hasError = false;

                cout << "Line " << (i + 1) << ": ";

                for (int j = 0; j < tokens.size(); j++) {
                    string& word = tokens[j].first;
                    bool isWord = tokens[j].second;

                    bool isCorrect = true;
                    if (isWord) {
                        string firstClean = removeSymbols(word);
                        string cleanWord = lowercase(firstClean);

                        if (!cleanWord.empty()) {
                            isCorrect = interface.searchWordBKTree(cleanWord) || interface.searchWordTrie(cleanWord);
                            if (!isCorrect) hasError = true;
                        }
                    }

                    cout << (isCorrect ? word : underline(word));
                }
                cout << endl;

                if (!hasError) {
                    cout << "No errors on this line" << endl;
                    continue;
                }

                cout << "Processing misspelled words:" << endl;
                
                //process misspelled words
                for (int j = 0; j < tokens.size(); j++) {
                    if (!tokens[j].second) continue;

                    string firstClean = removeSymbols(tokens[j].first);
                    string cleanWord = lowercase(firstClean);

                    if (cleanWord.empty()) continue;

                    cout << "\nMisspelled word: " << tokens[j].first << endl;

                    autocorResult resultBK = interface.autocorrectBKTree(cleanWord, 2); //don't want more than a distance of 2
                    vector<pair<string, int>> resultTrie = interface.autocorrectTrie(cleanWord);

                    bool sugg = false;
                    if (!resultBK.suggestions.empty()) {
                        cout << "BK-Tree suggestions: word/rank/distance" << endl;
                        auto vec = resultBK.suggestions;
                        for (int k = 0; k < vec.size(); k++) {
                            cout << " b" << (k + 1) << ". " << vec[k].word << " " << vec[k].distance << " " << vec[k].rank << endl;
                        }
                        sugg = true;
                    }
                    if (!resultTrie.empty()) {
                        cout << "Trie suggestions: " << endl;
                        for (int k = 0; k < resultTrie.size(); k++) {
                            cout << " t" << (k + 1) << ". " << resultTrie[k].first << " "<< resultTrie[k].second << endl;
                        }
                        sugg = true;
                    }

                    if (!sugg) {
                        cout << "No suggestion found." << endl;
                        continue;
                    }

                    cout << "Enter replacement letter/number (e.g. t1 or b4) or 'ignore': ";
                    string input;
                    cin >> input;

                    if (input == "ignore") {
                        continue;
                    } else if (input.size() == 2 && isdigit(input[1])) {

                        int numChoice = input[1] - '1';

                        if (input[0] == 't' && numChoice >= 0 && numChoice < resultTrie.size()) {

                                cout << "Changed " << tokens[j].first << " into " << resultTrie[numChoice].first << endl;
                                tokens[j].first = resultTrie[numChoice].first;
                        
                        } else if (input[0] == 'b' && numChoice >= 0 && numChoice < resultBK.suggestions.size()) {

                                cout << "Changed " << tokens[j].first << " into " << resultBK.suggestions[numChoice].word << endl;
                                tokens[j].first = resultBK.suggestions[numChoice].word;

                        } else {

                                cout << "Invalid input, skipping." << endl;
                            }

                    } else {

                            cout << "Invalid input, skipping." << endl;
                    }
                }

                tokenizedLines[i] = tokens;
                cout << "\nContinue to next line? (y/n): ";
                string answer;
                cin >> answer;
                if (answer != "y" && answer != "Y") break;
            }

            
            //saving the correct file
            string correctedFile = filename.substr(0, filename.find_last_of('.')) + "_corrected.txt";
            ofstream newFile(correctedFile);

            if (newFile.is_open()) {
                for (const auto& line : tokenizedLines) {
                    for (const auto& [token, isWord] : line) {
                        newFile << token;
                    }
                    newFile << '\n';
                }
                newFile.close();
                cout << "\nCorrected file saves as: " << correctedFile << endl;
            }
            else {
                cout << "Error: Could not create corrected file." << endl;
            }

            cout << "Press Enter to continue";
            cin.ignore();
            cin.get();
        }


    public:
        CLI() {};

        void mainLoop() {
            int choice;

            while (true) {
                printHeader();
                printMenu();

                if (!(cin >> choice)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
                        checkTextFile();
                        break;
                    case 4:
                        cout << "Bye Bye!" << endl;
                        return;
                    default:
                        cout << "Invalid input, please use a number from 1-4" << endl;
                        cout << "Press enter to continue." << endl;
                        cin.ignore();
                        cin.get();
                }
            }
        }

};