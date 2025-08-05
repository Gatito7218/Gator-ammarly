#include "BKTree.h"


//Node

void BKNode::addChildren(string& inpW, int distance, int rank) {
    children[distance].emplace_back(make_unique<BKNode>(inpW, rank));
}


//BKTree

BKTree::BKTree() : root(nullptr), treeSize(0) {};

BKTree::~BKTree() {};

int BKTree::LevenshteinDistance(string& s1, string& s2) {
    //UTILIZES THE WAGNER-FISCHER ALGORITHM USING BOTTOM-UP DYNAMIC PROGRAMMING
    int m = s1.size();
    int n = s2.size();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 0; i <= m; i++) {
        dp[i][0] = i;
    }
    for (int j = 0; j <= n; j++) {
        dp[0][j] = j;
    }
    int substitutionCost = 0;
    //Using dynamic programming to determine the similarity between the 2 inputted words
    for (int j = 1; j <= n; j++) {
        for (int i = 1; i <= m; i++) {
            if (s1[i-1] == s2[j-1])  { //original algorithm is 1-indexed
                substitutionCost = 0;
            }
            else {
                substitutionCost = 1;
            }

            dp[i][j] = min({dp[i-1][j] + 1, dp[i][j-1] + 1, dp[i-1][j-1] + substitutionCost});
        }
    }
    return dp[m][n];
}

void BKTree::insert(string& inpW, int rank) {
    //we assume that the string is auto set to lower case through the cli

    if (!root) {
        root = make_unique<BKNode>(inpW, rank);
        treeSize++;
        return;
    }

    BKNode* curr = root.get();
    while (true) {
        int distance = LevenshteinDistance(curr->word, inpW);

        if (distance == 0) return; //a distance of 0 means that the words are equivalent, so the word is already in the list so it exits

        auto it = curr->children.find(distance);


        if (it != curr->children.end()) { //in the case that there are multiple children with the same distance (they become stored as vectors)
            bool slot = false;
            for (auto& child : it->second) {
                int d = LevenshteinDistance(child->word, inpW);
                if (d == 0) return; //word exists so don't insert
                curr = child.get();
                slot = true; //a valid child to traverse to is found
                break;
            }
            if (!slot) { //in case children at this distance are duplicates, probably won't happen but its good to have a checker
                curr->addChildren(inpW, distance, rank);
                treeSize++;
                break;
            }
        }

        else {
            curr->addChildren(inpW, distance, rank); //child with a certain distance does not exist so it is created
            treeSize++;
            break;
        }
    }
}

bool BKTree::contains(string& w) {
    //logically very similar to the insert function
    if (!root) return false;

    BKNode* curr = root.get();
    while (curr) {
        int distance = LevenshteinDistance(curr->word, w);
        if (distance == 0) return true;
        auto it = curr->children.find(distance);
        if (it != curr->children.end()) {
            for (auto& child : it->second) {
                curr = child.get();
                break;
            }
        }
        else {
            break;
        }
    }
    return false;
}
//CREDIT GOES TO THE CREATORS OF THE BK-TREE FOR THEIR PSEUDOCODE FOR THE TRIANGLE INEQUALITY
//Realistically a person only makes a typo of up to ~2 letters, so its best to keep maxDist at 2
vector<outputWord> BKTree::search(string& inpW, int maxDist) { //maxDist is the furthest we are willing to go so we don't get word suggestions that are really different
    if (!root) return {};
    

    vector<outputWord> res;
    stack<BKNode*> process;
    process.push(root.get());

    while (!process.empty()) { 
        BKNode* curr = process.top();
        process.pop();
        int distance = LevenshteinDistance(curr->word, inpW);
        if (distance <= maxDist) {
            res.emplace_back(curr->word, distance, curr->rank);
        }

        for (int d = max(1, distance - maxDist); d <= distance + maxDist; d++) { //This is a triangle inequality;
            auto it = curr->children.find(d);
            if (it != curr->children.end()) {
                for (auto& child : it->second) {
                    process.push(child.get());
                }
            }
        }
    }

    sort(res.begin(), res.end(), [](outputWord& a, outputWord& b) {
        if (a.distance != b.distance) return a.distance < b.distance; 
        if (a.rank != b.rank) return a.rank < b.rank; //if 2 words have the same distance use rank from the dataset
        return a.word < b.word;
    });

    if (res.size() > 5) { //caps the number of suggestions
        res.resize(5);
    }

    return res;
}

int BKTree::returnSize() {
    return treeSize;
}