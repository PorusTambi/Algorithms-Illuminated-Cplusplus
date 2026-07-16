#include <iostream>
#include <vector>
#include <unordered_map>
#include <random>
#include <cmath>
using namespace std;
void assignColorsRandomly(vector<int> &colorsMap, int n, int k);
int getMinCostPanchromaticPath(vector<vector<pair<int, int>>> &adj,
                               int n, int k,
                               vector<int> &colorsMap, vector<int> &memo);

int removeColor(int currSubsetVal, int colorToRemove);
bool isColorPresentInSubset(int subsetVal, int color);

void reconstructPath(vector<vector<pair<int, int>>> &adj, int n, int k,
                     vector<int> &colorsMap, vector<int> &memo, vector<int> &path);

int main()
{

    // iterative + memoization implementation of color coding

    // sample input
    //     8
    // 10
    // 4
    // 0 1 1
    // 1 2 7
    // 2 3 9
    // 0 6 2
    // 1 7 8
    // 2 4 6
    // 3 5 5
    // 4 5 4
    // 5 6 3
    // 6 7 10

    // most optimal minCost 4 Path for above input = 6

    // Taking input as adjacency list

    // the number of vertices
    int n;

    // the number of edges
    int m;

    // the k in min cost k path
    int k;

    cin >> n >> m >> k;

    // pair contains vertex, weight
    vector<vector<pair<int, int>>> adj(n);

    // input all edges
    int a, b, w;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b >> w;

        // Pushing in both due to undirected graph
        adj[a].push_back({b, w});
        adj[b].push_back({a, w});
    }

    // for all analysis assume edges >= vertices

    // the colors map for vertices, mapping each vertex color
    vector<int> colorsMap(n, -1);

    double epowerk = exp(k);
    double pi = 3.141;
    double root2pik = sqrt(2 * pi * k);
    // this tells error probability is less than 0.01
    double delta = 0.01;

    double ln100 = log(1 / delta);

    // the number of times we will run this experiment of randomly assigning colors and finding min cost k path
    // translating things to integer
    // this is the formula for calculating number of trails required, if we want failure probability less than delta
    int t = (int)((epowerk / root2pik) * ln100);

    // t is O(e^k)

    // Think like god tells us that min cost k path ends with vertex v5
    // and before vertex v5 god tells us that v3 comes , suppose v5 is yellow
    // Now we have to find optimal path that ends with v3 containing all colors except yellow
    // this is optimal substructure
    // and our subproblems is Cj,S
    // that is optimal path containing all colors in set S exactly once and ends with vertex j
    // also Cj,S-{red,yellow} is same as Cj,S-{yellow, red}
    // this suggests overlapping subproblems
    // hence we are thinking of dynamic programming

    // since there are k colors and base case is subset of size 1
    // total possibilities = 2^k - 1  where -1 is for phi/empty subset
    int rows = (1 << k) - 1;

    // cols one for each vertex for a given subset
    int cols = n;

    // space taken is O(2^k * n)

    // since subsets are S={red,yellow} we have to map them to numbers to index in array
    // hence think of 1 to k colors as 1 to k bits of a binary number
    // whichever color is present mark its corresponding bit as 1

    // memoization table storing solution of each subproblem

    // vector<vector<int>>memo(rows, vector<int>(cols))
    // this vector of vector is a problem as there are pointers and each array is scattered
    // vector<vector<int>> memo(rows, vector<int>(cols, INT_MAX));
    // that is 0th array is contiguous,1st array is also contiguous
    // but 0 and 1 array scattered in memory, this creates more time to fetch something
    // and less cache locality, why not make it a single dimensional array, better cache locality
    vector<int> memo(rows * cols);

    // set the starting minCost to infinity
    // assume no path length is greater than or equal to INT_MAX
    // INT_MAX here denotes infinity
    int minCost = INT_MAX;

    // This will actually store the vertices in min cost k path
    vector<int> minCostKPath(k, -1);

    cout << "Trials required " << t << endl;

    // do this for all independent trails t times

    for (int i = 1; i <= t; i++)
    {
        cout << "Executing trial " << i << "----------------------------------" << endl;

        // assign colors randomly to each vertex from colors 1 to k
        // assignColorsRandomly runs in O(n) time
        assignColorsRandomly(colorsMap, n, k);

        // this getMinCostPanchromaticPath runs in O(2^k * m) time, see function for details
        int currCost = getMinCostPanchromaticPath(adj, n, k, colorsMap, memo);

        // only if currCost is lower save the path with yourself
        if (minCost > currCost)
        {
            minCost = currCost;
            // reconstructPath runs in O(k*m) time, see function for details
            reconstructPath(adj, n, k, colorsMap, memo, minCostKPath);
        }

        cout << "Min cost of trial " << i << " = " << minCost << endl;

        cout << "Trial " << i << " finished" << endl
             << endl;

        /// this loop runs t times, each iteration takes O(2^k * m) time
        // hence total time = O(2^k * m * t)
    }

    cout << endl
         << endl;

    cout
        << "Final min cost of " << k << " path achieved " << minCost << endl;
    cout << "The exact path " << endl;

    for (int a : minCostKPath)
    {
        cout << a << " ";
    }

    cout << endl;

    return 0;

    // so total time = t* 2^k * m = O(e^k * 2^k * m)
    // total space = O(2^k * n)
}

