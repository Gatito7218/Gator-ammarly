#include "BKTree.h"
#include <string>


//Node

void Node::addChildren(string& inpW, int distance) {
    children[distance] = make_unique<Node>(inpW);
}


//BKTree

BKTree::BKTree() : root(nullptr), treeSize(0) {};

BKTree::~BKTree() {};

int BKTree::LevenshteinDistance(string& s1, string& s2) {
    //UTILIZES THE WAGNER-FISCHER ALGORITHM USING BOTTOM-UP DYNAMIC PROGRAMMING
    int m = s1.size();
    int n = s2.size();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 0; i < m; i++) {
        dp[i][0] = i;
    }
    for (int j = 0; j < n; j++) {
        dp[0][j] = j;
    }
    int substitutionCost = 0;
    for (int j = 1; j < n; j++) {
        for (int i = 1; i < m; i++) {
            if (s1[i-1] == s2[j-1])  { //original algorithm is 1-indexed
                substitutionCost = 0;
            }
            else {
                substitutionCost = 1;
            }

            dp[i][j] = min(dp[i-1][j] + 1, dp[i][j-1] + 1, dp[i-1][j-1] + substitutionCost);
        }
    }
    return dp[m][n];
}

void BKTree::insert(string& inpW) {
    //we assume that the string is auto set to lower case through the cli

    if (!root) {
        root = make_unique<Node>(inpW);
        treeSize++;
        return;
    }

    Node* curr = root.get();
    while (curr) {
        int distance = LevenshteinDistance(curr->word, inpW);
        if (distance == 0) return;
        auto it = curr->children.find(distance);
        if (it != curr->children.end()) {
            curr = it->second.get();
        }
        else {
            curr->addChildren(inpW, distance);
            treeSize++;
            break;
        }
    }
}

bool BKTree::contains(string& w) {
    //logically very similar to the insert function
    if (!root) return false;

    Node* curr = root.get();
    while (curr) {
        int distance = LevenshteinDistance(curr->word, w);
        if (distance == 0) return true;
        auto it = curr->children.find(distance);
        if (it != curr->children.end()) {
            curr = it->second.get();
        }
        else {
            break;
        }
    }
    return false;
}

vector<string> BKTree::search(string& inpW, int maxDist) {
    if (!root) return {};

    vector<string> res;
    stack<Node*> process = {root.get()};

    while (!process.empty()) {
        Node* curr = process.top();
        process.pop();
        int distance = LevenshteinDistance(curr->word, inpW);
        if (distance <= maxDist) {
            res.push_back(curr->word);
        }

        for (int d = max(1, distance - maxDist); d <= distance + maxDist; d++) {
            auto it = curr->children.find(d);
            if (it != curr->children.end()) {
                process.push(it->second.get());
            }
        }
    }

    if (res.size() > 5) { //don't want too many results
        res.resize(5);
    }
    return res;
}

int BKTree::returnSize() {
    return treeSize;
}
