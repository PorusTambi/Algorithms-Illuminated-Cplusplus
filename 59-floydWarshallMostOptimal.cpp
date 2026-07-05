#include <iostream>
#include <vector>

using namespace std;

int infinity = 100000000;

void floydWarshall(vector<vector<int>> &dist);

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

    //most optimal space and time - 3rd
    // Code here

    int v = dist.size();

    //dist already represents base case

    for (int k = 1; k <= v; k++)
    {

        for (int i = 0; i < v; i++)
        {

            for (int j = 0; j < v; j++)
            {

                int u = k - 1;

                //in kth iteration this is the value of k-1th iteration
                int m1 = dist[i][j];

                //start with u or end with u these are unchanged entries
                //that is not changing in k-1 and kth iteration
                if (u == i || u == j)
                {
                    dist[i][j] = m1;
                }

                else
                {

                    int m2 = dist[i][u];
                    int m3 = dist[u][j];

                    //both m2,m3 falls to unchanged entry
                    int m4;

                    if (m2 == infinity || m3 == infinity)
                    {
                        m4 = infinity;
                    }
                    else
                    {
                        m4 = m2 + m3;
                    }

                    dist[i][j] = min(m1, m4);
                }
            }
        }
    }

    //no negative cycle check as question already says no negative cycle
}