// assigns random color from 1 to k to each vetex uniformly and independently
// changes colorsMap in place
void assignColorsRandomly(vector<int> &colorsMap, int n, int k)
{
    random_device rd;

    mt19937 gen(rd());

    uniform_int_distribution<int> dist(1, k);

    for (int i = 0; i < n; i++)
    {
        colorsMap[i] = dist(gen);
    }

    // this function runs in O(n) time
}

// calculates min cost of panchromatic path
int getMinCostPanchromaticPath(vector<vector<pair<int, int>>> &adj,
                               int n, int k,
                               vector<int> &colorsMap, vector<int> &memo)
{
    // first think that for calculating our subproblem Cj,S we do Cj,(S- color of j)
    // Now S-(color of j) is always less than S
    // so if we do in ascending order starting from 1 color subset to (2^k - 1) where all colors are included we are done

    int allColorsSubset = (1 << k) - 1;

    // for all subsets
    for (int subsetVal = 1; subsetVal <= allColorsSubset; subsetVal++)
    {
        // for each vertex
        for (int i = 0; i < n; i++)
        {
            int currIndex = ((subsetVal - 1) * n) + i;

            int vertexColor = colorsMap[i];

            bool isVertexColorInSubset = isColorPresentInSubset(subsetVal, vertexColor);

            if (!isVertexColorInSubset)
            {
                // if vertex color is not in subset simply that Cj,S is infinity
                memo[currIndex] = INT_MAX;
            }
            else
            {

                // now we go for indegree of vertex i
                int minCost = INT_MAX;
                int newSubsetVal = removeColor(subsetVal, vertexColor);

                bool isSingleColorInSubset = newSubsetVal == 0;

                if (isSingleColorInSubset)
                {
                    // this is also a base case
                    // since vertex color in subset and single color in subset, cost is 0
                    memo[currIndex] = 0;
                }

                else
                {
                    int newSubsetValInd = newSubsetVal - 1;

                    for (auto p : adj[i])
                    {

                        int adjVertex = p.first;
                        int w = p.second;

                        int newIndex = (newSubsetVal - 1) * n + adjVertex;

                        // since newSubsetValInd is less than subsetValInd, this value is readily available at this time
                        int minSubpath = memo[newIndex];
                        int totalCost = minSubpath == INT_MAX ? INT_MAX : (minSubpath + w);
                        minCost = min(minCost, totalCost);
                    }

                    memo[currIndex] = minCost;
                }
            }
        }

        // so number of subsets is O(2^k)
        // for each subset consider all vertices
        // so total how many time loop run is submission of indegree of v for all v
        // and its 2* edges in undirected graph
        // inner loop runs 2*m times and for each run takes O(1) time
        // hence time to calculate O(2^k * m)
    }

    int finalMinCost = INT_MAX;
    int allColorsSubsetInd = allColorsSubset - 1;

    // to calculate final min cost iterate over Cj,allColorsSubset and find min

    for (int i = 0; i < n; i++)
    {
        int currIndex = (allColorsSubset - 1) * n + i;
        finalMinCost = min(memo[currIndex], finalMinCost);
    }

    // total takes O(2^k * m)

    return finalMinCost;
}

// check if the color is present in subset
bool isColorPresentInSubset(int subsetVal, int color)
{
    // check if color-1 bit is 1

    int rightShifted = subsetVal >> (color - 1);

    return (rightShifted & 1) > 0;
}

// removes a color from a subset and returns new subset val
int removeColor(int currSubsetVal, int colorToRemove)
{

    // think it does xor to clear that bit
    return currSubsetVal ^ (1 << (colorToRemove - 1));

    // since subset is k bit number k can be huge like 1 million bits
    // so any operation on k bit number takes O(k) time
    // but for simplicity we take k small and take it O(1)
}

// reconstruct the actual path from memo table
void reconstructPath(vector<vector<pair<int, int>>> &adj, int n, int k,
                     vector<int> &colorsMap, vector<int> &memo, vector<int> &path)
{

    // We can also cache the best selection of each subproblem
    // but I don't want to take extra space hence recalculating again by retracing the memo table

    // all colors subset
    int currSubsetVal = (1 << k) - 1;
    int endVertex = -1;
    int minCost = INT_MAX;

    // find the end vertex which gives min with all colors
    // that is min of Cj,S where S contains all colors

    // this takes O(n) time
    for (int i = 0; i < n; i++)
    {
        int currIndex = (currSubsetVal - 1) * n + i;
        int pathCost = memo[currIndex];

        if (pathCost < minCost)
        {
            minCost = pathCost;
            endVertex = i;
        }
    }

    // add the vertex in end of path
    path[k - 1] = endVertex;

    for (int i = k - 2; i >= 0; i--)
    {
        int newEndVertex = -1;
        minCost = INT_MAX;

        // remove previous endVertex color from subset and get new value
        int newSubsetVal = removeColor(currSubsetVal, colorsMap[endVertex]);

        // for all in adjacency of end vertex
        for (auto p : adj[endVertex])
        {
            int u = p.first;
            int w = p.second;

            int currIndex = (newSubsetVal - 1) * n + u;

            int pathCost = memo[currIndex];

            int totalCost = pathCost == INT_MAX ? INT_MAX : (pathCost + w);

            if (totalCost < minCost)
            {
                minCost = totalCost;
                newEndVertex = u;
            }
        }

        // add the vertex in path
        path[i] = newEndVertex;

        currSubsetVal = newSubsetVal;
        endVertex = newEndVertex;

        // inner loop runs for indegree of vertex times
        // total time for this loop k* (sum of indegree)
        // sum of all indegree is 2*m
    }

    // total time O(k*m)
}