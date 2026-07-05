#include <iostream>
#include <vector>
using namespace std;

class minHeap
{
private:
    vector<int> h;
    // Initialize your data members

public:
    void push(int x)
    {
        // Insert x into the heap
        h.push_back(x);

        int size = h.size();

        int i = size - 1;
        int p = (i - 1) >> 1;

        while (i != 0 && h[i] < h[p])
        {
            swap(h[i], h[p]);
            i = p;
            p = (i - 1) >> 1;
        }

        return;
    }

    void pop()
    {
        // Remove the top (minimum) element
        int size = h.size();
        if (size == 0)
        {
            return;
        }

        swap(h[0], h[size - 1]);
        h.pop_back();

        int i = 0;
        int s = getSmallestInd(i);

        while (s != i)
        {
            swap(h[i], h[s]);
            i = s;
            s = getSmallestInd(i);
        }
    }

    int getSmallestInd(int i)
    {
        int n = h.size();

        int s = i;

        int ils = i << 1;
        int l = ils + 1;
        int r = ils + 2;

        if (l < n && h[l] < h[s])
        {
            s = l;
        }
        if (r < n && h[r] < h[s])
        {
            s = r;
        }
        return s;
    }

    int peek()
    {

        // Return the top element or -1 if empty
        return h.size() == 0 ? -1 : h[0];
    }

    int size()
    {
        // Return the number of elements in the heap
        return h.size();
    }
    void swap(int &a, int &b)
    {
        int temp = a;
        a = b;
        b = temp;
    }
};

int main()
{
    minHeap m;

    m.push(22);
    m.push(0);

    cout << m.peek() << endl;

    m.pop();
    cout << m.peek() << endl;

    return 0;
}