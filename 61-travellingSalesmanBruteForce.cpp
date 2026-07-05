#include <iostream>
#include <utility>
#include <vector>

using namespace std;
void tsp(int src, int n, int vertices, int cost, vector<int> &doneOrder, vector<vector<int>> &adjMatrix, int &optCost, vector<int> &optOrder);
int main()
{

    //i/p
    //4
    // 0 1 4 3
    // 1 0 5 2
    // 4 5 0 6
    // 3 2 6 0

    //o/p
    //     Min tour value 13
    // Actual tour
    // 0 1 3 2

    int n;
    cin >> n;

    //taking the graph as adjacency matrix as the graph is complete undirected graph
    vector<vector<int>> adjMatrix(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> adjMatrix[i][j];
        }
    }

    //to keep track of which vertices in path we already selected and in which order, so it not loops back to them
    vector<int> doneOrder(n, -1);

    //optOrder[i] represents which vertex comes at ith position in tour
    vector<int> optOrder(n, -1);
    int optCost = INT_MAX;

    //since a tour is a cycle we can start from any point , I am starting from 0
    int src = 0;
    int cost = 0;
    tsp(src, n, n, cost, doneOrder, adjMatrix, optCost, optOrder);

    cout << "Min tour value " << optCost << endl;

    cout << "Actual tour " << endl;

    for (int x : optOrder)
    {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}

void tsp(int src, int n, int vertices, int cost, vector<int> &doneOrder, vector<vector<int>> &adjMatrix, int &optCost, vector<int> &optOrder)
{

    //make it doneOrder to a number other than -1 , so its not selected in dfs down again
    doneOrder[src] = vertices - n;

    //base case
    if (n == 1)
    {
        //since n is 1 its last so we have to go back to start which is 0
        int currCost = cost + adjMatrix[0][src];

        if (optCost > currCost)
        {
            //if optimal cost is bigger than currCost
            //set optimal cost to current cost
            optCost = currCost;

            //and also set optimal done order to this done order

            for (int i = 0; i < vertices; i++)
            {
                //optOrder[i] represents which vertex comes at ith position in tour
                int vertex = i;
                int position = doneOrder[vertex];
                optOrder[position] = vertex;
            }
        }
    }

    else
    {

        for (int u = 0; u < vertices; u++)
        {

            //if not done
            //this is trying all possibilities
            if (doneOrder[u] == -1)
            {
                int w = adjMatrix[src][u];
                int currCost = cost + w;
                tsp(u, n - 1, vertices, currCost, doneOrder, adjMatrix, optCost, optOrder);
            }
        }
    }

    //making done false so that it when backtracks it can be selected again
    doneOrder[src] = -1;

    return;
}
