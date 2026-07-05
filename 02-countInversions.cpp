#include <iostream>
#include <vector>
using namespace std;

int inversionCount(vector<int> &arr);
int mergeSortAndCntInv(vector<int> &arr, int s, int e);
int mergeAndCntInv(vector<int> &arr, int s, int mid, int e);

int main()
{

    //Given an array of integers arr[]. You have to find the Inversion Count of the array.
    // Note : Inversion count is the number of pairs of elements (i, j) such that i < j and arr[i] > arr[j].

    // Examples:

    // Input: arr[] = [2, 4, 1, 3, 5]
    // Output: 3
    // Explanation: The sequence 2, 4, 1, 3, 5 has three inversions (2, 1), (4, 1), (4, 3).
    // Input: arr[] = [2, 3, 4, 5, 6]
    // Output: 0
    // Explanation: As the sequence is already sorted so there is no inversion count.
    // Input: arr[] = [10, 10, 10]
    // Output: 0
    // Explanation: As all the elements of array are same, so there is no inversion count.

    int n;
    cin >> n;

    vector<int> arr(n);

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << "Number of inversions = " << inversionCount(arr) << endl;

    return 0;
}

int inversionCount(vector<int> &arr)
{
    // Code Here
    int n = arr.size();
    int inv = mergeSortAndCntInv(arr, 0, n - 1);

    return inv;
}

int mergeSortAndCntInv(vector<int> &arr, int s, int e)
{

    if (s == e)
    {
        return 0;
    }

    int mid = (s + e) / 2;

    int l = mergeSortAndCntInv(arr, s, mid);
    int r = mergeSortAndCntInv(arr, mid + 1, e);

    int split = mergeAndCntInv(arr, s, mid, e);

    return l + r + split;
}

int mergeAndCntInv(vector<int> &arr, int s, int mid, int e)
{

    int i = s;
    int j = mid + 1;

    int size = e - s + 1;
    int leftSize = mid - s + 1;
    int splitInv = 0;

    vector<int> temp;

    while (i <= mid && j <= e)
    {
        if (arr[i] <= arr[j])
        {
            temp.push_back(arr[i]);
            i += 1;
        }
        else
        {
            splitInv += leftSize - (i - s);
            temp.push_back(arr[j]);
            j += 1;
        }
    }

    while (i <= mid)
    {
        temp.push_back(arr[i]);
        i += 1;
    }

    while (j <= e)
    {
        temp.push_back(arr[j]);
        j += 1;
    }

    for (int k = s; k <= e; k++)
    {
        arr[k] = temp[k - s];
    }

    return splitInv;
}
