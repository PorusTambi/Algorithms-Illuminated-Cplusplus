#include <iostream>
#include <queue>
#include <functional>

using namespace std;

struct maxHeapCmp
{

    //should return true if a,b needs to be swapped a is up b is down
    bool operator()(int a, int b)
    {
        return a < b;
    }
};

struct minHeapCmp
{

    //should return true if a,b needs to be swapped a is up b is down
    bool operator()(int a, int b)
    {
        return a > b;
    }
};

int main()
{

    //by default maxHeap
    priority_queue<int> maxHeap1;

    //max heap
    //constructor arguments
    //1. datatype
    //2. container container can be vector, deque
    //3. comparator -  a structure with overloaded fn call operator ()
    priority_queue<int, vector<int>, maxHeapCmp> maxHeap;

    priority_queue<int, vector<int>, minHeapCmp> minHeap;
    //can also use
    priority_queue<int, vector<int>, greater<int>> minHeap2;

    minHeap.push(-1);
    minHeap.push(999);
    minHeap.push(7838);
    minHeap.push(1000);

    cout << endl
         << "Min heap " << endl;

    int size = minHeap.size();
    for (int i = 0; i < size; i++)
    {
        cout << minHeap.top() << " ";
        minHeap.pop();
    }
    cout << endl;

    //any array of any size with random elements
    int a[5] = {66, 222, 13, 3134, 25};

    //this is much more efficient than pushinh each element one by one
    //think....
    priority_queue<int> mh(a, a + 5);
    cout << mh.top() << endl;
    cout << a[0] << endl;

    //Please note
    // Unlike a std::vector or a std::set,
    //a standard priority_queue does not allow you to look at or touch anything except the very top.

    // Modify an element: ❌ Not supported.
    // You cannot change a value inside the queue
    //because the heap property would break,
    //and the structure has no way to "re-heapify" from a random middle point.

    // Delete a random element: ❌ Not supported. There is no pq.erase(iterator) or pq.remove(value)

    minHeap2.push(1);
    minHeap2.push(0);

    cout << minHeap2.top() << endl;

    return 0;
}
