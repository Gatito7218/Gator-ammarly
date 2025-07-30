#include "BKTree.h"
#include <string>


//Node

void BKNode::addChildren(string& inpW, int distance, int rank) {
    children[distance].push_back(make_unique<BKNode>(inpW, rank));
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

void BKTree::insert(string& inpW, int rank) {
    //we assume that the string is auto set to lower case through the cli

    if (!root) {
        root = make_unique<BKNode>(inpW, rank);
        treeSize++;
        return;
    }

    Node* curr = root.get();
    while (true) {
        int distance = LevenshteinDistance(curr->word, inpW);

        if (distance == 0) return;

        auto it = curr->children.find(distance);


        if (it != curr->children.end()) {
            bool slot = false;
            for (auto& child : it->second) {
                int d = LevenshteinDistance(child->word, inpW);
                if (d == 0) return;
                curr = child.get();
                slot = true;
                break;
            }
            if (!slot) {
                curr->addChildren(inpW, distance, rank);
                treeSize++;
                break;
            }
        }

        else {
            curr->addChildren(inpW, distance, rank);
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

vector<outputWord> BKTree::search(string& inpW, int maxDist) {
    if (!root) return {};

    vector<outputWord> res;
    stack<BKNode*> process = {root.get()};

    while (!process.empty()) {
        BKNode* curr = process.top();
        process.pop();
        int distance = LevenshteinDistance(curr->word, inpW);
        if (distance <= maxDist) {
            res.push_back(curr->word, distance, curr->rank);
        }

        for (int d = max(1, distance - maxDist); d <= distance + maxDist; d++) {
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
        if (a.rank != b.rank) return a.rank < b.rank;
        return a.word < b.word;
    });

    if (res.size() > 5) { //don't want too many results
        res.resize(5);
    }
    return res;
}

int BKTree::returnSize() {
    return treeSize;
}
