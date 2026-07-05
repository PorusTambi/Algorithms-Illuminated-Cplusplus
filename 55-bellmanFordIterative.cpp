
#include <iostream>
#include <vector>

using namespace std;

int infiniteVal = 100000000;
vector<int> bellmanFord(int V, vector<vector<int>> &edges, int src);

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

    ////iterative + reconstruction + stable
    //set it to infiniteVal for everyone denoting infinity
    vector<vector<int>> memo(V + 1, vector<int>(V, infiniteVal));
    vector<int> parent(V, -1);

    //base case initialization
    //set to src=0;
    memo[0][src] = 0;

    //used to early exit algo
    //if for all vertices shortest paths with at most i+1 edges equal correponding with i edges
    //then we can do early exit
    bool stable;

    for (int i = 1; i <= V; i++)
    {

        stable = true;

        //we have to find shortest path for i>=1

        //if src!=b then edge must be there to connect it

        //hence we get min of all edges in indegree of v

        //if src ==b then I can reach in 0 weight or there is a negative or positive cycle around src

        //base val set for src=b
        memo[i][src] = 0;
        //if there is a negative cycle at src , below for loop over all edges will cater it

        //rest all can be calculated via edges
        //if no edge its already infinity intialized in top

        //this is same as taking min over all indegree of v for all v
        //just a simple way of doing this
        for (int j = 0; j < edges.size(); j++)
        {

            int a = edges[j][0];
            int b = edges[j][1];
            int w = edges[j][2];

            int aVal = memo[i - 1][a];

            //to handle cases for example infinity-2 to remain infinity
            if (aVal != infiniteVal)
            {
                if ((aVal + w) < memo[i][b])
                {
                    memo[i][b] = aVal + w;
                    parent[b] = a;
                }
            }

            //Once memo[i-1][b] is greater than memo[i][b] stable is false
            //in future memo[i][b] can remain same or decrease
            if (memo[i - 1][b] > memo[i][b])
            {
                stable = false;
            }
        }

        if (stable)
        {
            return memo[i];
        }
    }

    //negative cycle as not stable
    return {-1};
}
