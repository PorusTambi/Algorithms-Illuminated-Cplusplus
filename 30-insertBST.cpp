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

TreeNode *insertIntoBST(TreeNode *root, int val);
TreeNode *insertIntoBSTIter(TreeNode *root, int val);
void inorder(TreeNode *root);

int main()
{
    //Leetcode - 701. Insert into a Binary Search Tree
    //     You are given the root node of a binary search tree (BST) and a value to insert into the tree. Return the root node of the BST after the insertion. It is guaranteed that the new value does not exist in the original BST.

    // Notice that there may exist multiple valid ways for the insertion, as long as the tree remains a BST after insertion. You can return any of them.

    // Example 1:

    // Input: root = [4,2,7,1,3], val = 5
    // Output: [4,2,7,1,3,5]
    // Explanation: Another accepted tree is:

    // Example 2:

    // Input: root = [40,20,60,10,30,50,70], val = 25
    // Output: [40,20,60,10,30,50,70,null,null,25]
    // Example 3:

    // Input: root = [4,2,7,1,3,null,null,null,null,null,null], val = 5
    // Output: [4,2,7,1,3,5]

    // Constraints:

    // The number of nodes in the tree will be in the range [0, 104].
    // -108 <= Node.val <= 108
    // All the values Node.val are unique.
    // -108 <= val <= 108
    // It's guaranteed that val does not exist in the original BST.

    TreeNode *root = new TreeNode(33);
    root->left = new TreeNode(22);
    root->right = new TreeNode(55);

    root = insertIntoBST(root, 2);
    root = insertIntoBSTIter(root, 32);

    cout << endl;
    inorder(root);
    cout << endl;

    return 0;
}

void inorder(TreeNode *root)
{

    if (root == NULL)
    {
        return;
    }

    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

TreeNode *insertIntoBST(TreeNode *root, int val)
{

    if (root == NULL)
    {
        return new TreeNode(val);
    }

    if (val < root->val)
    {

        TreeNode *subtreeRoot = insertIntoBST(root->left, val);

        root->left = subtreeRoot;

        return root;
    }
    else
    {

        TreeNode *subtreeRoot = insertIntoBST(root->right, val);

        root->right = subtreeRoot;

        return root;
    }
}

TreeNode *insertIntoBSTIter(TreeNode *root, int val)
{
    TreeNode *prev = NULL;
    TreeNode *curr = root;

    while (curr != NULL)
    {
        prev = curr;
        if (val < curr->val)
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    }

    TreeNode *t = new TreeNode(val);

    if (prev == NULL)
    {
        return t;
    }

    if (val < prev->val)
    {

        prev->left = t;
    }
    else
    {

        prev->right = t;
    }

    return root;
}