#include <iostream>
#include <vector>

using namespace std;

int rob(vector<int> &nums);
int dpRob(vector<int> &a, int i, vector<int> &memo, vector<int> &choices);
vector<int> reconstructSolution(vector<int> &choices);

int main()
{
    //leetcode 198 House robber exact similar to WIS
    //     You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security systems connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

    // Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.

    //     Example 1:

    // Input: nums = [1,2,3,1]
    // Output: 4
    // Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
    // Total amount you can rob = 1 + 3 = 4.
    // Example 2:

    // Input: nums = [2,7,9,3,1]
    // Output: 12
    // Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
    // Total amount you can rob = 2 + 9 + 1 = 12.

    // Constraints:

    //     1 <= nums.length <= 100 0 <= nums[i] <= 400

    int n;
    cin >> n;

    vector<int> nums(n);

    for (int i = 0; i < n; i++)
    {

        cin >> nums[i];
    }

    int ans = rob(nums);

    cout << "Max money robbed " << ans << endl;

    return 0;
}

int rob(vector<int> &nums)
{

    //recursion + reconstruction
    int n = nums.size();

    vector<int> memo(n, -1);
    memo[0] = nums[0];

    //to reconstruct solution
    vector<int> choices(n, -1);
    //1 means 1st subproblem optimal , 2 means 2nd subproblem
    choices[0] = 2;

    int optimalVal = dpRob(nums, n - 1, memo, choices);

    vector<int> optimalSolution = reconstructSolution(choices);

    cout << "choices ";
    for (int x : optimalSolution)
    {
        cout << x << " ";
    }
    cout << endl;

    return optimalVal;
}

int dpRob(vector<int> &a, int i, vector<int> &memo, vector<int> &choices)
{

    if (i < 0)
    {
        return 0;
    }

    else if (memo[i] != -1)
    {
        //early return
        return memo[i];
    }

    int x = dpRob(a, i - 1, memo, choices);        //not choose a[i]
    int y = a[i] + dpRob(a, i - 2, memo, choices); //choose a[i]

    if (x >= y)
    {
        //memoization
        memo[i] = x;
        choices[i] = 1;
    }
    else
    {
        //memoization
        memo[i] = y;
        choices[i] = 2;
    }

    return memo[i];
}

vector<int> reconstructSolution(vector<int> &choices)
{
    int n = choices.size();

    int i = n - 1;

    vector<int> solution;

    while (i >= 0)
    {

        if (choices[i] == 1)
        {
            i -= 1;
        }
        else
        {
            solution.push_back(i);
            i -= 2;
        }
    }

    return solution;
}