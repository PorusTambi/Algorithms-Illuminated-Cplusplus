#include <iostream>
#include <vector>
using namespace std;

bool isVertexPresentInSubset(int currSubsetVal, int vertexNo);
int getNewSubsetVal(int currSubsetVal, int vertexRemoved);
int getSubsetSize(int subsetVal);
int getMinTourCost(vector<vector<int>> &adjMatrix, vector<int> &memo, int n);
void printOptimalTour(vector<vector<int>> &adjMatrix, vector<int> &memo, int n);

int main()
{

    // dynamic programming iterative+memoization implementation of TSP

    // taking the undirected complete graph as input
    // since the graph is complete its better to take it as adjacency matrix

    // sample input
    //     5
    // 0 1 4 5 10
    // 1 0 2 6 3
    // 4 2 0 7 8
    // 5 6 7 0 9
    // 10 3 8 9 0

    // output
    // Optimal tour value is 23
    // Optimal tour
    // 0 2 1 4 3 0

    // the number of vertices
    int n;
    cin >> n;

    // adjacency matrix storing cost of each edge
    vector<vector<int>> adjMatrix(n, vector<int>(n, 0));

    // please note that if a,a input should give cost 0
    // also please not a,b and b,a cost should be same

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> adjMatrix[i][j];
        }
    }

    // Let's think of this problem via god's way
    // Now a tour can start and end with any vertex, let say it starts with vertex 0, vertices indexed from 0 to n-1
    // out of all vertices suppose god tell 0 connects to 5 in optimal tour
    // now we have to find a optimal cycle free path from 5 to 0 covering all vertices exactly once

    // if we move one step ahead let suppose god tells us, 5 connects to 7 in optimal tour
    // then we have to find optimal cycle free path from 7 to 0 including all vertices exactly once except 5
    // this is the optimal substructure

    // how to write recurrance
    // see the final optimal tour is min of all cycle free paths from j to 0 with j!=0 + cost of edge (j,0)
    // hence our subproblems are cycle free path from a vertex j to 0
    // now those cycle free paths could contain any set of vertices lets call that set S
    // lets say S is the set of vertices present in cycle free path, except 0 as that is always included by convention
    // now our subproblems are Cj,S
    // that is min cost cycle free path from j to 0 that contains all vertices in S exactly once, note 0 not belongs to S
    // Cj,S = min k!=j, k!=0 k belongs to set S ((Ck,S-{j},cost(j,k)))

    // Now how many subproblems
    // see the set S contains always at least 1 vertices , that is to be clubbed with 0
    // the sets S={j} are base cases for all possible j!=0
    // apart from 0, other remaining are n-1 vertices
    // now for each I can select or not total possible = 2^(n-1)
    // but I have to select one for sure as base case is of size 2 , hence remove phi from 2^(n-1)
    // total possible subsets = (2^(n-1) - 1)
    // for each subset I can select any j from that subset as start so overall max I can say subproblems is O((2^(n-1)-1)*(n-1))
    // so its around 2^n * n subproblems

    // overlapping subproblems
    // Now I have Cj,S let say in first I pick 3 and next 5 vertex next 7 so it comes C7,S-{j,3,5}
    // I can also pick like 5 then 3 then 7 so it comes C7,S-{j,5,3}
    // see overlapping subproblems

    // calculating subproblems
    // Now I have to calculate each subproblem and store its optimal cost
    // How do I index these sets S in array, I mean I can index j in Cj,S but what about S ?
    // since there are n-1 vertices if you think like a bit array of all n-1 and put one to whichever selected
    // 2 different subsets correspond to different integers if I convert binary to decimal and I can use integers as an index in array
    // range I can get is since at least 1 selected so its 1 to (2^(n-1) - 1)(when all n-1 selected)
    // think of vertices from 1 to n-1, 1 being on right and n-1 on left
    //  so a number like 0 1 means vertex 1 is in set vertex 2 is not in set

    // create a memo table to store all subproblems answer
    // for each Cj,S we know how many i belongs to S and i!=0, i!=j, only these type of i belonging to S are relevant
    // so actually rows are 2^(n-1) - 1 and cols depend on S size
    // still we make rows = (2^(n-1))-1 and cols=n-1 size array for simplicity

    int numberOfSubsets = (1 << (n - 1)) - 1;

    int rows = numberOfSubsets; // this is (2^(n-1))-1
    int cols = n - 1;

    // keep it simple no cycle free path or tour is of length INT_MAX or greater
    // space taken O(n * 2^n)

    // this vector of vector is a problem as there are pointers and each array is scattered
    // vector<vector<int>> memo(rows, vector<int>(cols, INT_MAX));
    // that is 0th array is contiguous,1st array is also contiguous
    // but 0 and 1 array scattered in memory, this creates more time to fetch something
    // and less cache locality, why not make it a single dimensional array, better cache locality

    // for iterative we have to start bottom up
    // now we have subsets of elements from 1 to n-1, we have at least subset size of 1
    // vertex 1 on right and n-1 on left
    // what is base case, is all subsets of size 1
    // then what is next all subsets of size 2
    // thus iteration will move in this way, first calculate all subproblems with subsets of size 1 then size 2, till size n-1
    // then at last calculate min tour using all those subproblems having subset of size n-1

    vector<int> memo((rows * cols), INT_MAX);

    // Now in each iteration I have to enumerate all subsets of a particular size let say k, how to do that?
    // I have to specifically enumerate their mapped numbers

    // Great Intuition
    //  what's the requirement for any S before calculating Cj,S for any j in S
    //  S-{j} should be available, S-{j} is a number smaller than S
    //  if I do traverse just numbers in ascending order this will work
    //  Now iterate easily from 1 to  2^(n-1), in ascending order
    // no need to find combinations

    for (int subsetVal = 1; subsetVal <= numberOfSubsets; subsetVal++)
    {
        // Number of iterations is O(2^n)

        // Number of elements in subset
        // this function getSubsetSize takes O(n) time, see function comments
        int subsetSize = getSubsetSize(subsetVal);

        // simply iterate over all j
        for (int j = 1; j < n; j++)
        {

            int ind = ((subsetVal - 1) * cols) + (j - 1);

            // this can be done only when vertex is present in subset, else we don't do anything
            // now Cj,S = min(Ck,S-{j} + cost k,j)
            // thus I have to iterate for every vertex in subset
            // Now (Ck, S-{j}) since S-{j} is of size less than S
            //(Ck, S-{j}) this subproblem answer is already calculated in some previous iteration

            // isVertexPresentInSubset takes O(n) time
            if (isVertexPresentInSubset(subsetVal, j))
            {

                if (subsetSize == 1)
                {
                    // this is base case set the cost of edge 0 to j
                    memo[ind] = adjMatrix[0][j];
                }

                else
                {

                    int val = INT_MAX;

                    // this is S-{j}
                    // this function getNewSubsetVal takes O(n) time
                    int newSubsetVal = getNewSubsetVal(subsetVal, j);

                    for (int r = 1; r < n; r++)
                    {

                        // if r not equals j and its in subset
                        if (r != j && isVertexPresentInSubset(subsetVal, r))
                        {
                            int index = ((newSubsetVal - 1) * cols) + (r - 1);

                            int cycleFreeCostPath = memo[index];
                            int edgeCost = adjMatrix[j][r];

                            int totalCost = cycleFreeCostPath + edgeCost;

                            if (val > totalCost)
                            {
                                val = totalCost;
                            }
                        }

                        // this loop takes O(n^2) time
                    }

                    memo[ind] = val;
                }
            }
            // this loop takes total O(n^3) time
        }
    }

    // this loop totally runs for all subsets and for each it takes O(n^3) time
    // so total takes O(n^3 * 2^n) time

    // this function getMinTourCost takes O(n^2) time, see comments inside function
    int minTour = getMinTourCost(adjMatrix, memo, n);

    cout << "Optimal tour value = " << minTour << endl
         << endl;

    printOptimalTour(adjMatrix, memo, n);

    // see functions below for details of each
    //  total time = O(n^3 * 2^n)
    //  space = O(n*2^n) for memo table

    return 0;
}

