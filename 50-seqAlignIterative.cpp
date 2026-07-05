
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int minDistance(string word1, string word2);
void reconstructSolution(vector<vector<int>> &memo,
                         string &w1, string &w2);

int main()
{
    //Leetcode 72 - Edit Distance
    // Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.

    // You have the following three operations permitted on a word:

    // Insert a character
    // Delete a character
    // Replace a character

    // Example 1:

    // Input: word1 = "horse", word2 = "ros"
    // Output: 3
    // Explanation:
    // horse -> rorse (replace 'h' with 'r')
    // rorse -> rose (remove 'r')
    // rose -> ros (remove 'e')
    // Example 2:

    // Input: word1 = "intention", word2 = "execution"
    // Output: 5
    // Explanation:
    // intention -> inention (remove 't')
    // inention -> enention (replace 'i' with 'e')
    // enention -> exention (replace 'n' with 'x')
    // exention -> exection (replace 'n' with 'c')
    // exection -> execution (insert 'u')

    // Constraints:

    // 0 <= word1.length, word2.length <= 500
    // word1 and word2 consist of lowercase English letters.

    string s1;
    string s2;

    cin >> s1 >> s2;

    int minOp = minDistance(s1, s2);
    cout << "Min operations needed " << minOp << endl;
    return 0;
}

int minDistance(string word1, string word2)
{

    //iterative + reconstruction

    int n = word1.length();
    int m = word2.length();

    vector<vector<int>> memo(n + 1, vector<int>(m + 1, -1));

    //base cases
    //both empty case

    for (int j = 0; j <= m; j++)
    {
        //all inserts
        memo[n][j] = m - j;
    }

    for (int i = 0; i <= n; i++)
    {
        //all deletes
        memo[i][m] = n - i;
    }

    for (int i = n - 1; i >= 0; i--)
    {

        for (int j = m - 1; j >= 0; j--)
        {
            int a = 1 + memo[i + 1][j];                                  //delete
            int b = 1 + memo[i][j + 1];                                  //insert
            int c = (word1[i] == word2[j] ? 0 : 1) + memo[i + 1][j + 1]; //matching
            memo[i][j] = min(min(a, b), c);
        }
    }

    reconstructSolution(memo, word1, word2);

    return memo[0][0];
}

void reconstructSolution(vector<vector<int>> &memo,
                         string &w1, string &w2)
{

    int n = w1.length();
    int m = w2.length();

    int i = 0;
    int j = 0;

    while (i < n && j < m)
    {
        int val = memo[i][j];

        int del = memo[i + 1][j];
        int ins = memo[i][j + 1];
        int repl = memo[i + 1][j + 1];

        if (val == (1 + del))
        {
            cout << "delete " << w1[i] << endl;
            i += 1;
        }
        else if (val == (1 + ins))
        {
            cout << "insert " << w2[j] << endl;
            j += 1;
        }
        else if (w1[i] == w2[j])
        {
            cout << "match " << w1[i] << endl;
            i += 1;
            j += 1;
        }
        else
        {
            cout << "replace " << w1[i] << " with " << w2[j] << endl;
            i += 1;
            j += 1;
        }
    }

    //base case handling
    if (memo[i][j] != 0)
    {

        if (i == n)
        {

            for (int k = j; k < m; k++)
            {
                cout << "insert " << w2[k] << endl;
            }
        }
        else
        {
            for (int k = i; k < n; k++)
            {
                cout << "delete " << w1[k] << endl;
            }
        }
    }
}
