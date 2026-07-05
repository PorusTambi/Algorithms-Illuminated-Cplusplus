
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
bool cmp(vector<int> &a, vector<int> &b);
int kruskalsMST(int V, vector<vector<int>> &edges);
bool uvPathExist(int u, int v, vector<vector<int>> &adj);
void dfs(int src, vector<vector<int>> &adj, vector<bool> &visited);

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

bool cmp(vector<int> &a, vector<int> &b)
{

    return a[2] < b[2];
}

int kruskalsMST(int V, vector<vector<int>> &edges)
{
    // code here

    //sort edges
    sort(edges.begin(), edges.end(), cmp);

    vector<vector<int>> adjTree(V);

    int mstCost = 0;
    int cnt = 0;

    for (int i = 0; i < edges.size(); i++)
    {

        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];

        bool doesCreateCycle = uvPathExist(u, v, adjTree);

        if (!doesCreateCycle)
        {

            adjTree[u].push_back(v);
            adjTree[v].push_back(u);

            mstCost += w;
            cnt += 1;
        }

        if (cnt == (V - 1))
        {
            break;
        }
    }

    return mstCost;
}

bool uvPathExist(int u, int v, vector<vector<int>> &adj)
{

    int vertices = adj.size();
    vector<bool> visited(vertices, false);

    dfs(u, adj, visited);

    return visited[v];
}

void dfs(int src, vector<vector<int>> &adj, vector<bool> &visited)
{

    visited[src] = true;

    for (int v : adj[src])
    {

        if (!visited[v])
        {
            dfs(v, adj, visited);
        }
    }
}