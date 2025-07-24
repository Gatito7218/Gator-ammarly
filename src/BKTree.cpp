#include "BKTree.h"


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
