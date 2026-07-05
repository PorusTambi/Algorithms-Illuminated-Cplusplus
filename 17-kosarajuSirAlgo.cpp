#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> getAdjListDirectedGraph();
int kosaraju(vector<vector<int>> &adj);
void dfs(vector<vector<int>> &adj, vector<bool> &visited, int src, vector<int> &vFinishTimeAsc);
void dfsScc(vector<vector<int>> &adj, vector<bool> &visited, int src, vector<int> &scc, int &sccCount);

int main()
{
    //     Given an adjacency list, adj of Directed Graph, Find the number of strongly connected components in the graph

    // Examples :

    // Input: adj[][] = [[2, 3], [0], [1], [4], []]

    // Output: 3
    // Explanation: We can clearly see that there are 3 Strongly Connected Components in the Graph.

    vector<vector<int>> adj = getAdjListDirectedGraph();

    int totalDifferentComponents = kosaraju(adj);

    cout << endl
         << "Total different components " << totalDifferentComponents << endl;

    return 0;
}

vector<vector<int>> getAdjListDirectedGraph()
{
    int vertices, edges;
    cin >> vertices >> edges;

    vector<vector<int>> adj(vertices);

    int u, v;
    for (int i = 0; i < edges; i++)
    {
        cin >> u >> v;
        adj[u].push_back(v);
    }

    return adj;
}

int kosaraju(vector<vector<int>> &adj)
{
    // code here

    int v = adj.size();
    vector<vector<int>> revGraph(v);

    //create reverse graph
    for (int i = 0; i < v; i++)
    {
        for (int u : adj[i])
        {
            revGraph[u].push_back(i);
        }
    }

    vector<bool> visited(v, false);
    vector<int> vFinishTimeAsc;
    vFinishTimeAsc.reserve(v);

    for (int i = 0; i < v; i++)
    {
        if (!visited[i])
        {
            dfs(revGraph, visited, i, vFinishTimeAsc);
        }
    }

    //mark all unexplored
    for (int i = 0; i < v; i++)
    {
        visited[i] = false;
    }

    vector<int> scc(v);
    int sccCount = 0;

    for (int i = v - 1; i >= 0; i--)
    {
        int src = vFinishTimeAsc[i];
        if (!visited[src])
        {
            sccCount += 1;
            dfsScc(adj, visited, src, scc, sccCount);
        }
    }

    cout << "Component of each vertex " << endl;
    for (int i = 0; i < v; i++)
    {
        cout << "Vertex " << i << "-" << scc[i] << endl;
    }

    return sccCount;
}

void dfs(vector<vector<int>> &adj, vector<bool> &visited, int src, vector<int> &vFinishTimeAsc)
{

    visited[src] = true;

    for (int u : adj[src])
    {
        if (!visited[u])
        {
            dfs(adj, visited, u, vFinishTimeAsc);
        }
    }

    vFinishTimeAsc.push_back(src);
}

void dfsScc(vector<vector<int>> &adj, vector<bool> &visited, int src, vector<int> &scc, int &sccCount)
{

    visited[src] = true;
    scc[src] = sccCount;

    for (int u : adj[src])
    {

        if (!visited[u])
        {
            dfsScc(adj, visited, u, scc, sccCount);
        }
    }
}
