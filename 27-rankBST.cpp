#include <iostream>

using namespace std;

struct TreeNode
{
    int val;
    int size;
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;

    TreeNode(int x, TreeNode *p) : val(x), size(1), left(NULL), right(NULL), parent(p) {}
};

TreeNode *insertVal(TreeNode *root, TreeNode *parent, int x);
int getRank(TreeNode *root, int x);
int getRankIter(TreeNode *root, int x);

int main()
{
    //only distinct values will be added in the tree
    //search index 1 to n

    int x;
    cin >> x;

    TreeNode *root = NULL;

    root = insertVal(root, NULL, 1);
    root = insertVal(root, NULL, 99);
    root = insertVal(root, NULL, 12);
    root = insertVal(root, NULL, 1);
    root = insertVal(root, NULL, -22);
    root = insertVal(root, NULL, 10);
    root = insertVal(root, NULL, 10);

    cout << "Rank of x = " << getRank(root, x) << endl;
    cout << "RankIter of x = " << getRankIter(root, x) << endl;

    return 0;
}

TreeNode *insertVal(TreeNode *root, TreeNode *parent, int x)
{
    if (root == NULL)
    {
        return new TreeNode(x, parent);
    }

    int val = root->val;

    if (x <= val)
    {
        root->left = insertVal(root->left, root, x);
        root->size += 1;
    }
    else
    {
        root->right = insertVal(root->right, root, x);
        root->size += 1;
    }

    return root;
}

int getRank(TreeNode *root, int x)
{
    if (root == NULL)
    {
        return 0;
    }

    int val = root->val;
    int l = root->left == NULL ? 0 : root->left->size;

    if (x >= val)
    {
        return l + 1 + getRank(root->right, x);
    }

    else
    {
        return getRank(root->left, x);
    }
}

int getRankIter(TreeNode *root, int x)
{
    int cnt = 0;

    while (root != NULL)
    {

        int val = root->val;
        int l = root->left == NULL ? 0 : root->left->size;

        if (x >= val)
        {
            cnt += l + 1;
            root = root->right;
        }
        else
        {
            root = root->left;
        }
    }

    return cnt;
}