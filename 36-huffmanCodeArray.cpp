
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Node
{
    int f;
    string s;
    Node *left;
    Node *right;

    Node(int a, string b)
    {
        f = a;
        s = b;
        left = NULL;
        right = NULL;
    }
};

void addNode(vector<Node *> &v, Node *a);
void merge2MinNodes(vector<Node *> &v);
void huffmanCodes(string S, vector<int> &f, int N);
void preorder(Node *root, string &s);

int main()
{
    //     Given a string S of distinct character of size N>=2 and their corresponding frequency f[ ]
    // i.e. character S[i] has f[i] frequency.
    //Your task is to build the Huffman tree print all the huffman codes in preorder traversal of the tree.
    // Note: While merging if two nodes have the same value,
    //then the node which occurs at first will be taken on the left of Binary Tree and the other one to the right
    //otherwise Node with less value will be taken on the left of the subtree and other one to the right.
    //if new merged node value is v and there are 3 v's then it will be at 4th position taken at last

    //example
    //abcdef
    // 5 9 12 13 16 45

    // f = 0
    // c = 100
    // d = 101
    // a = 1100
    // b = 1101
    // e = 111

    string s;

    cin >> s;

    int n = s.size();

    vector<int> f(n);
    for (int i = 0; i < n; i++)
    {
        cin >> f[i];
    }

    //prints the optimal encoding
    cout << endl;
    huffmanCodes(s, f, n);
}

void huffmanCodes(string S, vector<int> &f, int N)
{
    // Code here

    vector<Node *> v;

    int cnt = N;

    for (int i = 0; i < cnt; i++)
    {
        Node *a = new Node(f[i], S.substr(i, 1));
        addNode(v, a);
    }

    while (cnt > 1)
    {
        merge2MinNodes(v);
        cnt -= 1;
    }

    Node *root = v[0];

    string p = "";

    preorder(root, p);
}

void addNode(vector<Node *> &v, Node *a)
{
    v.push_back(a);
}

void merge2MinNodes(vector<Node *> &v)
{

    int n = v.size();

    int p1 = 0;

    for (int i = 0; i < n; i++)
    {
        if (v[i]->f < v[p1]->f)
        {
            p1 = i;
        }
    }

    int p2 = p1 == 0 ? 1 : 0;

    for (int i = 0; i < n; i++)
    {
        if (i != p1 && v[i]->f < v[p2]->f)
        {
            p2 = i;
        }
    }

    //merge Nodes
    int mergeFreq = v[p1]->f + v[p2]->f;
    string mergeStr = v[p1]->s + v[p2]->s;

    Node *mergeNode = new Node(mergeFreq, mergeStr);

    mergeNode->left = v[p1];
    mergeNode->right = v[p2];

    //shifting
    int t = 0;
    for (int i = 0; i < n; i++)
    {
        if (i != p1 && i != p2)
        {
            v[t] = v[i];
            t += 1;
        }
    }

    v.pop_back();
    v.pop_back();
    v.push_back(mergeNode);
}

void preorder(Node *root, string &s)
{

    //its a leaf in this case
    if (root->left == NULL && root->right == NULL)
    {
        cout << root->s << " = " << s << endl;
        return;
    }

    s.push_back('0');
    preorder(root->left, s);

    s.pop_back();

    s.push_back('1');
    preorder(root->right, s);

    s.pop_back();
}
