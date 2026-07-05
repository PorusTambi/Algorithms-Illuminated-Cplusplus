#include <iostream>
#include <queue>
#include <vector>
using namespace std;

void augumentedBfs(vector<vector<int>> &adj, int src, vector<bool> &visited, vector<int> &d);
vector<int> shortestPath(int V, vector<vector<int>> &edges, int src);

int main()
{
    //     You are given an undirected graph with V vertices numbered from 0 to V-1 and E edges, represented as a 2D array edges[][], where each element edges[i] = [u, v] represents an undirected edge between vertices u and v.

    // Your task is to find the shortest path distance from a given source vertex src to all other vertices in the graph.
    // If a vertex is not reachable from the source, return -1 for that vertex.

    // Note: All edges have unit weight (1).

    //     Input: V = 9, E = 10,
    // edges[][] = [[0, 1], [0, 3], [1, 2], [3, 4], [4, 5], [2, 6], [5, 6], [6, 7], [6, 8], [7, 8]], src = 0
    // Output: [0, 1, 2, 1, 2, 3, 3, 4, 4]

    int vertices, edges, src;
    cin >> vertices >> edges >> src;

    int u, v;
    vector<vector<int>> edgesArr(edges);

    for (int i = 0; i < edges; i++)
    {
        cin >> u >> v;
        edgesArr[i].push_back(u);
        edgesArr[i].push_back(v);
    }

    vector<int> sp = shortestPath(vertices, edgesArr, src);

    cout << "shortest paths " << endl;
    for (int x : sp)
    {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}

vector<int> shortestPath(int V, vector<vector<int>> &edges, int src)
{
    // code here
    vector<int> d(V, -1);
    vector<bool> visited(V, false);

    vector<vector<int>> adj(V);

    for (int i = 0; i < edges.size(); i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    augumentedBfs(adj, src, visited, d);

    return d;
}

void augumentedBfs(vector<vector<int>> &adj, int src, vector<bool> &visited, vector<int> &d)
{
    queue<int> q;
    d[src] = 0;
    visited[src] = true;

    q.push(src);

    while (!q.empty())
    {
        int vertex = q.front();
        q.pop();

        for (int x : adj[vertex])
        {
            if (!visited[x])
            {
                visited[x] = true;
                d[x] = d[vertex] + 1;
                q.push(x);
            }
        }
    }
}
