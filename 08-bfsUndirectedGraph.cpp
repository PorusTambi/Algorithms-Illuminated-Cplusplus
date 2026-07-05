#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<int>> getAdjListUndirectedGraph();
void bfs(vector<vector<int>> &adj, int src, vector<bool> &visited, vector<int> &res);
vector<int> getOrder(vector<vector<int>> &adj);

int main()
{
    //vertices are numbered from 0 to v-1
    //     Given a connected undirected graph containing V vertices, represented by a 2-d adjacency list adj[][], where each adj[i] represents the list of vertices connected to vertex i. Perform a Breadth First Search (BFS) traversal starting from vertex 0, visiting vertices from left to right according to the given adjacency list, and return a list containing the BFS traversal of the graph.

    // Note: Do traverse in the same order as they are in the given adjacency list.

    // Examples:

    // Input: adj[][] = [[2, 3, 1], [0], [0, 4], [0], [2]]

    // Output: [0, 2, 3, 1, 4]

    vector<vector<int>> adj = getAdjListUndirectedGraph();

    vector<int> bfsOrder = getOrder(adj);

    cout << "Bfs order " << endl;
    for (int x : bfsOrder)
    {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}

vector<vector<int>> getAdjListUndirectedGraph()
{
    int vertices, edges;
    cin >> vertices >> edges;

    vector<vector<int>> adj(vertices);

    int u, v;
    for (int i = 0; i < edges; i++)
    {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    return adj;
}

vector<int> getOrder(vector<vector<int>> &adj)
{
    // code here
    int v = adj.size();
    vector<int> res;
    res.reserve(v);

    vector<bool> visited(v, false);

    for (int i = 0; i < v; i++)
    {
        if (!visited[i])
        {
            bfs(adj, i, visited, res);
        }
    }

    return res;
}

void bfs(vector<vector<int>> &adj, int src, vector<bool> &visited, vector<int> &res)
{
    queue<int> q;
    visited[src] = true;

    q.push(src);

    while (!q.empty())
    {

        int vertex = q.front();
        q.pop();

        res.push_back(vertex);

        for (int x : adj[vertex])
        {
            if (!visited[x])
            {
                visited[x] = true;
                q.push(x);
            }
        }
    }
}
