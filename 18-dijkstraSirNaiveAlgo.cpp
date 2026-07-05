#include <iostream>
#include <vector>
#include <utility>

using namespace std;

vector<int> dijkstra(int V, vector<vector<int>> &edges, int src);

int main()
{

    //     Given an undirected, weighted graph with V vertices numbered from 0 to V-1 and E edges, represented by 2d array edges[][], where edges[i]=[u, v, w] represents the edge between the nodes u and v having w edge weight.
    // You have to find the shortest distance of all the vertices from the source vertex src, and return an array of integers where the ith element denotes the shortest distance between ith node and source vertex src.

    // Note: The Graph is connected and doesn't contain any negative weight edge.
    // It is guaranteed that all the shortest distance will fit in a 32-bit integer.

    // Examples:

    // Input: V = 3, edges[][] = [[0, 1, 1], [1, 2, 3], [0, 2, 6]], src = 2
    // Output: [4, 3, 0]

    //     Input: V = 5, edges[][] = [[0, 1, 4], [0, 2, 8], [1, 4, 6], [2, 3, 2], [3, 4, 10]], src = 0
    // Output: [0, 4, 8, 10, 10]

    int v, e, src;

    cin >> v >> e >> src;

    vector<vector<int>> edges(e);

    int a, b, w;
    for (int i = 0; i < e; i++)
    {
        cin >> a >> b >> w;
        edges[i].push_back(a);
        edges[i].push_back(b);
        edges[i].push_back(w);
    }

    vector<int> sp = dijkstra(v, edges, src);

    for (int x : sp)
    {
        cout << x << " ";
    }

    cout << endl;

    return 0;
}

vector<int> dijkstra(int V, vector<vector<int>> &edges, int src)
{
    // Code here

    //create adjacency list
    vector<vector<pair<int, int>>> adj(V);

    for (int i = 0; i < edges.size(); i++)
    {
        int a = edges[i][0];
        int b = edges[i][1];
        int w = edges[i][2];

        adj[a].push_back({b, w});
        adj[b].push_back({a, w});
    }

    //-1 here indicates the infinity not reachable
    vector<int> d(V, -1);

    vector<int> a(V, -1);

    a[src] = 0;

    int minInd = src;

    while (minInd != -1)
    {

        //setting the shortest path
        int sp = a[minInd];
        d[minInd] = sp;

        for (pair<int, int> p : adj[minInd])
        {

            int u = p.first;
            int w = p.second;

            int currDist = a[u];

            //infinity or its greater
            if (currDist == -1 || currDist > (w + sp))
            {
                a[u] = w + sp;
            }
        }

        //resetting minInd to -1
        minInd = -1;

        //finding the next minimum index
        for (int i = 0; i < V; i++)
        {

            bool isVertexValid = a[i] != -1 && d[i] == -1;

            if (isVertexValid)
            {
                minInd = minInd == -1 || a[minInd] > a[i] ? i : minInd;
            }
        }
    }

    return d;
}
