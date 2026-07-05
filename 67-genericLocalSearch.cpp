#include <iostream>
#include <vector>
#include <random>
#include <unordered_map>
#include <utility>
#include <cmath>
using namespace std;

//here we are writing two algorithms for makespan minimization problem
//one using LPT algo
//one using generic local search

unordered_map<int, int> mmLocalSearch(int n, int m, vector<int> &jobLoad);
unordered_map<int, int> getStartingSolution(int n, int m, vector<int> &jobLoad);
int getRandomNumber(int start, int end);
pair<int, int> chooseLocalMove(int n, int m, vector<int> &jobLoad, unordered_map<int, int> &currSolution);
int getMaxLoad();
bool rollCoinWithProbability(double p);

//denotes machine load
vector<int> machineLoad;

int main()
{

    //n is number of jobs, and m the number of machines
    int n, m;

    cin >> n >> m;

    //load of each job
    vector<int> jobLoad(n, 0);

    for (int i = 0; i < n; i++)
    {
        cin >> jobLoad[i];
    }

    for (int i = 0; i < m; i++)
    {
        machineLoad.push_back(0);
    }

    unordered_map<int, int> jobMap = mmLocalSearch(n, m, jobLoad);
    int finalCost = getMaxLoad();

    // cout << endl
    //      << "Final assignment -------------------" << endl
    //      << endl;

    // for (int i = 0; i < n; i++)
    // {
    //     cout << "Job " << i + 1 << " - "
    //          << "machine " << jobMap[i] + 1 << endl;
    // }

    cout << "Final makespan = " << finalCost << endl;

    cout << endl
         << "----------------------------------" << endl;

    return 0;
}

//mmLocal search stands for makespan minimization by local search, return assignment of jobs to m machines
unordered_map<int, int> mmLocalSearch(int n, int m, vector<int> &jobLoad)
{
    //Modelling decisions - think of meta graph of all feasible solutions
    //local search is just some walk in a meta graph

    //step 1 - what are vertices of meta graph, all feasible solution
    //how many vertices - each job has m choices so m^n total assignments

    //step 2 - think of objective function that we need to minimize or maximize
    //we need to minimize the maximal load on a machine

    //after step 1 and 2 we have the global optima defined in our mind imagination

    //step 3 - think of edges in your meta graph that is allowable local moves
    //one basic intuitional move we get from 2opt is like 1 change swap, call it type 1 move
    //that is given an assignment a vertex in meta graph shift one job to some other machine, let say to its adjacent machine
    //think of things as circular mth is adjacent to m-1 and 1
    //number of allowable local moves = n*(2) -> n jobs for each shift to other 2 adjacent its not part of
    //see these are allowable local moves they can improve or degrade objective function value

    //step 4 - neighbourhood size
    //number of allowable local moves is called neighbourhood size
    //see I can also do like shift a job to any other machine not only adjacent, this will have greater neighbourhood size, call it type 2 move
    //total number of allowable local moves = n*(m-1) -> n jobs for each shift to other m-1 its not part of
    //the local optimal of type 2 move is also local optima of type 1, but vice versa is not true
    //number of local optimal of type 2 is less than that of type 1 , hence intuitionally it can get stuck in less local optimas
    //and by type 2 moves we may get better answer
    //but remember large neighbourhood is good but its not the guarantee that we will get better answer
    //we can get better answer with small neighbourhood as well
    //best is to try and experiment different neighbourhood size and compare results on same inputs
    //for this we will stick to type 2 moves

    //after step 4 we have now defined local optimas in our meta graph, now we start with algorithmic decisions

    //Algorithmic decision - which vertex to start and which move to pick

    //step 5 - Now we choose our starting vertex in our meta graph where we start our walk
    //for more details on this see function called below

    //this type of data structure we choose so that its easy to move jobs from one machine to other
    unordered_map<int, int> currSolution = getStartingSolution(n, m, jobLoad);

    //step 6 - choose which local move to apply, for details on this see below function chooseLocalMove

    //see function chooseLocalMove to understand what these iterations mean
    //iterations should scale with n more n more iterations so n*100 I choose
    //I have myself chosen one number n*100 , best way is to experiment
    int iterations = n * 100;

    //step 7 - keep walking in meta graph for some iterations
    while (iterations > 0)
    {

        //this function returns which job to move, and the new machine
        //if no local move to choose it return {-1,-1}
        //but for our case there will always be a local move as we consider both improving and non improving moves
        //see function chooseLocalMove for more details
        pair<int, int> localMove = chooseLocalMove(n, m, jobLoad, currSolution);

        int job = localMove.first;
        int machine = localMove.second;

        int oldMachine = currSolution[job];

        //change machine loads
        machineLoad[oldMachine] -= jobLoad[job];
        machineLoad[machine] += jobLoad[job];

        //apply the local move
        currSolution[job] = machine;

        // int maxLoad = getMaxLoad();
        // cout << "Iteration " << 400 - iterations + 1 << " - " << maxLoad << endl;

        iterations -= 1;
    }

    return currSolution;
}

