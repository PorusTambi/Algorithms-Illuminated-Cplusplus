#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector<int> topoSort(int V, vector<vector<int>> &edges);
void dfsPluckSinkIterative(vector<vector<int>> &adj, vector<bool> &visited, int src, vector<int> &res, int &currIndex);

int main()
{

    //     Given a Directed Acyclic Graph (DAG) of V (0 to V-1) vertices and E edges represented as a 2D list of edges[][], where each entry edges[i] = [u, v] denotes a directed edge u -> v. Return the topological sort for the given graph.

    // Topological sorting for Directed Acyclic Graph (DAG) is a linear ordering of vertices such that for every directed edge u -> v, vertex u comes before v in the ordering.
    // Note: As there are multiple Topological orders possible, you may return any of them
    //Input: V = 4, E = 3, edges[][] = [[3, 0], [1, 0], [2, 0]]
    //     Output:  Few valid Topological orders for the given graph are:
    // [3, 2, 1, 0]
    // [1, 2, 3, 0]
    // [2, 3, 1, 0]

    int vertices, edges;

    cin >> vertices >> edges;

    vector<vector<int>> edgesArr(edges);

    int u, v;

    for (int i = 0; i < edges; i++)
    {
        cin >> u >> v;
        edgesArr[i].push_back(u);
        edgesArr[i].push_back(v);
    }
    vector<int> topoOrder = topoSort(vertices, edgesArr);

    cout << "topological order " << endl;

    for (int x : topoOrder)
    {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}

vector<int> topoSort(int V, vector<vector<int>> &edges)
{
    // code here

    vector<vector<int>> adj(V);

    for (int i = 0; i < edges.size(); i++)
    {
        int a = edges[i][0];
        int b = edges[i][1];

        adj[a].push_back(b);
    }

    vector<int> res(V);
    int currIndex = V - 1;

    vector<bool> visited(V, false);

    for (int i = 0; i < V; i++)
    {

        if (!visited[i])
        {
            dfsPluckSinkIterative(adj, visited, i, res, currIndex);
        }
    }

    return res;
}
void dfsPluckSinkIterative(vector<vector<int>> &adj, vector<bool> &visited, int src, vector<int> &res, int &currIndex)
{

    stack<pair<int, int>> s;

    s.push({src, -1});

    while (!s.empty())
    {

        int vertex = s.top().first;
        int &listInd = s.top().second;
        int vListSize = adj[vertex].size();

        //marking vertex as visited
        visited[vertex] = true;

        if (listInd == vListSize - 1)
        {
            //all children are completed
            res[currIndex] = vertex;
            currIndex -= 1;
            s.pop();
        }

        else
        {
            //find the next in adjaceny list and push
            for (int i = listInd + 1; i < vListSize; i++)
            {
                int u = adj[vertex][i];
                if (!visited[u])
                {
                    listInd = i; //this updates in stack as well as listInd was a reference
                    s.push({u, -1});
                    //next time it will continue from here
                    break;
                }
                else
                {
                    listInd = i;
                }
            }
        }
    }
}
