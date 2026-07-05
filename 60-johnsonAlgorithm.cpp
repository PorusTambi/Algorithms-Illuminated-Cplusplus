#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int infinity = 100000000;

void johnsonAlgo(vector<vector<int>> &dist);
vector<int> bellmanFord(int src, vector<vector<int>> &edges, int vertices);
vector<vector<pair<int, int>>> transformGraphForDijkstra(vector<vector<int>> &edges, vector<int> &d, int vertices);
vector<int> dijkstra(vector<vector<pair<int, int>>> &adj, int src, int vertices);

int main()
{
    //   Geeks for geeks -  Floyd Warshall
    // You are given a weighted directed graph, represented by an adjacency matrix, dist[][] of size n x n, where dist[i][j] represents the weight of the edge from node i to node j. If there is no direct edge, dist[i][j] is set to a large value (i.e., 108) to represent infinity.
    // The graph may contain negative edge weights, but it does not contain any negative weight cycles.

    // Your task is to find the shortest distance between every pair of nodes i and j in the graph.

    // Note: Modify the distances for every pair in place.

    // Examples :

    // Input: dist[][] = [[0, 4, 10^8, 5, 10^8], [10^8, 0, 1, 10^8, 6], [2, 10^8, 0, 3, 10^8], [10^8, 10^8, 1, 0, 2], [1, 10^8, 10^8, 4, 0]]

    // Output: [[0, 4, 5, 5, 7], [3, 0, 1, 4, 6], [2, 6, 0, 3, 5], [3, 7, 1, 0, 2], [1, 5, 5, 4, 0]]

    // Explanation: Each cell dist[i][j] in the output shows the shortest distance from node i to node j, computed by considering all possible intermediate nodes.

    // Input: dist[][] = [[0, -1, 2], [1, 0, 10^8], [3, 1, 0]]
    // Output: [[0, -1, 2], [1, 0, 3], [2, 1, 0]]
    // Explanation: Each cell dist[i][j] in the output shows the shortest distance from node i to node j, computed by considering all possible intermediate nodes.
    // From 2 to 0 shortest distance should be 2 by following path 2 -> 1 -> 0
    // From 1 to 2 shortest distance should be 3 by following path 1 -> 0 -> 2

    // Constraints:
    // 1 ≤ dist.size() ≤ 100
    // -1000 ≤ dist[i][j] ≤ 1000
    // dist[i][j] can be 108 to represent infinity.

    int v;

    cin >> v;

    vector<vector<int>> dist(v, vector<int>(v, 0));

    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < v; j++)
        {
            cin >> dist[i][j];
        }
    }

    johnsonAlgo(dist);

    cout << "all pairs shortest paths " << endl;
    for (auto x : dist)
    {

        for (int y : x)
        {
            cout << y << " ";
        }
        cout << endl;
    }

    return 0;
}

struct cmp
{

    bool operator()(pair<int, int> &a, pair<int, int> &b)
    {

        return a.second > b.second;
    }
};
void johnsonAlgo(vector<vector<int>> &dist)
{

    //johnson algorithm - 4th

    int v = dist.size();

    //new source as 0 to v-1 already there I pick v
    int ns = v;

    vector<vector<int>> edges;

    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < v; j++)
        {
            if (dist[i][j] != infinity)
            {
                edges.push_back({i, j, dist[i][j]});
            }
        }
    }

    //new edge of weight 0 from new source to every vertex
    //so that everything is reachable from newSource and we can stop early by bellman ford if negative cycle in graph
    for (int i = 0; i < v; i++)
    {
        edges.push_back({ns, i, 0});
    }

    //run bellman ford to get vertex weights for transforming all edge weights to >=0
    //so that dijikstra can be applied n times

    //shortest path from ns newSource to all v
    int vertices = v + 1;
    vector<int> d = bellmanFord(ns, edges, vertices);

    if (d.size() == 1 && d[0] == -1)
    {
        cout << "negative cycle";
        return;
    }

    //after this d gets populated

    //adjancency list representation of new graph with manipulated edge lengths
    vector<vector<pair<int, int>>> adj = transformGraphForDijkstra(edges, d, vertices);

    //run dijkstra with each vertex as source
    for (int i = 0; i < v; i++)
    {

        vector<int> currD = dijkstra(adj, i, v);

        for (int j = 0; j < v; j++)
        {
            int val = currD[j];
            //transform shortest path again, so that it represents shortest path val in original graph G
            int actual = val == infinity ? val : val + d[j] - d[i];
            dist[i][j] = actual;
        }
    }
}

vector<int> bellmanFord(int src, vector<vector<int>> &edges, int vertices)
{

    vector<int> d(vertices, infinity);

    d[src] = 0;

    bool stable = true;

    for (int k = 1; k <= vertices; k++)
    {
        stable = true;

        for (auto e : edges)
        {
            int i = e[0];
            int j = e[1];
            int w = e[2];

            int val = d[i] == infinity ? infinity : d[i] + w;

            if (val < d[j])
            {
                stable = false;
                d[j] = val;
            }
        }

        if (stable)
        {
            return d;
        }
    }

    return {-1};
}

vector<vector<pair<int, int>>> transformGraphForDijkstra(vector<vector<int>> &edges, vector<int> &d, int vertices)
{

    //as new source will not be there in graph, it was only for reachability
    int v = vertices - 1;

    vector<vector<pair<int, int>>> adj(v);

    for (auto e : edges)
    {

        int i = e[0];
        int j = e[1];
        int w = e[2];

        //ignore new source outgoing edges
        if (i != v)
        {
            //reweighting to make all edge weights greater than equal to 0
            int newWt = w + d[i] - d[j];
            adj[i].push_back({j, newWt});
        }
    }

    return adj;
}

vector<int> dijkstra(vector<vector<pair<int, int>>> &adj, int src, int vertices)
{

    vector<int> d(vertices, infinity);

    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;

    pq.push({src, 0});

    while (!pq.empty())
    {

        auto top = pq.top();
        pq.pop();

        int u = top.first;
        int sp = top.second;

        if (d[u] == infinity)
        {
            d[u] = sp;

            for (auto x : adj[u])
            {

                int a = x.first;
                int w = x.second;

                if (d[a] == infinity)
                {
                    pq.push({a, sp + w});
                }
            }
        }
    }

    return d;
}
