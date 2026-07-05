#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;
bool sortByXCoordinate(pair<int, int> &p1, pair<int, int> &p2);
bool sortByYCoordinate(pair<int, int> &p1, pair<int, int> &p2);
vector<pair<int, int>> closestPair(vector<pair<int, int>> Px, vector<pair<int, int>> Py);
double getDistance(pair<int, int> &v1, pair<int, int> &v2);
vector<pair<int, int>> closestSplitPair(vector<pair<int, int>> Px, vector<pair<int, int>> Py, double delta);
vector<pair<int, int>> bruteForceClosestPair(vector<pair<int, int>> &v);

int main()
{
    //This code works for any n>=2 points, where two points cannot be coincident in input like (2,1) and (2,1)
    //points can have same x coordinate or same y coordinate but both can't be equal
    //This code also works if points are not integer just use double

    //All same x example
    //i/p n=4
    //0 0
    //0 100
    //0 2
    //0 50
    //o/p min distance = 2 and points 0,0 and 0,2

    //split pair example
    //i/p n=5
    // 1 10
    // 4 5
    // 6 5
    // 7 5
    // 9 10
    // The best pair is
    // x1-6 y1-5
    // x2-7 y2-5
    // The min distance between these 1

    //all same y example
    //n=4
    // 1 1
    // 5 1
    // 99 1
    // 2 1
    // The best pair is
    // x1-1 y1-1
    // x2-2 y2-1
    // The min distance between these 1

    int n;
    cin >> n;
    int x, y;

    vector<pair<int, int>> Px(n);
    vector<pair<int, int>> Py(n);

    //first denotes x coordinate
    //second denotes y coordinate
    //two points cannot be coincident in input like (2,1) and (2,1)

    for (int i = 0; i < n; i++)
    {
        cin >> x >> y;

        Px[i].first = x;
        Px[i].second = y;

        Py[i].first = x;
        Py[i].second = y;
    }

    //sort by x coordinate ascending, if x coordinate same sort by y coordinate ascending
    sort(Px.begin(), Px.end(), sortByXCoordinate);
    //sort by y coordinate ascending, if y coordinate same sort by x coordinate ascending
    sort(Py.begin(), Py.end(), sortByYCoordinate);

    vector<pair<int, int>> bestPair = closestPair(Px, Py);

    cout << "The best pair is" << endl;
    cout << "x1-" << bestPair[0].first << " "
         << "y1-" << bestPair[0].second << endl;

    cout << "x2-" << bestPair[1].first << " "
         << "y2-" << bestPair[1].second << endl;

    cout << "The min distance between these " << getDistance(bestPair[0], bestPair[1]) << endl;

    return 0;
}

bool sortByXCoordinate(pair<int, int> &p1, pair<int, int> &p2)
{
    int x1 = p1.first;
    int y1 = p1.second;

    int x2 = p2.first;
    int y2 = p2.second;

    if (x1 != x2)
    {
        return x1 < x2;
    }
    else
    {
        return y1 < y2;
    }
}

bool sortByYCoordinate(pair<int, int> &p1, pair<int, int> &p2)
{
    int x1 = p1.first;
    int y1 = p1.second;

    int x2 = p2.first;
    int y2 = p2.second;

    if (y1 != y2)
    {
        return y1 < y2;
    }
    else
    {
        return x1 < x2;
    }
}

