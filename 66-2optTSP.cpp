#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> nearestNeighbourTour(vector<vector<int>> &adjMatrix);
vector<pair<int, int>> getEdgesInCyclicManner(vector<vector<int>> &tspTour);
bool isImproving2Change(vector<vector<int>> &adjMatrix, int a, int b, int c, int d);
vector<int> getImproving2Change(vector<vector<int>> &adjMatrix, vector<vector<int>> &tspTour);
void removeAndAddVertex(vector<vector<int>> &tspTour, int v, int remove, int add);
vector<vector<int>> getTspTour(vector<vector<int>> &adjMatrix);
void printTspTourAndCost(vector<vector<int>> &adjMatrix, vector<vector<int>> &tspTour);

int main()
{

    //sample i/p
    //     5
    // 0 1 4 5 10
    // 1 0 2 6 3
    // 4 2 0 7 8
    // 5 6 7 0 9
    // 10 3 8 9 0

    //sample o/p
    //     starting tour ----------------------
    // 0 1 2 3 4 0 The final cost 29
    //  ----------------------------------

    // Decrease by 2Change (0, 1)  (3, 4)  = 2
    // Decrease by 2Change (0, 4)  (1, 2)  = 3

    // Final tsp tour ------------------------------
    // 0 3 2 4 1 0 The final cost 24
    // --------------------------------

    //i/p is complete graph undirected with edge weights
    //since I can reach anywhere from a vertex its complete, better to store as adjacency matrix

    //number of vertices;
    int n;
    cin >> n;

    //adjacency matrix storing weights of all
    vector<vector<int>> adjMatrix(n, vector<int>(n, 0));

    //think simply user will give adjacency matrix as input with weights
    //edge v,v will always be given weight 0
    //user should make sure to put cost of a b and b a same
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> adjMatrix[i][j];
        }
    }

    vector<vector<int>> tspTour = getTspTour(adjMatrix);

    cout << endl
         << endl
         << "Final tsp tour ------------------------------" << endl;

    printTspTourAndCost(adjMatrix, tspTour);

    cout << "--------------------------------" << endl
         << endl;

    return 0;
}

vector<vector<int>> nearestNeighbourTour(vector<vector<int>> &adjMatrix)
{
    //this is a greedy heuristic algorithm
    //this takes somewhat motivation from Prim's algorithm for MST
    //this is used to get a starting tour , where we would apply 2 change algo

    int n = adjMatrix[0].size();

    //vector telling which vertices are done
    vector<bool> done(n, false);

    //why I represent a tour like this ?
    //this I figured out while thinking of implementing 2 change
    //each vertex index gets exactly 2 length array
    //one outgoing one incoming vertex
    vector<vector<int>> tspTour(n);

    //select any arbitrary vertex as start, we are selecting 0
    //selcting different starting vertices, may give different cost tours
    int start = 0;

    int vertex = start;
    bool isTourComplete = false;

    int cost = 0;

    while (!isTourComplete)
    {
        //mark it as done
        done[vertex] = true;

        //select the nearest neighbour for this vertex that is not yet done
        int vertexSelected = -1;

        //find nearest neighbour
        for (int i = 0; i < n; i++)
        {
            if (i != vertex && !done[i])
            {

                if (vertexSelected == -1 || adjMatrix[vertex][i] < adjMatrix[vertex][vertexSelected])
                {
                    vertexSelected = i;
                }
            }
        }

        if (vertexSelected == -1)
        {
            //this means all done, we have to return back to start
            vertexSelected = start;

            //set tour to complete, so loop breaks in next
            isTourComplete = true;
        }

        //set outgoing from vertex
        tspTour[vertex].push_back(vertexSelected);

        //set incoming of vertexSelected
        tspTour[vertexSelected].push_back(vertex);

        cost += adjMatrix[vertex][vertexSelected];

        //next vertex is vertexSelected
        vertex = vertexSelected;
    }

    //this function overall takes
    //theta(n) time in finding each min, for n vertices hence theta(n^2) time
    return tspTour;
}

vector<pair<int, int>> getEdgesInCyclicManner(vector<vector<int>> &tspTour)
{
    //this may return in clockwise or anti clock manner, in any one type
    //actually we need in cyclic manner , clock or anti-clock not matter

    int n = tspTour.size();

    vector<pair<int, int>> edges;

    //we can take any vertex as start
    int curr = 0;

    //clever logic to select not visited vertices
    int prev = tspTour[curr][1];

    int count = 0;

    while (count < n)
    {
        int a = curr;

        //clever logic to select not visited vertex
        int b = tspTour[curr][0] + tspTour[curr][1] - prev;

        edges.push_back({a, b});

        curr = b;
        prev = a;

        count += 1;
    }

    //this function runs in theta(n) time

    return edges;
}

