#include <iostream>
using namespace std;

struct MinHeap
{
    int *harr;
    int capacity, heap_size;
    MinHeap(int cap)
    {
        heap_size = 0;
        capacity = cap;
        harr = new int[cap];
    }
    int extractMin();
    void deleteKey(int i);
    void insertKey(int k);
    void MinHeapify(int i);
    void decreaseKey(int i, int new_val);
    void swap(int &a, int &b);
};

// Function to extract minimum value in heap and then to store
// next minimum value at first index.
int MinHeap::extractMin()
{
    // Your code here
    if (heap_size == 0)
    {
        return -1;
    }

    int val = harr[0];

    harr[0] = harr[heap_size - 1];
    heap_size -= 1;

    MinHeapify(0);

    return val;
}

// Function to delete a key at ith index.
void MinHeap::deleteKey(int i)
{
    if (heap_size == 0 || i < 0 || i >= heap_size)
    {
        return;
    }

    int ov = harr[i];
    int nv = harr[heap_size - 1];

    // swapy(harr[i], harr[heap_size-1]);
    heap_size -= 1;

    if (ov == nv)
    {
        return;
    }

    else if (nv > ov)
    {
        harr[i] = nv;
        MinHeapify(i);
    }
    else
    {
        decreaseKey(i, nv);
    }
    // Your code here
}

// Function to insert a value in Heap.

void MinHeap::insertKey(int k)
{

    if (heap_size == capacity)
    {
        return;
    }

    harr[heap_size] = k;
    heap_size += 1;

    int i = heap_size - 1;
    int p = (i - 1) >> 1;

    while (i != 0 && harr[i] < harr[p])
    {
        swap(harr[i], harr[p]);
        i = p;
        p = (i - 1) >> 1;
    }
}

// Function to change value at ith index and store that value at first index.
void MinHeap::decreaseKey(int i, int new_val)
{

    if (i < 0 || i >= heap_size)
    {
        return;
    }

    harr[i] = new_val;

    int p = (i - 1) >> 1;

    while (i != 0 && harr[i] < harr[p])
    {
        swap(harr[i], harr[p]);
        i = p;
        p = (i - 1) >> 1;
    }
}

/* You may call below MinHeapify function in
   above codes. Please do not delete this code
   if you are not writing your own MinHeapify */
void MinHeap::MinHeapify(int i)
{

    if (i < 0 || i >= heap_size)
    {
        return;
    }

    int ils = i << 1;
    int l = ils + 1;
    int r = ils + 2;

    int s = i;

    if (l < heap_size && harr[l] < harr[s])
    {
        s = l;
    }
    if (r < heap_size && harr[r] < harr[s])
    {
        s = r;
    }

    if (s != i)
    {
        swap(harr[i], harr[s]);
        MinHeapify(s);
    }
}

void MinHeap::swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int main()
{

    MinHeap m(5);

    m.insertKey(22);
    m.insertKey(0);

    m.deleteKey(1);

    cout << m.extractMin() << endl;
    cout << m.extractMin() << endl;

    return 0;
}