#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<vector<int>> getAdjListUndirectedGraph();
vector<int> dfs(vector<vector<int>> &adj);
int main()
{

    //     Given a connected undirected graph containing V vertices represented by a 2-d adjacency list adj[][], where each adj[i] represents the list of vertices connected to vertex i. Perform a Depth First Search (DFS) traversal starting from vertex 0, visiting vertices from left to right as per the given adjacency list, and return a list containing the DFS traversal of the graph.

    // Note: Do traverse in the same order as they are in the given adjacency list.

    // Input: adj[][] = [[2, 3, 1], [0], [0, 4], [0], [2]]
    // Output: [0, 2, 4, 3, 1]
    // Explanation: Starting from 0, the DFS traversal proceeds as follows:
    // Visit 0 → Output: 0
    // Visit 2 (the first neighbor of 0) → Output: 0, 2
    // Visit 4 (the first neighbor of 2) → Output: 0, 2, 4
    // Backtrack to 2, then backtrack to 0, and visit 3 → Output: 0, 2, 4, 3
    // Finally, backtrack to 0 and visit 1 → Final Output: 0, 2, 4, 3, 1

    // Input: adj[][] = [[1, 2], [0, 2], [0, 1, 3, 4], [2], [2]]
    // Output: [0, 1, 2, 3, 4]
    // Explanation: Starting from 0, the DFS traversal proceeds as follows:
    // Visit 0 → Output: 0
    // Visit 1 (the first neighbor of 0) → Output: 0, 1
    // Visit 2 (the first neighbor of 1) → Output: 0, 1, 2
    // Visit 3 (the first neighbor of 2) → Output: 0, 1, 2, 3
    // Backtrack to 2 and visit 4 → Final Output: 0, 1, 2, 3, 4

    vector<vector<int>> adj = getAdjListUndirectedGraph();
    vector<int> res = dfs(adj);

    cout << "Dfs order " << endl;
    for (int u : res)
    {
        cout << u << " ";
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

vector<int> dfs(vector<vector<int>> &adj)
{
    // Code here

    int v = adj.size();
    vector<int> res;
    res.reserve(v);

    vector<bool> visited(v, false);

    stack<int> s;

    s.push(0);

    while (!s.empty())
    {
        int src = s.top();

        s.pop();

        if (!visited[src])
        {
            res.push_back(src);
            visited[src] = true;

            int len = adj[src].size() - 1;
            for (int i = len; i >= 0; i--)
            {
                s.push(adj[src][i]);
            }
        }
    }

    return res;
}
