
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

    //most optimal space and time

    int n = word1.length();
    int m = word2.length();

    vector<int> prevRow(m + 1, 0);
    vector<int> currRow(m + 1, 0);

    //base cases
    for (int j = 0; j <= m; j++)
    {
        //all inserts
        prevRow[j] = m - j;
    }

    for (int i = n - 1; i >= 0; i--)
    {

        currRow[m] = n - i;

        for (int j = m - 1; j >= 0; j--)
        {

            int ins = 1 + currRow[j + 1];
            int del = 1 + prevRow[j];
            int repl = (word1[i] == word2[j] ? 0 : 1) + prevRow[j + 1];

            currRow[j] = min(min(ins, del), repl);
        }

        swap(prevRow, currRow);
    }

    return prevRow[0];
}
