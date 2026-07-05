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
TreeNode *deleteVal(TreeNode *root, int x);
TreeNode *searchVal(TreeNode *root, int x);
TreeNode *selectVal(TreeNode *root, int i);
TreeNode *selectValIter(TreeNode *root, int i);
bool validateSize(TreeNode *root);

int main()
{
    //only distinct values will be added in the tree
    //search index 1 to n

    TreeNode *root = NULL;

    root = insertVal(root, NULL, 1);
    root = insertVal(root, NULL, 99);
    root = insertVal(root, NULL, 12);
    root = insertVal(root, NULL, 31);
    root = insertVal(root, NULL, -22);
    root = insertVal(root, NULL, 10);

    root = deleteVal(root, 10);

    cout << selectVal(root, 3)->val << endl;

    TreeNode *s1 = selectVal(root, 22);

    if (s1 == NULL)
    {
        cout << "No value" << endl;
    }

    cout << selectValIter(root, 3)->val << endl;

    cout << "validate size = " << validateSize(root) << endl;

    return 0;
}

TreeNode *insertVal(TreeNode *root, TreeNode *parent, int x)
{
    if (root == NULL)
    {
        return new TreeNode(x, parent);
    }

    int val = root->val;

    if (x < val)
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

TreeNode *deleteVal(TreeNode *root, int x)
{
    TreeNode *t = searchVal(root, x);

    if (t == NULL)
    {
        return root;
    }

    TreeNode *p = t->parent;

    TreeNode *c = t->left == NULL ? t->right : t->left;

    if (t->left == NULL || t->right == NULL)
    {

        if (p == NULL)
        {
            root = c;
        }
        else if (p->left == t)
        {
            p->left = c;
        }
        else
        {
            p->right = c;
        }

        if (c != NULL)
        {
            c->parent = p;
        }
    }

    else
    {

        TreeNode *curr = t->left;
        while (curr->right != NULL)
        {
            curr = curr->right;
        }

        int val = curr->val;

        root = deleteVal(root, curr->val);

        t->val = val;

        return root;
    }

    p = t->parent;

    while (p != NULL)
    {
        p->size -= 1;
        p = p->parent;
    }

    delete t;

    return root;
}

TreeNode *searchVal(TreeNode *root, int x)
{
    if (root == NULL)
    {
        return NULL;
    }

    int val = root->val;

    if (x == val)
    {
        return root;
    }

    else if (x < val)
    {
        return searchVal(root->left, x);
    }
    else
    {
        return searchVal(root->right, x);
    }
}

TreeNode *selectVal(TreeNode *root, int i)
{

    if (root == NULL)
    {
        return NULL;
    }

    int l = root->left == NULL ? 0 : root->left->size;
    int r = root->right == NULL ? 0 : root->right->size;

    if (i == (l + 1))
    {
        return root;
    }
    else if (i <= l)
    {
        return selectVal(root->left, i);
    }
    else if (i > (l + r + 1))
    {
        return NULL;
    }
    else
    {
        return selectVal(root->right, i - (l + 1));
    }
}

TreeNode *selectValIter(TreeNode *root, int i)
{

    while (root != NULL)
    {
        int l = root->left == NULL ? 0 : root->left->size;
        int s = root->size;

        if (i > s)
        {
            return NULL;
        }
        else if (i == l + 1)
        {
            return root;
        }
        else if (i <= l)
        {
            root = root->left;
        }
        else
        {
            root = root->right;
            i = i - (l + 1);
        }
    }

    return root;
}

bool validateSize(TreeNode *root)
{
    if (root == NULL)
    {
        return true;
    }

    int s = root->size;

    int l = root->left == NULL ? 0 : root->left->size;
    int r = root->right == NULL ? 0 : root->right->size;

    return (s == (l + r + 1)) && validateSize(root->left) && validateSize(root->right);
}