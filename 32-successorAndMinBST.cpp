#include <iostream>
#include <unordered_map>

using namespace std;

// Definition for a binary tree node.
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class BSTIterator
{
public:
    //stores parent pointers
    unordered_map<TreeNode *, TreeNode *> m;
    TreeNode *nextNode = NULL;

    BSTIterator(TreeNode *root)
    {
        setParents(root, NULL);
        nextNode = root;

        while (nextNode->left != NULL)
        {
            nextNode = nextNode->left;
        }
    }

    int next()
    {
        int val = nextNode->val;

        if (nextNode->right != NULL)
        {

            nextNode = nextNode->right;
            nextNode = getMinIter(nextNode);
        }
        else
        {

            TreeNode *p = m[nextNode];

            //follow parent pointers
            while (p != NULL && p->right == nextNode)
            {
                nextNode = p;
                p = m[nextNode];
            }

            nextNode = p;
        }

        return val;
    }

    bool hasNext()
    {
        return nextNode != NULL;
    }

    void setParents(TreeNode *root, TreeNode *p)
    {
        if (root == NULL)
        {
            return;
        }
        setParents(root->left, root);
        m[root] = p;
        setParents(root->right, root);
    }

    TreeNode *getMin(TreeNode *root)
    {
        if (root == NULL)
        {
            return NULL;
        }
        else if (root->left == NULL)
        {
            return root;
        }
        else
        {
            return getMin(root->left);
        }
    }
    TreeNode *getMinIter(TreeNode *root)
    {
        if (root == NULL)
        {
            return NULL;
        }
        while (root->left != NULL)
        {
            root = root->left;
        }
        return root;
    }
};

int main()
{
    //Leetcode - 173. Binary Search Tree Iterator
    //     Implement the BSTIterator class that represents an iterator over the in-order traversal of a binary search tree (BST):

    // BSTIterator(TreeNode root) Initializes an object of the BSTIterator class. The root of the BST is given as part of the constructor. The pointer should be initialized to a non-existent number smaller than any element in the BST.
    // boolean hasNext() Returns true if there exists a number in the traversal to the right of the pointer, otherwise returns false.
    // int next() Moves the pointer to the right, then returns the number at the pointer.
    // Notice that by initializing the pointer to a non-existent smallest number, the first call to next() will return the smallest element in the BST.

    // You may assume that next() calls will always be valid. That is, there will be at least a next number in the in-order traversal when next() is called.

    // Example 1:

    // Input
    // ["BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next", "hasNext", "next", "hasNext"]
    // [[[7, 3, 15, null, null, 9, 20]], [], [], [], [], [], [], [], [], []]
    // Output
    // [null, 3, 7, true, 9, true, 15, true, 20, false]

    // Explanation
    // BSTIterator bSTIterator = new BSTIterator([7, 3, 15, null, null, 9, 20]);
    // bSTIterator.next();    // return 3
    // bSTIterator.next();    // return 7
    // bSTIterator.hasNext(); // return True
    // bSTIterator.next();    // return 9
    // bSTIterator.hasNext(); // return True
    // bSTIterator.next();    // return 15
    // bSTIterator.hasNext(); // return True
    // bSTIterator.next();    // return 20
    // bSTIterator.hasNext(); // return False

    // Constraints:

    // The number of nodes in the tree is in the range [1, 105].
    // 0 <= Node.val <= 106
    // At most 105 calls will be made to hasNext, and next.

    // Follow up:

    // Could you implement next() and hasNext() to run in average O(1) time and use O(h) memory, where h is the height of the tree?

    TreeNode *root = new TreeNode(33);
    root->left = new TreeNode(22);
    root->right = new TreeNode(55);

    BSTIterator *obj = new BSTIterator(root);
    int param_1 = obj->next();
    bool param_2 = obj->hasNext();

    cout << "next = " << param_1 << endl
         << "has next = " << param_2 << endl
         << "next next = " << obj->next() << endl;
}
