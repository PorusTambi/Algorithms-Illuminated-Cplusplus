#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct job
{
    int key;
    int weight;
    int length;
};

void scheduleJobs(vector<job> &j);

int main()
{
    int n;
    cin >> n;
    int w, l;

    vector<job> j(n);

    for (int i = 0; i < n; i++)
    {
        cin >> w >> l;
        j[i].key = i + 1;
        j[i].weight = w;
        j[i].length = l;
    }

    scheduleJobs(j);

    cout << "optimal schedule " << endl;

    int ans = 0;
    int completionTime = 0;

    for (int i = 0; i < n; i++)
    {
        cout << j[i].key << " ";
        completionTime += j[i].length;
        ans += (j[i].weight) * completionTime;
    }
    cout << endl;

    cout << "optimal val " << ans << endl;
}

bool cmp(job &j1, job &j2)
{
    //Using double for the comparison ratio is generally fine,
    // but in competitive programming or high-precision proofs,
    //division can lead to precision errors (e.g., $0.333333333333334$ vs $0.333333333333333$)
    //The Pro-Tip: Use cross-multiplication to compare ratios without division.
    //Instead of (w1/l1) > (w2/l2), use (w1 * l2) > (w2 * l1).
    //This keeps everything in the integer domain and is $100\%$ accurate.

    return (j1.weight * j2.length) > (j2.weight * j1.length);
}

void scheduleJobs(vector<job> &j)
{
    sort(j.begin(), j.end(), cmp);
}
