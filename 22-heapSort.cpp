#include <iostream>
#include <vector>
using namespace std;

vector<int> sortArray(vector<int> &nums);
void swap(int &a, int &b);
int getMaxInd(vector<int> &a, int i, int s);
void maxHeapify(vector<int> &a, int i, int s);
void extractMax(vector<int> &a, int s);
void buildMaxHeap(vector<int> &a);

int main()
{
    int n;
    cin >> n;

    vector<int> a(n);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    cout << "Sorted version " << endl;

    sortArray(a);

    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}

vector<int> sortArray(vector<int> &nums)
{

    int n = nums.size();

    buildMaxHeap(nums);

    int currSize = n;
    for (int i = 0; i < n; i++)
    {
        extractMax(nums, currSize);
        currSize -= 1;
    }

    return nums;
}

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int getMaxInd(vector<int> &a, int i, int s)
{
    int ils = i << 1;
    int l = ils + 1;
    int r = ils + 2;

    int b = i;

    if (l < s && a[l] > a[b])
    {
        b = l;
    }
    if (r < s && a[r] > a[b])
    {
        b = r;
    }

    return b;
}

void maxHeapify(vector<int> &a, int i, int s)
{

    int ind = getMaxInd(a, i, s);

    while (ind != i)
    {
        swap(a[i], a[ind]);
        i = ind;
        ind = getMaxInd(a, i, s);
    }
}

void extractMax(vector<int> &a, int s)
{
    swap(a[0], a[s - 1]);
    maxHeapify(a, 0, s - 1);
}

void buildMaxHeap(vector<int> &a)
{
    int n = a.size();
    for (int i = (n - 2) / 2; i >= 0; i--)
    {
        maxHeapify(a, i, n);
    }
}
