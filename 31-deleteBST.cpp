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

TreeNode *deleteNode(TreeNode *root, int key);
TreeNode *search(TreeNode *root, int key, TreeNode *&parent);
TreeNode *delNode(TreeNode *root, TreeNode *t, TreeNode *parent);
void inorder(TreeNode *root);

int main()
{
    //Leetcode - 450. Delete Node in a BST
    //Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node reference (possibly updated) of the BST.

    // Basically, the deletion can be divided into two stages:

    // Search for a node to remove.
    // If the node is found, delete the node.

    // Example 1:

    // Input: root = [5,3,6,2,4,null,7], key = 3
    // Output: [5,4,6,2,null,null,7]
    // Explanation: Given key to delete is 3. So we find the node with value 3 and delete it.
    // One valid answer is [5,4,6,2,null,null,7], shown in the above BST.
    // Please notice that another valid answer is [5,2,6,null,4,null,7] and it's also accepted.

    // Example 2:

    // Input: root = [5,3,6,2,4,null,7], key = 0
    // Output: [5,3,6,2,4,null,7]
    // Explanation: The tree does not contain a node with value = 0.
    // Example 3:

    // Input: root = [], key = 0
    // Output: []

    // Constraints:

    // The number of nodes in the tree is in the range [0, 104].
    // -105 <= Node.val <= 105
    // Each node has a unique value.
    // root is a valid binary search tree.
    // -105 <= key <= 105

    // Follow up: Could you solve it with time complexity O(height of tree)?

    TreeNode *root = new TreeNode(33);
    root->left = new TreeNode(22);
    root->right = new TreeNode(55);

    root = deleteNode(root, 33);

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

TreeNode *deleteNode(TreeNode *root, int key)
{

    TreeNode *parent = NULL;

    TreeNode *t = search(root, key, parent);

    return delNode(root, t, parent);
}

TreeNode *search(TreeNode *root, int key, TreeNode *&parent)
{

    if (root == NULL)
    {
        return NULL;
    }

    else if (key == root->val)
    {
        return root;
    }

    else if (key < root->val)
    {
        parent = root;
        return search(root->left, key, parent);
    }
    else
    {
        parent = root;
        return search(root->right, key, parent);
    }
}

TreeNode *delNode(TreeNode *root, TreeNode *t, TreeNode *parent)
{

    if (t == NULL)
    {
        return root;
    }

    if (t->left == NULL && t->right == NULL)
    {

        if (parent == NULL)
        {
            root = NULL;
        }

        else if (parent->left == t)
        {
            parent->left = NULL;
        }
        else
        {
            parent->right = NULL;
        }

        delete t;

        return root;
    }

    else if (t->left == NULL)
    {
        if (parent == NULL)
        {
            root = t->right;
        }

        else if (parent->left == t)
        {
            parent->left = t->right;
        }
        else
        {
            parent->right = t->right;
        }

        delete t;

        return root;
    }

    else if (t->right == NULL)
    {

        if (parent == NULL)
        {
            root = t->left;
        }

        else if (parent->left == t)
        {
            parent->left = t->left;
        }
        else
        {
            parent->right = t->left;
        }

        delete t;
        return root;
    }
    else
    {

        TreeNode *temp = t->left;

        TreeNode *p = t;

        while (temp->right != NULL)
        {
            p = temp;
            temp = temp->right;
        }

        t->val = temp->val;

        return delNode(root, temp, p);
    }
}
