#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int findMedian(vector<int> &a, int l, int r);
int dselect(vector<int> &a, int l, int r, int k);
pair<int, int> partition(vector<int> &a, int l, int r, int pivotEl);
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
         << "smallest element is " << dselect(a, 0, n - 1, k - 1) << endl;

    return 0;
}

int dselect(vector<int> &a, int l, int r, int k)
{

    //base case
    if (l == r)
    {
        return a[l];
    }

    //take group size as 5
    //array having each group median
    vector<int> aux;

    for (int i = l; i <= r; i += 5)
    {
        int median = findMedian(a, i, r);
        aux.push_back(median);
    }

    int auxSize = aux.size();

    int pivotEl = dselect(aux, 0, auxSize - 1, auxSize / 2);

    pair<int, int> p = partition(a, l, r, pivotEl);

    if (k > p.first && k < p.second)
    {
        return pivotEl;
    }
    else if (k <= p.first)
    {
        return dselect(a, l, p.first, k);
    }
    return dselect(a, p.second, r, k);
}

int findMedian(vector<int> &a, int l, int r)
{
    //find median of group of 5 elements
    int start = l;
    int end = l + 4 > r ? r : l + 4;

    sort(a.begin() + start, a.begin() + end + 1);

    int groupSize = end - start + 1;

    if (groupSize == 5)
    {
        return a[start + 2];
    }

    else
    {
        return a[start + (groupSize / 2)];
    }
}

pair<int, int> partition(vector<int> &a, int l, int r, int pivotEl)
{
    int i = l;

    while (i <= r)
    {

        if (a[i] == pivotEl)
        {
            i++;
        }
        else if (a[i] < pivotEl)
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
