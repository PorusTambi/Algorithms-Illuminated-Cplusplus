#include <iostream>
#include <vector>

using namespace std;

int infinity = 100000000;

void floydWarshall(vector<vector<int>> &dist);
void setShortestPath(int v, int w, int k,
                     vector<int> &parent,
                     vector<vector<vector<int>>> &memo);

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

    floydWarshall(dist);

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

void floydWarshall(vector<vector<int>> &dist)
{

    //iterative + reconstruction - 2nd solution
    // Code here

    int v = dist.size();

    //3d array
    vector<vector<vector<int>>> memo(v + 1, vector<vector<int>>(v, vector<int>(v, INT_MIN)));

    //base case when k=0 no intermediate vertices
    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < v; j++)
        {
            memo[0][i][j] = dist[i][j];
        }
    }

    for (int k = 1; k <= v; k++)
    {

        for (int i = 0; i < v; i++)
        {

            for (int j = 0; j < v; j++)
            {

                int u = k - 1;

                int m1 = memo[k - 1][i][j];

                if (u == i || u == j)
                {
                    memo[k][i][j] = m1;
                }

                else
                {

                    int m2 = memo[k - 1][i][u];
                    int m3 = memo[k - 1][u][j];
                    int m4;

                    if (m2 == infinity || m3 == infinity)
                    {
                        m4 = infinity;
                    }
                    else
                    {
                        m4 = m2 + m3;
                    }

                    memo[k][i][j] = min(m1, m4);
                }
            }
        }
    }

    //check if negative cycle
    for (int i = 0; i < v; i++)
    {
        if (memo[v][i][i] < 0)
        {
            cout << "negative cycle exist " << endl;
            return;
        }
    }

    //copying of values
    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < v; j++)
        {
            dist[i][j] = memo[v][i][j];
        }
    }

    cout << "shortest path 2 to 0 parent matrix" << endl;
    vector<int> parent(v, -1);

    setShortestPath(2, 0, v, parent, memo);

    for (int x : parent)
    {
        cout << x << " ";
    }

    // cout<<endl;
}

void setShortestPath(int v, int w, int k,
                     vector<int> &parent,
                     vector<vector<vector<int>>> &memo)
{
    int vertices = memo[0][0].size();

    if (memo[k][v][w] == infinity)
    {
        return;
    }

    else if (k == 0)
    {
        if (v != w)
        {
            parent[w] = v;
        }

        return;
    }

    int u = k - 1;

    int m1 = memo[k - 1][v][w];

    //falling in case 1
    if (u == v || u == w)
    {
        setShortestPath(v, w, k - 1, parent, memo);
        return;
    }

    int m2 = memo[k - 1][v][u];
    int m3 = memo[k - 1][u][w];

    int m4;

    if (m2 == infinity || m3 == infinity)
    {
        m4 = infinity;
    }

    else
    {
        m4 = m2 + m3;
    }

    //falling in case 1
    if (m1 < m4)
    {
        setShortestPath(v, w, k - 1, parent, memo);
        return;
    }

    //falling in case 2
    else
    {
        //call in reverse so that uth parent is not set to -1
        setShortestPath(u, w, k - 1, parent, memo);
        setShortestPath(v, u, k - 1, parent, memo);

        return;
    }
}
