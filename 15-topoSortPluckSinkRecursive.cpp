#include <iostream>
#include <vector>

using namespace std;

vector<int> topoSort(int V, vector<vector<int>> &edges);
vector<int> pluckSink(vector<vector<int>> &adj);
void dfs(vector<vector<int>> &adj, vector<bool> &visited, int src, int &currIndex, vector<int> &res);

int main()
{

    //     Given a Directed Acyclic Graph (DAG) of V (0 to V-1) vertices and E edges represented as a 2D list of edges[][], where each entry edges[i] = [u, v] denotes a directed edge u -> v. Return the topological sort for the given graph.

    // Topological sorting for Directed Acyclic Graph (DAG) is a linear ordering of vertices such that for every directed edge u -> v, vertex u comes before v in the ordering.
    // Note: As there are multiple Topological orders possible, you may return any of them
    //Input: V = 4, E = 3, edges[][] = [[3, 0], [1, 0], [2, 0]]
    //     Output:  Few valid Topological orders for the given graph are:
    // [3, 2, 1, 0]
    // [1, 2, 3, 0]
    // [2, 3, 1, 0]

    int vertices, edges;

    cin >> vertices >> edges;

    vector<vector<int>> edgesArr(edges);

    int u, v;

    for (int i = 0; i < edges; i++)
    {
        cin >> u >> v;
        edgesArr[i].push_back(u);
        edgesArr[i].push_back(v);
    }
    vector<int> topoOrder = topoSort(vertices, edgesArr);

    cout << "topological order " << endl;

    for (int x : topoOrder)
    {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}

vector<int> topoSort(int V, vector<vector<int>> &edges)
{
    // code here

    vector<vector<int>> adj(V);

    for (int i = 0; i < edges.size(); i++)
    {
        int a = edges[i][0];
        int b = edges[i][1];

        adj[a].push_back(b);
    }

    return pluckSink(adj);
}

vector<int> pluckSink(vector<vector<int>> &adj)
{

    int v = adj.size();
    vector<int> res(v);
    vector<bool> visited(v, false);

    int currIndex = v - 1;

    for (int i = 0; i < v; i++)
    {
        if (!visited[i])
        {
            dfs(adj, visited, i, currIndex, res);
        }
    }

    return res;
}

void dfs(vector<vector<int>> &adj, vector<bool> &visited, int src, int &currIndex, vector<int> &res)
{
    visited[src] = true;

    for (int u : adj[src])
    {
        if (!visited[u])
        {
            dfs(adj, visited, u, currIndex, res);
        }
    }

    res[currIndex] = src;
    currIndex -= 1;
}
