#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cctype>
#include "BKTree.h"
#include "Trie.h"


using namespace std;

string lowercase(string& inpstr) {
    string outstr;
    std::transform(outstr.begin(), outstr.end(), outstr.begin(), ::tolower);
    return outstr;
};


class Interface {
    private:
        BKTree bkTreeImplement;
        Trie trieImplement;

    public:
    //Create some funcion for word regex and extracting words; changing to lower case etc.
    //Initialize the BKTree and the trie here as well and train them on the data set (will be added later)

    //inserting the common word data set into the trees
    void loadBKTree(string& filename);
    void loadTRie(string& filename);

    //inserting into trees
    void insertResultBKTree(string& word);
    void insertResultTrie(string& word);


    //use regex to get words from the textfile
    vector<string> wordExtraction(string& text);


    void basicCLI(); //testing
};