// now given any subset, I have to choose vertices from it
// so its like given any vertex I have to check if vertex is present in that subset or not, below function tells this
bool isVertexPresentInSubset(int currSubsetVal, int vertexNo)
{
    int bitNumber = vertexNo - 1;
    // check if the bit at above position is 1

    int num = 1 << bitNumber;

    return (currSubsetVal & num) > 0;
    // this function takes O(n) time and O(n) auxillary space
}

// now next operation is you have to remove a vertex from subset and get new subset mapped number, this function tells this
int getNewSubsetVal(int currSubsetVal, int vertexRemoved)
{

    // placing 1 at that vertex position
    // remember vertices are like 1 to n-1, 1 being on right and n-1 on left
    //  so a number like 0 1 means vertex 1 is in set vertex 2 is not in set
    int removeVal = 1 << (vertexRemoved - 1);

    // take xor of two so as to make that 1 in that vertex position as 0
    return currSubsetVal ^ removeVal;

    // calculating remove val and taking xor takes O(n) for n bit numbers  where n can be very large as per number of vertices
    // this function takes O(n) time and O(n) auxillary space
}

// this function tells the number of elements in a subset
int getSubsetSize(int subsetVal)
{

    int size = 0;

    while (subsetVal > 0)
    {
        // check if the bit is 1
        if (subsetVal & 1)
        {
            size += 1;
        }
        subsetVal = subsetVal >> 1;
    }

    // for n bits this takes O(n) time

    return size;
}

