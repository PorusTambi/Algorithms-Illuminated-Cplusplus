#include <iostream>
#include <vector>
using namespace std;

int searchInsert(vector<int> &nums, int target);
int getCountSmallerEqual(vector<int> &a, int val);

int main()
{

    //     Given a sorted array of integers and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

    // You must write an algorithm with O(log n) runtime complexity.

    // Example 1:

    // Input: nums = [1,3,5,6], target = 5
    // Output: 2

    // Example 2:

    // Input: nums = [1,3,5,6], target = 2
    // Output: 1

    // Example 3:

    // Input: nums = [1,3,5,6], target = 7
    // Output: 4

    // Constraints:

    // 1 <= nums.length <= 104
    // -104 <= nums[i] <= 104
    // nums contains values sorted in ascending order.
    // -104 <= target <= 104

    int n, t;
    cin >> n;
    cin >> t;

    vector<int> a(n);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    cout << "Position of " << t << " " << searchInsert(a, t) << endl;
    cout << "Rank = number of element less than equal to " << t << " in array " << getCountSmallerEqual(a, t) << endl;

    return 0;
}

int searchInsert(vector<int> &nums, int target)
{
    int cnt = getCountSmallerEqual(nums, target);

    if (cnt == 0)
    {
        return cnt;
    }

    else if (nums[cnt - 1] == target)
    {
        return cnt - 1;
    }
    return cnt;
}

int getCountSmallerEqual(vector<int> &a, int val)
{
    int n = a.size();
    int l = 0;
    int r = n - 1;

    while (l <= r)
    {
        int mid = (l + r) / 2;
        int el = a[mid];

        if (el <= val)
        {
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }

    return l;
}