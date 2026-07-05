
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct uf
{

    vector<int> parent;
    vector<int> treeSize;

    uf(int n)
    {
        parent.reserve(n);
        treeSize.reserve(n);

        for (int i = 0; i < n; i++)
        {
            //-1 indicates root
            parent.push_back(-1);
            treeSize.push_back(1);
        }
    }

    int findSet(int x)
    {

        if (parent[x] == -1)
        {
            return x;
        }

        int set = findSet(parent[x]);

        //path compression
        parent[x] = set;

        return set;
    }

    bool unionVertices(int x, int y)
    {

        int rep1 = findSet(x);
        int rep2 = findSet(y);

        if (rep1 == rep2)
        {
            return false;
        }

        int s1 = treeSize[rep1];
        int s2 = treeSize[rep2];

        if (s1 >= s2)
        {

            //updateParent
            parent[rep2] = rep1;

            //updateSize
            treeSize[rep1] = s1 + s2;
        }
        else
        {

            //updateParent
            parent[rep1] = rep2;

            //updateSize
            treeSize[rep2] = s1 + s2;
        }

        return true;
    }
};

bool cmp(vector<int> &a, vector<int> &b);
int kruskalsMST(int V, vector<vector<int>> &edges);

int main()
{

    //    geeks for geeks Minimum Spanning Tree - Kruskal's Algorithm
    // Given a weighted, undirected, and connected graph with V vertices and E edges, the task is to find the sum of the weights of the edges in the Minimum Spanning Tree (MST) of the graph using Kruskal's Algorithm. The graph is represented as an edge list edges[][], where edges[i] = [u, v, w] denotes an undirected edge between u and v with weight w.

    // Input: V = 3, E = 3, edges[][] = [[0, 1, 5], [1, 2, 3], [0, 2, 1]]
    //     Output: 4

    //     Input: V = 2, E = 1, edges = [[0, 1, 5]]
    //     Output: 5

    //     Constraints:
    // 2 ≤ V ≤ 1000
    // V-1 ≤ E ≤ (V*(V-1))/2
    // 1 ≤ w ≤ 1000
    // The graph is connected and doesn't contain self-loops & multiple edges.

    int V;
    cin >> V;

    int E;
    cin >> E;

    vector<vector<int>> edges(E, vector<int>(3));

    for (int i = 0; i < E; i++)
    {
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
    }

    cout << "ans = " << kruskalsMST(V, edges) << endl;

    return 0;
}

int kruskalsMST(int V, vector<vector<int>> &edges)
{
    // code here

    //sort edges
    sort(edges.begin(), edges.end(), cmp);

    //initialize union find
    uf disjointSet(V);

    int mstCost = 0;
    int cnt = 0;

    for (int i = 0; i < edges.size(); i++)
    {

        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];

        bool unionDone = disjointSet.unionVertices(u, v);

        if (unionDone)
        {
            cnt += 1;
            mstCost += w;
        }

        if (cnt == (V - 1))
        {
            break;
        }
    }

    return mstCost;
}

bool cmp(vector<int> &a, vector<int> &b)
{

    return a[2] < b[2];
}
