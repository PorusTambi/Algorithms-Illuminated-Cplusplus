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

bool cmp(Node *a, Node *b);
void addNode(queue<Node *> &q1, Node *a);
void merge2MinNodes(queue<Node *> &q1, queue<Node *> &q2, int &counter);
void preorder(Node *root, string &s);
void huffmanCodes(string S, vector<int> &f, int N);

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

bool cmp(Node *a, Node *b)
{

    if (a->f == b->f)
    {
        return a->id < b->id;
    }
    return a->f < b->f;
}

void huffmanCodes(string S, vector<int> &f, int N)
{
    // Code here

    vector<Node *> v;

    queue<Node *> q1;
    queue<Node *> q2;

    int cnt = N;

    for (int i = 0; i < cnt; i++)
    {
        Node *a = new Node(i, f[i], S.substr(i, 1));
        v.push_back(a);
    }

    sort(v.begin(), v.end(), cmp);

    for (int i = 0; i < cnt; i++)
    {
        addNode(q1, v[i]);
    }

    v.clear();

    int counter = N;

    while (cnt > 1)
    {

        merge2MinNodes(q1, q2, counter);
        cnt -= 1;
    }

    Node *root = q2.front();
    q2.pop();

    string p = "";

    cout << endl;
    preorder(root, p);
}

void addNode(queue<Node *> &q1, Node *a)
{
    q1.push(a);
}

void merge2MinNodes(queue<Node *> &q1, queue<Node *> &q2, int &counter)
{

    Node *arr[2];

    for (int i = 0; i < 2; i++)
    {

        int s1 = q1.size();
        int s2 = q2.size();

        if (s1 == 0)
        {
            arr[i] = q2.front();
            q2.pop();
        }
        else if (s2 == 0)
        {
            arr[i] = q1.front();
            q1.pop();
        }

        else
        {

            Node *p1 = q1.front();
            Node *p2 = q2.front();

            if (p1->f <= p2->f)
            {
                arr[i] = p1;
                q1.pop();
            }
            else
            {
                arr[i] = p2;
                q2.pop();
            }
        }
    }

    int mergeFreq = arr[0]->f + arr[1]->f;
    string ms = arr[0]->s + arr[1]->s;
    Node *mergeNode = new Node(counter, mergeFreq, ms);

    mergeNode->left = arr[0];
    mergeNode->right = arr[1];

    q2.push(mergeNode);

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
