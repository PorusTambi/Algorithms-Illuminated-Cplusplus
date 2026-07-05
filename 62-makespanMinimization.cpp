#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct cmp
{

    bool operator()(pair<int, int> &a, pair<int, int> &b)
    {
        //this is for min heap;
        return a.second > b.second;
    }
};

int grahamAlgo(int m, int n, vector<int> &jobLoad, vector<vector<int>> &jobsOnMachine);

int main()
{

    //i/p-o/p

    // 5
    // 21
    // 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 5
    // Minimum makespan is 9
    // Jobs on each machine
    // Machine 0 - 2 9 13 17
    // Machine 1 - 1 6 11 16
    // Machine 2 - 4 8 12 19
    // Machine 3 - 0 5 10 15 20
    // Machine 4 - 3 7 14 18

    //number of servers
    int m;

    // number of jobs
    int n;

    cin >> m >> n;

    // length of each jobs, length positive, it may or may not be integer length for simplicity integer
    vector<int> jobLoad(n);

    for (int i = 0; i < n; i++)
    {
        cin >> jobLoad[i];
    }

    //brute force algo time is m^n , m choice for each job, this is exponential
    //this problem is NP Hard

    //Fast heuristics for this is greedy algo devised by Graham

    //array to represent indices of job on 0 to m-1 machines
    //jobs also have indices 0 to m-1
    vector<vector<int>> jobsOnMachine(m);

    int makespan = grahamAlgo(m, n, jobLoad, jobsOnMachine);

    cout << "Minimum makespan is " << makespan << endl;

    cout << "Jobs on each machine " << endl;

    for (int i = 0; i < m; i++)
    {
        cout << "Machine " << i << " - ";

        for (int j : jobsOnMachine[i])
        {
            cout << j << " ";
        }
        cout << endl;
    }

    cout << endl;

    return 0;
}

int grahamAlgo(int m, int n, vector<int> &jobLoad, vector<vector<int>> &jobsOnMachine)
{
    //keeping track of each machine load
    vector<int> machineLoad(m, 0);

    vector<pair<int, int>> machineIndexAndLoad(m);

    //theta(m) operations
    for (int i = 0; i < m; i++)
    {
        machineIndexAndLoad[i] = {i, 0};
    }

    //create and put all {i,0} in priority queue this is theta(m) operation
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq(machineIndexAndLoad.begin(), machineIndexAndLoad.end());

    for (int i = 0; i < n; i++)
    {

        //find the machine with minimum load
        //and assign this job to that machine
        //break ties arbitrarily

        //findMin can be done efficiently via heap in logm per min find
        auto p = pq.top();

        //pop from pq
        pq.pop();

        int mInd = p.first;
        int load = p.second;

        //new machine load
        machineLoad[mInd] = load + jobLoad[i];

        //add job i to machine mInd
        jobsOnMachine[mInd].push_back(i);

        //push again to pq
        pq.push({mInd, machineLoad[mInd]});
    }

    //loop total is theta(n*logm)

    //find max load of all machines that is min makespan

    int makespan = 0;

    for (int i = 0; i < m; i++)
    {

        if (machineLoad[i] > makespan)
        {
            makespan = machineLoad[i];
        }
    }

    //running time theta(n*logm)+m
    //since in general cases n>m otherwise problem is not interesting
    ///hence running time is theta(n*logm)

    return makespan;
}
