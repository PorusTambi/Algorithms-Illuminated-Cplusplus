
#include <iostream>
#include <vector>

using namespace std;

int knapsack(int W, vector<int> &val, vector<int> &wt);
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

    //iterative + reconstruction
    int n = val.size();
    int m = W + 1;

    vector<vector<int>> memo(n, vector<int>(m, -1));
    vector<vector<int>> choices(n, vector<int>(m, -1));

    //base case i=0, filling frst row
    int weight = wt[0];
    int value = val[0];
    for (int j = 0; j < m; j++)
    {

        if (weight <= j)
        {
            memo[0][j] = value;
            choices[0][j] = 2;
        }
        else
        {
            memo[0][j] = 0;
            choices[0][j] = 1;
        }
    }

    for (int i = 1; i < n; i++)
    {

        for (int j = 0; j < m; j++)
        {
            weight = wt[i];
            value = val[i];

            if (weight > j)
            {
                //not choose i
                memo[i][j] = memo[i - 1][j];
                choices[i][j] = 1;
            }
            else
            {

                int a = memo[i - 1][j];                  //not choose i
                int b = value + memo[i - 1][j - weight]; //choose i

                if (a >= b)
                {
                    memo[i][j] = a;
                    choices[i][j] = 1;
                }
                else
                {
                    memo[i][j] = b;
                    choices[i][j] = 2;
                }
            }
        }
    }

    vector<int> optimalSolution = reconstructSolution(choices, wt);

    cout << "choices ";
    for (int x : optimalSolution)
    {
        cout << x << " ";
    }
    cout << endl;

    return memo[n - 1][m - 1];
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
