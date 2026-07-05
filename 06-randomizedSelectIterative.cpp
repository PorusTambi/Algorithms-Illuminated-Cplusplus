#include <iostream>
#include <vector>
#include <utility>
#include <random>

using namespace std;

int rselect(vector<int> &a, int l, int r, int k);
int choosePivot(int l, int r);
pair<int, int> partition(vector<int> &a, int l, int r, int pivot);
void swap(int &a, int &b);

int main()
{
    int n, k;
    cin >> n >> k;

    vector<int> a(n);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    cout << "The " << k << "th "
         << "smallest element is " << rselect(a, 0, n - 1, k - 1) << endl;

    return 0;
}

int rselect(vector<int> &a, int l, int r, int k)
{

    while (l < r)
    {
        if (l == r)
        {
            return a[l];
        }

        int pivot = choosePivot(l, r);

        pair<int, int> p = partition(a, l, r, pivot);

        if (k > p.first && k < p.second)
        {
            return a[k];
        }

        else if (k <= p.first)
        {
            r = p.first;
        }

        else
        {
            l = p.second;
        }
    }
    return a[k];
}

int choosePivot(int l, int r)
{
    static random_device rd;
    static mt19937 gen(rd());

    uniform_int_distribution<int> dist(l, r);
    int randomNumber = dist(gen);
    return randomNumber;
}

pair<int, int> partition(vector<int> &a, int l, int r, int pivot)
{

    int i = l;
    int el = a[pivot];

    while (i <= r)
    {

        if (a[i] == el)
        {
            i++;
        }
        else if (a[i] < el)
        {
            swap(a[i], a[l]);
            l++;
            i++;
        }
        else
        {
            swap(a[i], a[r]);
            r--;
        }
    }

    return {l - 1, r + 1};
}

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}
