#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int getCoverageIncrease(unordered_set<int> &currentSet, vector<int> &subset);
int greedyCoverage(int m, int k, vector<vector<int>> &subsets, vector<bool> &isSubsetChosen);

int main()
{

    //no of subsets
    int m;

    //number of subsets we can select
    int k;

    cin >> m >> k;

    //for simplicity assume elements in each subset are integers
    vector<vector<int>> subsets(m);

    //count of elements in a given subset
    //each set will have unique elements that's what is a set
    int cnt;

    //actual el
    int el;

    for (int i = 0; i < m; i++)
    {

        cin >> cnt;

        for (int j = 0; j < cnt; j++)
        {

            cin >> el;
            subsets[i].push_back(el);
        }
    }

    //first of all lets analyze what is input size
    //that will help us to tell whether running time is polynomial or exponential in input size

    //for m - logm keystrokes to enter
    // k - logm keystrokes to enter at most as k<=m
    //m total subsets , let say max count of elements in any subset is s
    //hence m*s*log(el) total keystrokes  - log(el) per element
    //let say all numbers are 32 bits so total size is m*s*32
    //hence input size theta m*s

    //brute force try all possible k , that is mchoosek, mck
    //it is m!/k!*(m-k)! see if k=m/2 then each term is 2*(m-r)/(m-2r)
    //and m-r > m-2r hence each term at least 2 so its at least 2^m/2 exponential

    //this problem is NP-Hard , hence use fast heuristics algo, greedy coverage

    //indices of k subsets will be true from m which are chosen
    vector<bool> isSubsetChosen(m, false);

    int maxCoverage = greedyCoverage(m, k, subsets, isSubsetChosen);

    cout << "Max coverage " << maxCoverage << endl;

    cout << "Subsets with 1 are selected " << endl;

    for (bool x : isSubsetChosen)
    {
        cout << x << " ";
    }

    cout << endl;

    return 0;
}

int greedyCoverage(int m, int k, vector<vector<int>> &subsets, vector<bool> &isSubsetChosen)
{

    //initially this will be phi that is empty
    unordered_set<int> currentSet;

    for (int i = 0; i < k; i++)
    {
        //greedily select that set which is not yet chosen which increases the coverage most, in each iteration
        int coverageIncrease = -1;
        int subsetChosen = -1;
        for (int j = 0; j < m; j++)
        {
            if (!isSubsetChosen[j])
            {
                //this function call takes theta(s) time, see in function
                int val = getCoverageIncrease(currentSet, subsets[j]);
                if (val > coverageIncrease)
                {
                    coverageIncrease = val;
                    subsetChosen = j;
                }
            }

            //this loop takes at most bigO(m*s) time
        }

        isSubsetChosen[subsetChosen] = true;
        //push all new elements in current set that is union operation
        for (int r = 0; r < subsets[subsetChosen].size(); r++)
        {
            //automatically handle duplicates
            currentSet.insert(subsets[subsetChosen][r]);

            //this loop also takes theta(s) time
        }

        //total time in per iteration of most outer loop
        //theta(m*s)
    }

    //this takes k*s time as k subsets and each having max s elements
    int maxCoverage = currentSet.size();

    //this total takes
    //k*m*s + k*s = bigO(k*m*s)

    //k<=m
    //hence total time bigO(m^2 * s)

    //now input size is m*s
    //total time <  m^2 * s^2 <= (m*s)^2
    //hence total time is bounded by a polynomial in input size m*s
    //hence this greedy algo takes polynomial time

    return maxCoverage;
}

int getCoverageIncrease(unordered_set<int> &currentSet, vector<int> &subset)
{
    int increase = 0;

    for (int i = 0; i < subset.size(); i++)
    {

        int el = subset[i];

        if (currentSet.find(el) == currentSet.end())
        {
            increase += 1;
        }
    }

    //this take subset size time, max elements in a subset is s
    //hence theta(s) time

    return increase;
}