//this function return the starting feasible solution from where local search starts
unordered_map<int, int> getStartingSolution(int n, int m, vector<int> &jobLoad)
{
    //There are multiple ways to select starting solution
    //Greedy - we already know LPT why not run the LPT algo to get the solution and take it as a starting solution which local search can improve
    //Randomly - randomly select any of the vertex in meta graph as starting solution

    //See note that having a better starting point doesn't guarantee you will land at better solution in local search
    //local optimas can trap you weirdly
    //I think randomization is great tool to beat any adversary when we don't know much about future
    //because I only don't know what randomization will pick, so how adversary can know it and beat us

    //so in this problem I will choose the starting solution randomly

    //how will I pick randomly
    //for each job independently I will choose one number uniformly at random from 0 to m-1 machine to which I will assign it
    //see any feasible solution has probability (1*m)^n all have same probaility
    //that is I am choosing any vertex at random from meta graph
    //simple and easy implementation

    //this type of data structure I choose because when we randomly move jobs its easy to find and change position of jobs

    unordered_map<int, int> startingSol;

    for (int i = 0; i < n; i++)
    {
        int ind = getRandomNumber(0, m - 1);
        startingSol[i] = ind;

        //updating machineLoad
        machineLoad[ind] += jobLoad[i];
    }

    return startingSol;
}

//This function chooses a number b/w [start,end] both inclusive, uniformly at random, independently
int getRandomNumber(int start, int end)
{

    //get a random device
    static random_device rd;

    //seed the merseene twister with random device
    //make these static so these are not initialized every time and you save time
    //I know this is not perfectly independent, but pseudo random are also very practically useful
    static mt19937 gen(rd());

    //create a variable for uniform int distribution
    uniform_int_distribution<int> dist(start, end);

    //generate a random number from start to end inclusive
    return dist(gen);
}

//This function chooses a local move assignment of a job to some other machine
//return jobNo and newMachine
pair<int, int> chooseLocalMove(int n, int m, vector<int> &jobLoad, unordered_map<int, int> &currSolution)
{

    //Now there can be many allowable local moves according to neighbourhood size
    //some allowable local moves can decrease our objective function, some can increase
    //out of multiple allowable local moves which to choose there are many ways to do this
    //in our case our motive is to decrease objective function, so think in that

    //1 - start scanning and pick first one which decreases
    //2 - out of all pick the one which is least that is which decreases most

    //But think of local optima traps, and think of 2 questions
    //q1 - should picking least, which decreases most guarantee a better solution - no, not always
    //q2 - should picking non improving that is increasing worsen my condition - may not worsen,
    //maybe you increase and then decrease and decrease and reach to better local optima
    //so what's again the best way to do if we don't know things - randomization

    //This randomization is again some of the ways to avoid local optima
    //So what we will do is uniformly randomly and independently pick one of allowable moves
    //if the allowable solution is improving that is it decreases we pick it
    //if the allowable solution is degrading that is it increases, we do some clever work

    //if the allowable solution is increasing we find the increase,lets call it delta
    //we pick that solution with some probability that is e^(-delta), otherwise we drop
    // this function is always 0 to 1, intuitive function for probability
    //that is more increase, less chances to pick
    //we can also use function e^-(a* delta) and fine tune parameter a, but for simplicity I am using a=1

    //Now if we choose such type of strategy
    //we can pick improving or degrading move any , so our algo may not halt due to cycle
    //so that is why I set some iterations like 200 in while loop of local search so it halts 100%
    //also local search anytime I halt contains one feasible solution with it
    //so its ok to interrupt local search at any time, that's why its also called anytime algorithm
    //if you think its taking too long stop it, you will at least get a feasible solution
    //if we pick only improving moves and number of feasible solutions is finite then algo 100% halt

    //let's start step by step simple and easy
    //ok so lets start, pick any job at random and uninformly and independently from 0 to n-1

    int jobNo = getRandomNumber(0, n - 1);

    //now see what's the current machine for that job in hashMap
    int oldMachine = currSolution[jobNo];

    //now think like we have 0 1 2 3 4 machine
    //current machine number comes to be 2
    //now I have to pick uniformly at random from 0 1 3 4
    //clever trick think like I have to pick from 0 1 2 3
    //if the number a that comes is less than than 2 pick a
    //if the number a that comes is greater that equal to 2 pick machine a+1 think....

    int rm = getRandomNumber(0, m - 2);
    int newMachine = rm >= oldMachine ? rm + 1 : rm;

    int maxLoad = getMaxLoad();

    //check if its degrading, if improving or same pick it directly
    bool isDegradingMove = maxLoad < (machineLoad[newMachine] + jobLoad[jobNo]);

    if (!isDegradingMove)
    {
        return {jobNo, newMachine};
    }

    //now we have to pick it or not with probability e^-delta
    int delta = (machineLoad[newMachine] + jobLoad[jobNo]) - maxLoad;

    //this is actually e^(-delta)if we put 10*delta its very small probability even e^-10 with delta 1
    //so it won't actually get picked
    double val = 1 * delta;
    double probability = exp(-val);

    bool rollCoin = rollCoinWithProbability(probability);

    if (rollCoin)
    {
        return {jobNo, newMachine};
    }

    //return same old machine no effect, next iteration may cause something
    return {jobNo, oldMachine};
}

//This function returns the makespan of the given solution
int getMaxLoad()
{ //now create what loads are on machines currently

    int maxLoad = machineLoad[0];

    for (int i = 1; i < machineLoad.size(); i++)
    {
        maxLoad = max(maxLoad, machineLoad[i]);
    }

    return maxLoad;
}

//This function rolls a coin with heads probability p and returns true if heads come
bool rollCoinWithProbability(double p)
{

    //see our influence maximization code in PC to understand how this works

    static random_device rd;

    static mt19937 gen(rd());

    uniform_real_distribution<double> dist(0.0, 1.0);

    double val = dist(gen);

    return val <= p;
}
