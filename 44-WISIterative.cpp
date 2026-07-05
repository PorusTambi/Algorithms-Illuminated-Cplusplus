#include <iostream>
#include <vector>

using namespace std;

int rob(vector<int> &nums);
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

    //iterative and reconstruction

    int n = nums.size();
    vector<int> ans(n, -1);
    ans[0] = nums[0];

    vector<int> choices(n, -1);
    //1 if 1st subproblem n-1 selected , 2 if n-2 subproblem selected
    choices[0] = 2;

    for (int i = 1; i < n; i++)
    {

        int x = ans[i - 1];
        int y = nums[i] + ((i - 2) >= 0 ? ans[i - 2] : 0);

        if (x >= y)
        {
            ans[i] = x;
            choices[i] = 1;
        }
        else
        {
            ans[i] = y;
            choices[i] = 2;
        }
    }

    vector<int> optimalSolution = reconstructSolution(choices);

    cout << "choices ";
    for (int w : optimalSolution)
    {
        cout << w << " ";
    }
    cout << endl;

    return ans[n - 1];
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
