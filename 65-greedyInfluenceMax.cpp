#include <iostream>
#include <vector>
#include <random>
#include <queue>

using namespace std;

double greedyInfluence(int n, int k, double p, int simulations, vector<vector<int>> &adj, vector<bool> &isChosen);
double getExpectedInfluence(int n, double p, int simulations, vector<vector<int>> &adj, vector<bool> &isChosen);
int runCascadeExperiment(int n, double p, vector<vector<int>> &adj, vector<bool> &isChosen);

//create a random device
random_device rd;

//create a mersenne random number generator and seed it with random_device
mt19937 rgen(rd());

//create a uniform distribution of 0 to 1
uniform_real_distribution<double> dist(0.0, 1.0);

//how to get probability p let say  0.2
//since each number in 0 to 1 is equally likely , and there are infinite numbers , the best way to look at this is
//consider a line from O to 1  of length 1 on x axis  and height 10 on y axis
//Now imagine you throw a dart , and its equally like to land at any point in 0 to 1 on x axis
//what is total sample space the complete area 1 * 10
//if the number chosen by random generator is less than 0.2
//analogous to your dart what is the probality of a dart falling in x <= 0.2
//its is 0.2 *10 / 1* 10 which is 0.2
//so if the number coming is less then equal to 0.2 than the edge is active, else not

int main()
{

    //i/p o/p examples

    //4
    // 5
    // 2
    // 0.2
    // 1000
    // 0 1
    // 0 2
    // 0 3
    // 2 3
    // 1 3
    // Running Greedy Influence Maximization...
    // Nodes: 4, Budget (k): 2, Probability: 0.2
    // Simulations : 1000

    // Calculating Step 1...
    //  Node chosen 0 (ExpectedInfluenceIncrease: 1.624)
    // Calculating Step 2...
    //  Node chosen 2 (ExpectedInfluenceIncrease: 0.954)
    // Max expected influence 2.578

    // Final Optimal Seed Set:  0 2

    // 4
    // 5
    // 2
    // 1
    // 1000
    // 0 1
    // 0 2
    // 0 3
    // 2 3
    // 1 3
    // Running Greedy Influence Maximization...
    // Nodes: 4, Budget (k): 2, Probability: 1
    // Simulations : 1000

    // Calculating Step 1...
    //  Node chosen 0 (ExpectedInfluenceIncrease: 4)
    // Calculating Step 2...
    //  Node chosen 1 (ExpectedInfluenceIncrease: 0)
    // Max expected influence 4

    // Final Optimal Seed Set:  0 1

    //number of vertices
    int n;

    //number of edges
    int m;

    //number of seed vertices we can select
    int k;

    //activation probability
    double p;

    //since we can't calculate exact expected value, we will use law of large numbers
    //and say if we run this experiment 1000 times and then sum all and divide by 1000, we will be very close to actual expected value
    //how we get this 1000 number run this experiment multiple times and plot on graph the average values
    //after some time you will see something like a horizontal straight line in graph, that time you will understand things are converging
    int simulations;

    cin >> n >> m >> k >> p >> simulations;

    vector<vector<int>> adj(n);

    int u, v;
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v;
        //creating directed graph via adjacency list
        adj[u].push_back(v);
    }

    //which vertices are chosen as seed vertices by our greedy influence algo
    vector<bool> isChosen(n, false);

    cout << "Running Greedy Influence Maximization...\n";
    cout << "Nodes: " << n << ", Budget (k): " << k << ", Probability: " << p << "\n";
    cout << "Simulations : " << simulations << "\n\n";

    //run the greedy influence algo, it updates isChosen in place
    double maxExpectedInfluence = greedyInfluence(n, k, p, simulations, adj, isChosen);

    cout << "Max expected influence " << maxExpectedInfluence << endl;

    cout << "\nFinal Optimal Seed Set:  ";

    for (int i = 0; i < n; i++)
    {

        if (isChosen[i])
        {

            cout << i << " ";
        }
    }

    cout << endl;

    return 0;
}

double greedyInfluence(int n, int k, double p, int simulations, vector<vector<int>> &adj, vector<bool> &isChosen)
{

    double maxExpectedInfluence = 0;

    //select each of k vertices
    for (int i = 0; i < k; i++)
    {
        int vertexSelected = -1;
        double val = -1;

        cout << "Calculating Step " << i + 1 << "..." << endl;

        for (int j = 0; j < n; j++)
        {

            //if not chosen
            if (!isChosen[j])
            {

                //temporarily set isChosen[i] to true
                isChosen[j] = true;

                //calculate expected influence with these isChosen true set of seed vertices
                double currentExpectedInfluence = getExpectedInfluence(n, p, simulations, adj, isChosen);

                //revert it back
                isChosen[j] = false;

                if (currentExpectedInfluence > val)
                {
                    //choose the one which maximizes the expectedInfluence
                    val = currentExpectedInfluence;
                    vertexSelected = j;
                }
            }
        }

        double increaseInExpectedInfluence = val - maxExpectedInfluence;
        maxExpectedInfluence = val;

        cout << " Node chosen " << vertexSelected << " (ExpectedInfluenceIncrease: " << increaseInExpectedInfluence << ")\n";

        //set vertexSelected to true
        isChosen[vertexSelected] = true;
    }

    return maxExpectedInfluence;
}

double getExpectedInfluence(int n, double p, int simulations, vector<vector<int>> &adj, vector<bool> &isChosen)
{

    int total = 0;
    for (int i = 0; i < simulations; i++)
    {
        //run experiment  and calculate number of activated vertices
        int countActivated = runCascadeExperiment(n, p, adj, isChosen);

        total += countActivated;
    }

    //sum them all and divide by total simulations to get the average/ expected value
    return ((double)(total)) / simulations;
}

int runCascadeExperiment(int n, double p, vector<vector<int>> &adj, vector<bool> &isChosen)
{

    //run bfs from all seed vertices and when reach any edge flip the coin to see if active if number is less than equal to p its active
    //do this to calculate the activated vertices

    vector<bool> activeVertices(n, false);

    queue<int> q;

    int countActivated = 0;

    //activate all seed vertices
    for (int i = 0; i < n; i++)
    {

        //activate all seed vertices
        activeVertices[i] = isChosen[i];

        //push activated vertices to q

        if (activeVertices[i])
        {
            countActivated += 1;
            q.push(i);
        }
    }

    while (!q.empty())
    {

        //fetch the front
        int v = q.front();

        //pop from queue
        q.pop();

        //for each in adjaceny of v
        for (int u : adj[v])
        {

            //if not active
            if (!activeVertices[u])
            {

                //then flip coin to see the edge active or not
                double num = dist(rgen);

                if (num <= p)
                {
                    //edge active

                    //make vertex active and push to queue

                    //making active is necessary before , otherwise it may be pushed twice
                    activeVertices[u] = true;
                    countActivated += 1;

                    q.push(u);
                }
            }
        }
    }

    return countActivated;
}