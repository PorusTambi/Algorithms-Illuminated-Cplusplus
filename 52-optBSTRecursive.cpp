
#include <iostream>
#include <vector>

using namespace std;

struct Node
{

    int key;
    Node *left;
    Node *right;

    Node(int k)
    {
        key = k;
        left = NULL;
        right = NULL;
    }
};

int minCost(vector<int> &keys, vector<int> &freq);
int dpBst(int i, int j, vector<int> &freq, vector<vector<int>> &memo,
          vector<int> &prefixSum, vector<vector<int>> &choices);
Node *reconstructTree(int i, int j, vector<vector<int>> &choices, vector<int> &keys);
void inorderTraversal(Node *root);

int main()
{

    // Geeks for Geeks - Optimal binary search tree
    // You are given a set of distinct keys in sorted order, which is represent by keys[]. Each key ki represents a data record that is accessed during a search operation. For all the keys, you are also given a frequency array freq[], which denotes how many times key ki is searched for.
    // The cost of accessing a key in a binary search tree is calculated by multiplying its access frequency by the level at which it appears in the tree. Therefore different arrangements of keys in the BST gives different total search costs.

    // Your task is to calculate the minimum total search cost required to construct a binary search tree containing all the keys.

    // Note: Consider the root of the BST is at level 1.

    // Examples:

    // Input: keys[] = [10, 12], freq[] = [34, 50]
    // Output: 118
    // Explaination: There can be following two possible BSTs
    // The cost of tree I is 34*1 + 50*2 = 134
    // The cost of tree II is 50*1 + 34*2 = 118

    // Input: keys[] = [10, 12, 20], freq[] = [34, 8, 50]
    // Output: 142
    // Explaination: There can be many possible BSTs

    // Among all possible BSTs,
    // cost of the 5th BST is minimum.
    // Cost of this BST is 1*50 + 2*34 + 3*8 = 142
    // Constraints:
    // 1 ≤ keys.size() = freq.size() ≤ 100
    // 1 ≤ keys[i], freq[i] ≤ 104

    int n;

    cin >> n;

    vector<int> keys(n);
    vector<int> freq(n);

    for (int i = 0; i < n; i++)
    {
        cin >> keys[i];
    }

    for (int i = 0; i < n; i++)
    {
        cin >> freq[i];
    }

    int ans = minCost(keys, freq);

    cout << "optimal cost " << ans << endl;

    return 0;
}

int minCost(vector<int> &keys, vector<int> &freq)
{

    //recursion + reconstruction

    int n = freq.size();

    vector<vector<int>> memo(n, vector<int>(n, -1));
    vector<vector<int>> choices(n, vector<int>(n, -1));

    vector<int> prefixSum(n, 0);
    int curr = 0;

    for (int i = 0; i < n; i++)
    {
        curr += freq[i];
        prefixSum[i] = curr;
    }

    int ans = dpBst(0, n - 1, freq, memo, prefixSum, choices);

    Node *root = reconstructTree(0, n - 1, choices, keys);
    inorderTraversal(root);
    cout << endl;

    return ans;

    // code here
}
int dpBst(int i, int j, vector<int> &freq, vector<vector<int>> &memo,
          vector<int> &prefixSum, vector<vector<int>> &choices)
{

    if (memo[i][j] != -1)
    {

        return memo[i][j];
    }

    int sel;
    //recursion
    int minVal = -1;

    for (int k = i; k <= j; k++)
    {

        int s = freq[k];
        int l = 0;
        int r = 0;

        if ((k - 1) >= i)
        {
            l = dpBst(i, k - 1, freq, memo, prefixSum, choices);
            l += prefixSum[k - 1] - prefixSum[i] + freq[i];
        }

        if ((k + 1) <= j)
        {
            r = dpBst(k + 1, j, freq, memo, prefixSum, choices);
            r += prefixSum[j] - prefixSum[k + 1] + freq[k + 1];
        }

        s = s + l + r;

        if (minVal == -1)
        {
            minVal = s;
            sel = k;
        }
        else if (minVal > s)
        {
            minVal = s;
            sel = k;
        }
    }

    memo[i][j] = minVal;
    choices[i][j] = sel;

    return minVal;
}

Node *reconstructTree(int i, int j, vector<vector<int>> &choices, vector<int> &keys)
{

    if (i > j)
    {
        return NULL;
    }

    int ind = choices[i][j];

    Node *root = new Node(keys[ind]);

    root->left = reconstructTree(i, ind - 1, choices, keys);
    root->right = reconstructTree(ind + 1, j, choices, keys);

    return root;
}

void inorderTraversal(Node *root)
{

    if (root == NULL)
    {
        return;
    }

    inorderTraversal(root->left);
    cout << root->key << " ";
    inorderTraversal(root->right);
}