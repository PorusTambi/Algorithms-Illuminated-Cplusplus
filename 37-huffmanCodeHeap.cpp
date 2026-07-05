#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

struct Node
{
    int f;
    int id;

    string s;

    Node *left;
    Node *right;

    Node(int i, int a, string b)
    {
        id = i;
        f = a;
        s = b;
        left = NULL;
        right = NULL;
    }
};

struct cmp
{

    bool operator()(Node *a, Node *b)
    {

        if (a->f == b->f)
        {
            return a->id > b->id;
        }
        return a->f > b->f;
    }
};

void addNode(priority_queue<Node *, vector<Node *>, cmp> &pq, Node *a);
void merge2MinNodes(priority_queue<Node *, vector<Node *>, cmp> &pq, int &counter);
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

    vector<string> ans;
    priority_queue<Node *, vector<Node *>, cmp> pq;

    int cnt = N;

    for (int i = 0; i < cnt; i++)
    {
        Node *a = new Node(i, f[i], S.substr(i, 1));
        addNode(pq, a);
    }

    int counter = N;

    while (cnt > 1)
    {
        merge2MinNodes(pq, counter);
        cnt -= 1;
    }

    Node *root = pq.top();
    pq.pop();

    string p = "";

    cout << endl;
    preorder(root, p);
}

void addNode(priority_queue<Node *, vector<Node *>, cmp> &pq, Node *a)
{

    pq.push(a);
}

void merge2MinNodes(priority_queue<Node *, vector<Node *>, cmp> &pq, int &counter)
{

    Node *n1 = pq.top();
    pq.pop();

    Node *n2 = pq.top();
    pq.pop();

    //merge Nodes
    int mergeFreq = n1->f + n2->f;
    string mergeStr = n1->s + n2->s;

    Node *mergeNode = new Node(counter, mergeFreq, mergeStr);

    mergeNode->left = n1;
    mergeNode->right = n2;

    pq.push(mergeNode);

    counter += 1;
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
