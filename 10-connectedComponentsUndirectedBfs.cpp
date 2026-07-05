#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> getComponents(int V, vector<vector<int>> &edges);
vector<int> bfs(vector<vector<int>> &adj, int src, vector<bool> &visited);

int main()
{

    //     Given an undirected graph with V vertices numbered from 0 to V-1 and E edges, represented as a 2D array edges[][], where each entry edges[i] = [u, v] denotes an edge between vertices u and v.

    // Your task is to return a list of all connected components. Each connected component should be represented as a list of its vertices, with all components returned in a collection where each component is listed separately.

    // Note: You can return the components in any order, driver code will print the components in sorted order.

    // Examples :

    // Input: V = 5, edges[][] = [[0, 1], [2, 1], [3, 4]]
    // Output: [[0, 1, 2], [3, 4]]

    int vertices, edges;
    cin >> vertices >> edges;

    int u, v;
    vector<vector<int>> edgesArr(edges);

    for (int i = 0; i < edges; i++)
    {
        cin >> u >> v;
        edgesArr[i].push_back(u);
        edgesArr[i].push_back(v);
    }

    vector<vector<int>> compo = getComponents(vertices, edgesArr);

    cout << "All components " << endl;
    int i = 0;
    for (vector<int> c : compo)
    {
        cout << "Component " << i + 1 << "----";
        for (int x : c)
        {
            cout << x << " ";
        }
        i += 1;
        cout << endl;
    }

    return 0;
}

vector<vector<int>> getComponents(int V, vector<vector<int>> &edges)
{
    // code here
    vector<vector<int>> adj(V);
    vector<bool> visited(V, false);
    vector<vector<int>> res;

    for (int i = 0; i < edges.size(); i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 0; i < V; i++)
    {
        if (!visited[i])
        {
            vector<int> comp = bfs(adj, i, visited);
            res.push_back(comp);
        }
    }

    return res;
}

vector<int> bfs(vector<vector<int>> &adj, int src, vector<bool> &visited)
{
    vector<int> res;
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

    return res;
}
