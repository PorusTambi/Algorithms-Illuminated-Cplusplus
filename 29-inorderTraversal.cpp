#include <iostream>
#include <stack>
#include <vector>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
vector<int> inorderTraversal(TreeNode *root);
void inorder(TreeNode *root, vector<int> &a);
vector<int> inorderTraversalIter(TreeNode *root);

int main()
{
    //Leetcode - 94. Binary Tree Inorder Traversal
    //Given the root of a binary tree, return the inorder traversal of its nodes' values.

    // Example 1:

    // Input: root = [1,null,2,3]

    // Output: [1,3,2]

    // Explanation:

    // Example 2:

    // Input: root = [1,2,3,4,5,null,8,null,null,6,7,9]

    // Output: [4,2,6,5,7,1,3,9,8]

    // Explanation:

    // Example 3:

    // Input: root = []

    // Output: []

    // Example 4:

    // Input: root = [1]

    // Output: [1]

    // Constraints:

    // The number of nodes in the tree is in the range [0, 100].
    // -100 <= Node.val <= 100

    // Follow up: Recursive solution is trivial, could you do it iteratively?

    TreeNode *root = new TreeNode(33);
    root->left = new TreeNode(22);
    root->right = new TreeNode(55);

    vector<int> v1 = inorderTraversal(root);
    vector<int> v2 = inorderTraversalIter(root);

    cout << "inorder recursive ";
    for (int x : v1)
    {
        cout << x << " ";
    }

    cout << endl;

    cout << "inorder iterative ";
    for (int x : v2)
    {
        cout << x << " ";
    }

    cout << endl;

    return 0;
}

vector<int> inorderTraversal(TreeNode *root)
{

    vector<int> ans;
    inorder(root, ans);

    return ans;
}

void inorder(TreeNode *root, vector<int> &a)
{

    if (root == NULL)
    {
        return;
    }

    inorder(root->left, a);
    a.push_back(root->val);
    inorder(root->right, a);
}

vector<int> inorderTraversalIter(TreeNode *root)
{
    vector<int> ans;

    stack<pair<TreeNode *, bool>> s;
    s.push({root, true});

    while (!s.empty())
    {
        auto &p = s.top();
        bool l = p.second;
        TreeNode *t = p.first;

        if (t == NULL)
        {
            s.pop();
        }
        else if (l)
        {
            p.second = false;
            s.push({t->left, true});
        }
        else
        {
            ans.push_back(t->val);
            s.pop();
            s.push({t->right, true});
        }
    }

    return ans;
}