bool isImproving2Change(vector<vector<int>> &adjMatrix, int a, int b, int c, int d)
{

    if (a == c || a == d || b == c || b == d)
    {
        //endpoints share, its invalid 2 swap will not result in tour/cycle
        return false;
    }

    //since edges were in cyclic manner a b and then c d
    //then swap will be a c and b d

    int prevSum = adjMatrix[a][b] + adjMatrix[c][d];

    int newSum = adjMatrix[a][c] + adjMatrix[b][d];

    //if newSum less than previous then its improving
    return newSum < prevSum;

    //this function runs in theta(1) time
}

vector<int> getImproving2Change(vector<vector<int>> &adjMatrix, vector<vector<int>> &tspTour)
{
    int n = adjMatrix[0].size();

    //check if the given tour has any improving 2 change
    //meaning if selecting 2 edges then swapping it with 2 different edges can reduce the total cost of tour
    //return 4 endpoint a,b c,d of 2 edges which are improving

    //if no improving tour this function returns empty array

    //first I should get all edges in cyclic manner

    //below line runs in theta(n)
    vector<pair<int, int>> edgesCyclic = getEdgesInCyclicManner(tspTour);

    //select all pair of edges, discard those pair which share endpoints
    //this will give me all possibilites to check

    //basic way to select all, there will be n edges in a cycle

    //loop runs in theta(n^2)
    for (int i = 0; i < n; i++)
    {
        //edge 1 first point
        int a = edgesCyclic[i].first;

        //edge 1 second point
        int b = edgesCyclic[i].second;

        for (int j = i + 1; j < n; j++)
        {

            int c = edgesCyclic[j].first;
            int d = edgesCyclic[j].second;

            if (isImproving2Change(adjMatrix, a, b, c, d))
            {
                return {a, b, c, d};
            }
        }
    }

    //this complete function takes theta(n^2)

    return {};
}

void removeAndAddVertex(vector<vector<int>> &tspTour, int v, int remove, int add)
{
    //given vertex v remove vertex remove from its list and add vertex add
    //clever trick by add/sub
    tspTour[v][0] = tspTour[v][0] + tspTour[v][1] - remove;
    tspTour[v][1] = add;
}

vector<vector<int>> getTspTour(vector<vector<int>> &adjMatrix)
{

    //get the starting tour, runs in theta(n^2)
    vector<vector<int>> tspTour = nearestNeighbourTour(adjMatrix);

    cout << endl
         << endl
         << "starting tour ----------------------" << endl;

    //runs in theta(n)
    printTspTourAndCost(adjMatrix, tspTour);
    cout << " ----------------------------------" << endl
         << endl;

    //runs in theta(n^2)
    vector<int>
        twoChange = getImproving2Change(adjMatrix, tspTour);

    //each iteration runs in theta(n^2)
    //until improving two change
    while (twoChange.size() != 0)
    {

        int a = twoChange[0];
        int b = twoChange[1];
        int c = twoChange[2];
        int d = twoChange[3];

        //since we always get in cyclic manner a,b c,d
        //hence it will always swap in a,c b,d

        int prevSum = adjMatrix[a][b] + adjMatrix[c][d];
        int newSum = adjMatrix[a][c] + adjMatrix[b][d];

        int costDecrease = prevSum - newSum;

        cout << "Decrease by 2Change "
             << "(" << a << ", " << b << ")"
             << "  "
             << "(" << c << ", " << d << ")"
             << "  = " << costDecrease << endl;

        removeAndAddVertex(tspTour, a, b, c);

        //for b remove a add d
        removeAndAddVertex(tspTour, b, a, d);

        //for c remove d add a
        removeAndAddVertex(tspTour, c, d, a);

        //for d remove c add b
        removeAndAddVertex(tspTour, d, c, b);

        //again check for improving twoChange
        twoChange = getImproving2Change(adjMatrix, tspTour);
    }

    //this complete functions runs in theta(n^2) + theta(number of iteration * n^2)
    //number of iterations can be exponential in worst case, if not this problem can't be NP hard

    return tspTour;
}

void printTspTourAndCost(vector<vector<int>> &adjMatrix, vector<vector<int>> &tspTour)
{

    int n = adjMatrix[0].size();
    int cost = 0;

    vector<pair<int, int>> edgesCyclic = getEdgesInCyclicManner(tspTour);

    int start = edgesCyclic[0].first;

    for (int i = 0; i < n; i++)
    {
        int a = edgesCyclic[i].first;
        int b = edgesCyclic[i].second;

        cout << a << " ";

        cost += adjMatrix[a][b];
    }

    //to complete cycle
    cout << start << " ";

    cout << "The final cost " << cost << endl;
}