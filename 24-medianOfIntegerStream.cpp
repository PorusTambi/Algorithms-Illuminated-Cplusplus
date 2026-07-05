#include <iostream>
#include <queue>

using namespace std;

class MedianFinder
{
public:
    struct cmp
    {
        bool operator()(int a, int b)
        {
            return a > b;
        }
    };
    priority_queue<int> h1;
    priority_queue<int, vector<int>, cmp> h2;
    MedianFinder()
    {
    }

    void addNum(int num)
    {
        int currSize = h1.size() + h2.size();

        if ((currSize & 1) == 0)
        {
            h1.push(num);
            h2.push(h1.top());
            h1.pop();
        }

        else
        {
            h2.push(num);
            h1.push(h2.top());
            h2.pop();
        }
    }

    double findMedian()
    {
        int currSize = h1.size() + h2.size();
        if ((currSize & 1) == 0)
        {
            return (h1.top() + h2.top()) / 2.0;
        }

        return h2.top();
    }
};

int main()
{
    //     The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value, and the median is the mean of the two middle values.

    // For example, for arr = [2,3,4], the median is 3.
    // For example, for arr = [2,3], the median is (2 + 3) / 2 = 2.5.
    // Implement the MedianFinder class:

    // MedianFinder() initializes the MedianFinder object.
    // void addNum(int num) adds the integer num from the data stream to the data structure.
    // double findMedian() returns the median of all elements so far. Answers within 10-5 of the actual answer will be accepted.

    // Example 1:

    // Input
    // ["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
    // [[], [1], [2], [], [3], []]
    // Output
    // [null, null, null, 1.5, null, 2.0]

    // Explanation
    // MedianFinder medianFinder = new MedianFinder();
    // medianFinder.addNum(1);    // arr = [1]
    // medianFinder.addNum(2);    // arr = [1, 2]
    // medianFinder.findMedian(); // return 1.5 (i.e., (1 + 2) / 2)
    // medianFinder.addNum(3);    // arr[1, 2, 3]
    // medianFinder.findMedian(); // return 2.0

    // Constraints:

    // -105 <= num <= 105
    // There will be at least one element in the data structure before calling findMedian.
    // At most 5 * 104 calls will be made to addNum and findMedian.

    // Follow up:

    // If all integer numbers from the stream are in the range [0, 100], how would you optimize your solution?
    //use a array of size 101 search naive all operations are still O(101) = O(1)

    // If 99% of all integer numbers from the stream are in the range [0, 100], how would you optimize your solution?
    // use array for 0 to 100 and self balancing BST for others

    MedianFinder *obj = new MedianFinder();
    obj->addNum(1);
    obj->addNum(0);
    obj->addNum(-1);
    cout << obj->findMedian() << endl;

    return 0;
}