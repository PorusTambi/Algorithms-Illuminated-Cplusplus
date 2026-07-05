
#include <iostream>
#include <vector>

using namespace std;

int infiniteVal = 100000000;
vector<int> bellmanFord(int V, vector<vector<int>> &edges, int src);
int dpSp(int src, int v, int i, vector<vector<pair<int, int>>> &indegAdj,
         vector<vector<int>> &memo, vector<int> &parent);

int main()
{
    //    Geeks for geeks - Bellman-Ford
    // Given an weighted graph with V vertices numbered from 0 to V-1 and E edges, represented by a 2d array edges[][], where edges[i] = [u, v, w] represents a direct edge from node u to v having w edge weight. You are also given a source vertex src.

    // Your task is to compute the shortest distances from the source to all other vertices. If a vertex is unreachable from the source, its distance should be marked as 108. Additionally, if the graph contains a negative weight cycle, return [-1] to indicate that shortest paths cannot be reliably computed.

    // Examples:

    // Input: V = 5, edges[][] = [[1, 3, 2], [4, 3, -1], [2, 4, 1], [1, 2, 1], [0, 1, 5]], src = 0

    // Output: [0, 5, 6, 6, 7]
    // Explanation: Shortest Paths:
    // For 0 to 1 minimum distance will be 5. By following path 0 → 1
    // For 0 to 2 minimum distance will be 6. By following path 0 → 1  → 2
    // For 0 to 3 minimum distance will be 6. By following path 0 → 1  → 2 → 4 → 3
    // For 0 to 4 minimum distance will be 7. By following path 0 → 1  → 2 → 4

    // Input: V = 4, edges[][] = [[0, 1, 4], [1, 2, -6], [2, 3, 5], [3, 1, -2]], src = 0
    // Output: [-1]
    // Explanation: The graph contains a negative weight cycle formed by the path 1 → 2 → 3 → 1, where the total weight of the cycle is negative.
    // Constraints:
    // 1 ≤ V ≤ 100
    // 1 ≤ E = edges.size() ≤ V*(V-1)
    // -1000 ≤ w ≤ 1000
    // 0 ≤ src < V

    int V, E, src;
    cin >> V >> E >> src;

    vector<vector<int>> edges(E, vector<int>(3, 0));

    for (int i = 0; i < E; i++)
    {
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
    }

    vector<int> sp = bellmanFord(V, edges, src);

    cout << "shortest paths " << endl;
    for (int x : sp)
    {
        cout << x << " ";
    }

    cout << endl;

    return 0;
}

vector<int> bellmanFord(int V, vector<vector<int>> &edges, int src)
{

    //recursive + reconstruction

    //if some val is INT_MIN that means that value is not yet calculated
    //as per problem contraints its safe because no path will ever reach INT_MIN
    vector<vector<int>> memo(V + 1, vector<int>(V, INT_MIN));
    vector<int> parent(V, -1);

    //base cases initialization
    //with 0 edges only memo src = 0 rest all infinity
    for (int i = 0; i < V; i++)
    {
        memo[0][i] = infiniteVal;
    }
    memo[0][src] = 0;

    //prepare indegree adjacency list
    vector<vector<pair<int, int>>> indegAdj(V);

    for (int i = 0; i < edges.size(); i++)
    {

        int a = edges[i][0];
        int b = edges[i][1];
        int w = edges[i][2];

        indegAdj[b].push_back({a, w});
    }

    for (int atMostEdgeCnt = V - 1; atMostEdgeCnt <= V; atMostEdgeCnt++)
    {
        //calculate with atmost V-1 and V edges so we can compare later to detect negative cycle

        for (int i = 0; i < V; i++)
        {
            int vertex = i;
            dpSp(src, vertex, atMostEdgeCnt, indegAdj, memo, parent);
        }
    }

    for (int i = 0; i < V; i++)
    {

        if (memo[V - 1][i] != memo[V][i])
        {
            //this denotes negative weight cycle
            return {-1};
        }
    }

    return memo[V - 1]; // return the one with V-1 edges at most if no negative cycle
}

//dpSp is dynamic programming shortest path
int dpSp(int src, int v, int i, vector<vector<pair<int, int>>> &indegAdj,
         vector<vector<int>> &memo, vector<int> &parent)
{

    //not INT_MIN suggests its not calculated yet
    if (memo[i][v] != INT_MIN)
    {
        return memo[i][v];
    }

    //since i=0 is base case which will return from 1st

    //we have to find shortest path for i>=1

    //if src!=v then edge must be there to connect it

    //hence we get min of all edges in indegree of v

    //if src ==v then I can reach in 0 weight or there is a negative or positive cycle around src

    //base val to compare to

    int baseVal = src != v ? infiniteVal : 0;

    int val = baseVal;

    for (auto p : indegAdj[v])
    {
        int u = p.first;
        int w = p.second;

        int uVal = dpSp(src, u, i - 1, indegAdj, memo, parent);

        //we should check this otherwise for example infinity -2 will be set incorrectly
        if (uVal != infiniteVal)
        {

            if (uVal + w < val)
            {
                val = uVal + w;
                parent[v] = u;
            }
        }
    }

    memo[i][v] = val;

    return memo[i][v];
}