vector<pair<int, int>> closestPair(vector<pair<int, int>> Px, vector<pair<int, int>> Py)
{

    int n = Px.size();

    //base case
    if (n <= 3)
    {
        return bruteForceClosestPair(Px);
    }

    int mid = (n / 2);

    vector<pair<int, int>> Lx;
    vector<pair<int, int>> Ly;
    vector<pair<int, int>> Rx;
    vector<pair<int, int>> Ry;

    //left half of Px
    for (int i = 0; i <= mid; i++)
    {
        Lx.push_back(Px[i]);
    }

    //right half of Px
    for (int i = mid + 1; i < n; i++)
    {
        Rx.push_back(Px[i]);
    }

    pair<int, int> midPair = Px[mid];

    //Ly is Lx sorted by y coordinate
    //Ry is Rx sorted by y coordinate
    for (int i = 0; i < n; i++)
    {
        int x = Py[i].first;
        int y = Py[i].second;

        if (x < midPair.first)
        {
            Ly.push_back(Py[i]);
        }
        else if (x > midPair.first)
        {
            Ry.push_back(Py[i]);
        }
        else
        {
            //if x coordinate is median take decision by y coordinate

            if (y <= midPair.second)
            {
                //push mid pair in Ly that is in left half by convention
                Ly.push_back(Py[i]);
            }
            else if (y > midPair.second)
            {
                Ry.push_back(Py[i]);
            }
        }
    }

    //pair of closest points in left half
    vector<pair<int, int>> leftPair = closestPair(Lx, Ly);

    //pair of closest points in right half
    vector<pair<int, int>> rightPair = closestPair(Rx, Ry);

    double leftDistance = getDistance(leftPair[0], leftPair[1]);

    double rightDistance = rightPair.size() > 0 ? getDistance(rightPair[0], rightPair[1]) : -1;

    double delta = rightPair.size() > 0 ? min(leftDistance, rightDistance) : leftDistance;

    //pair of closest points which are split pair
    vector<pair<int, int>> splitPair = closestSplitPair(Px, Py, delta);

    //finding minimum of all and return the best pair
    if (splitPair.size() > 0)
    {
        return splitPair;
    }

    else if (rightDistance == -1 || leftDistance < rightDistance)
    {
        return leftPair;
    }

    return rightPair;
}

double getDistance(pair<int, int> &v1, pair<int, int> &v2)
{
    int x1 = v1.first;
    int y1 = v1.second;

    int x2 = v2.first;
    int y2 = v2.second;

    long long diffX = x2 - x1;
    long long diffY = y2 - y1;

    //euclidean distance sqrt((x2-x1)^2 + (y2-y1)^2)
    return sqrt(pow(diffX, 2) + pow(diffY, 2));
}

vector<pair<int, int>> closestSplitPair(vector<pair<int, int>> Px, vector<pair<int, int>> Py, double delta)
{
    int mid = Px.size() / 2;
    int medianX = Px[mid].first;

    double low = medianX - delta;
    double high = medianX + delta;

    // sorted by y coordinate and  x coordinate following low<x<high
    vector<pair<int, int>> Sy;

    for (auto p : Py)
    {
        if (low < p.first && p.first < high)
        {
            Sy.push_back(p);
        }
    }

    double minDist = delta;
    vector<pair<int, int>> bestPair;

    int l = Sy.size();

    for (int i = 0; i < l; i++)
    {
        //only need to check 7 points
        for (int j = i + 1; j < l && j <= (i + 7); j++)
        {

            double d = getDistance(Sy[i], Sy[j]);

            if (d < minDist)
            {
                minDist = d;
                if (bestPair.size() > 0)
                {
                    bestPair[0] = Sy[i];
                    bestPair[1] = Sy[j];
                }
                else
                {
                    bestPair.push_back(Sy[i]);
                    bestPair.push_back(Sy[j]);
                }
            }
        }
    }

    //This function returns empty vector if all have distance > delta,
    // else it returns best split pair having distance
    //less than delta
    return bestPair;
}

vector<pair<int, int>> bruteForceClosestPair(vector<pair<int, int>> &v)
{

    //basic brute force closest pair used for n<=3
    int n = v.size();

    if (n == 1)
    {
        //empty vector return in case of n=1
        //this case can occur if n=3 and left half has 2 points and right half has 1 point
        return {};
    }

    double minDist = -1;

    vector<pair<int, int>> bestPair(2);

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            double d = getDistance(v[i], v[j]);

            if (minDist == -1 || d < minDist)
            {
                minDist = d;
                bestPair[0] = v[i];
                bestPair[1] = v[j];
            }
        }
    }

    return bestPair;
}
