#include <iostream>
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
TreeNode *searchBST(TreeNode *root, int val);
TreeNode *searchBSTIter(TreeNode *root, int val);

int main()
{
    //Leetcode - 700. Search in a Binary Search Tree
    //You are given the root of a binary search tree (BST) and an integer val.

    //Find the node in the BST that the node's value equals val and return the subtree rooted with that node.
    // If such a node does not exist, return null.
    // Example 1:

    //   4
    //  2 7
    // n n 8 n
    // Input: root = [4,2,7,null,null,8], val = 2
    //2's both child are null
    // Output: [2,1,3]

    //     Input: root = [4,2,7,1,3], val = 5
    // Output: []

    // Constraints:

    // The number of nodes in the tree is in the range [1, 5000].
    // 1 <= Node.val <= 107
    // root is a binary search tree.
    // 1 <= val <= 107

    TreeNode *root = new TreeNode(33);
    root->left = new TreeNode(22);
    root->right = new TreeNode(55);

    cout << "search 55 recursive " << searchBST(root, 55)->val << endl;
    cout << "search 55 iterative" << searchBSTIter(root, 55)->val << endl;

    return 0;
}

TreeNode *searchBST(TreeNode *root, int val)
{
    if (root == NULL)
    {
        return NULL;
    }

    else if (root->val == val)
    {
        return root;
    }

    else if (root->val > val)
    {
        return searchBST(root->left, val);
    }
    else
    {
        return searchBST(root->right, val);
    }
}

TreeNode *searchBSTIter(TreeNode *root, int val)
{

    while (root != NULL)
    {
        if (root->val == val)
        {
            return root;
        }
        else if (root->val > val)
        {
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }

    return NULL;
}
