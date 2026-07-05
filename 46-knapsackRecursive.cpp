
#include <iostream>
#include <vector>

using namespace std;

int knapsack(int W, vector<int> &val, vector<int> &wt);
int dpKnap(int i, int c, vector<int> &val, vector<int> &wt,
           vector<vector<int>> &memo, vector<vector<int>> &choices);

vector<int> reconstructSolution(vector<vector<int>> &choices, vector<int> &wt);

int main()
{
    //geeks for geeks

    //     0 - 1 Knapsack Problem
    // Given two arrays, val[] and wt[], where each element represents the value and weight of an item respectively, and an integer W representing the maximum capacity of the knapsack (the total weight it can hold).

    // The task is to put the items into the knapsack such that the total value obtained is maximum without exceeding the capacity W.

    // Note: You can either include an item completely or exclude it entirely — fractional selection of items is not allowed. Each item is available only once.

    // Examples :

    // Input: W = 4, val[] = [1, 2, 3], wt[] = [4, 5, 1]
    // Output: 3
    // Explanation: Choose the last item, which weighs 1 unit and has a value of 3.
    // Input: W = 3, val[] = [1, 2, 3], wt[] = [4, 5, 6]
    // Output: 0
    // Explanation: Every item has a weight exceeding the knapsack's capacity (3).
    // Input: W = 5, val[] = [10, 40, 30, 50], wt[] = [5, 4, 2, 3]
    // Output: 80
    // Explanation: Choose the third item (value 30, weight 2) and the last item (value 50, weight 3) for a total value of 80.
    // Constraints:
    // 1 ≤ val.size() = wt.size() ≤ 103
    // 1 ≤ W ≤ 103
    // 1 ≤ val[i] ≤ 103
    // 1 ≤ wt[i] ≤ 103

    int n, w;
    cin >> n >> w;

    vector<int> val(n);
    vector<int> wt(n);

    for (int i = 0; i < n; i++)
    {
        cin >> val[i];
    }

    for (int i = 0; i < n; i++)
    {
        cin >> wt[i];
    }

    int ans = knapsack(w, val, wt);

    cout << "Max value " << ans << endl;

    return 0;
}

int knapsack(int W, vector<int> &val, vector<int> &wt)
{
    // code here

    //recursion + reconstruction
    int n = val.size();

    vector<vector<int>> memo(n, vector<int>(W + 1, -1));
    vector<vector<int>> choices(n, vector<int>(W + 1, -1));

    int optimalVal = dpKnap(n - 1, W, val, wt, memo, choices);

    vector<int> optimalSolution = reconstructSolution(choices, wt);

    cout << "choices ";

    for (int x : optimalSolution)
    {
        cout << x << " ";
    }
    cout << endl;
    return optimalVal;
}

int dpKnap(int i, int c, vector<int> &val, vector<int> &wt,
           vector<vector<int>> &memo, vector<vector<int>> &choices)
{
    //base cases 1 and 2
    if (i < 0)
    {
        return 0;
    }

    else if (memo[i][c] != -1)
    {
        return memo[i][c];
    }

    int s = wt[i];

    if (s > c)
    {

        //memoization
        memo[i][c] = dpKnap(i - 1, c, val, wt, memo, choices); //not choose i
        choices[i][c] = 1;
    }

    else
    {

        int a = dpKnap(i - 1, c, val, wt, memo, choices);              //not choose i
        int b = val[i] + dpKnap(i - 1, c - s, val, wt, memo, choices); //choose i

        if (a >= b)
        {
            //memoization
            memo[i][c] = a;
            choices[i][c] = 1;
        }
        else
        {
            //memoization
            memo[i][c] = b;
            choices[i][c] = 2;
        }
    }

    return memo[i][c];
}

vector<int> reconstructSolution(vector<vector<int>> &choices, vector<int> &wt)
{
    int n = choices.size();
    int m = choices[0].size();

    vector<int> solution;

    int i = n - 1;
    int j = m - 1;

    while (i >= 0)
    {

        if (choices[i][j] == 2)
        {
            solution.push_back(i);

            j = j - wt[i];
            i -= 1;
        }
        else
        {
            i -= 1;
        }
    }

    return solution;
}