int getMinTourCost(vector<vector<int>> &adjMatrix, vector<int> &memo, int n)
{

    // starting is from 0
    //  from 0 if I choose 2 then 2 to 0 cycle free path that covers all vertices
    // so find min of Cj,S+ cost(j,0) for 1 subset of size n-1 that contains all

    // calculating subset val takes O(n) time
    int subsetVal = (1 << (n - 1)) - 1;

    // take assumption any tour or any path is not above or equal INT_MAX
    int minTour = INT_MAX;

    // choose any vertex other than 0
    for (int j = 1; j < n; j++)
    {
        // get cycle free path from j to 0 covering all vertices that is starting subset and 0 by default

        int ind = ((subsetVal - 1) * (n - 1)) + (j - 1);
        int cycleFreePathCost = memo[ind];
        int edgeCost = adjMatrix[0][j];
        int totalCost = cycleFreePathCost + edgeCost;

        // take min of all
        if (minTour > totalCost)
        {
            minTour = totalCost;
        }
        // this loop takes O(n^2) time as operations on n bit integers
    }

    // time this function takes is O(n^2) and O(n) auxillary space

    return minTour;
}

// prints the optimal tour - the reconstruction step
void printOptimalTour(vector<vector<int>> &adjMatrix, vector<int> &memo, int n)
{
    // Note we can also remember the choice of each step, each subproblem
    // but storing that takes me huge space
    // that's why I trace them back using our memo table

    // this function takes auxillary space of just O(n) due to just storing of subset of n bits

    // starting vertex of tour 0
    int startingVertex = 0;

    // starting subset of tour
    // this takes O(n) time
    int currSubsetVal = (1 << (n - 1)) - 1;

    // current vertex of tour
    int currVertex = startingVertex;

    cout << endl
         << endl;

    cout << "Optimal tour " << endl;

    cout << currVertex << " ";

    // to keep track how many done
    int count = 1;

    while (count < n)
    {

        int val = INT_MAX;
        int vertexSelected = -1;

        // now we need to find minimum of all in starting subset
        for (int i = 1; i < n; i++)
        {
            if (i != currVertex && isVertexPresentInSubset(currSubsetVal, i))
            {
                // current vertex to i edge cost
                int edgeCost = adjMatrix[currVertex][i];

                int ind = ((currSubsetVal - 1) * (n - 1)) + (i - 1);

                // cycle free path from i to 0 cost, with subset as currSubsetVal
                int cycleFreePathCost = memo[ind];

                int totalCost = edgeCost + cycleFreePathCost;

                if (val > totalCost)
                {
                    val = totalCost;
                    vertexSelected = i;
                }
            }

            // loop takes O(n* n) time O(n) due to isVertexPresentInSubset
        }

        cout << vertexSelected << " ";

        // update the subset val after removing vertexSelected from it
        // this takes O(n) time
        currSubsetVal = getNewSubsetVal(currSubsetVal, vertexSelected);
        // set current vertex as vertexSelected
        currVertex = vertexSelected;
        count += 1;

        // total while loop takes O(n*n^2) = O(n^3) time
    }

    cout << startingVertex << " ";

    cout << endl
         << endl;

    // this function takes O(n^3) time
}