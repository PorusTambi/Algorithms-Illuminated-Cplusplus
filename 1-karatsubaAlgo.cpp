#include <iostream>
#include <stack>
#include <string>

using namespace std;

string karatsuba(string x, string y);
string addK(string x, string y);
string subK(string x, string y);
void appPreZeros(string &x, int n, bool app);
void makeEqualLength(string &x, string &y);
string removeLeadingZeros(string x);

int main()
{
    string x;
    string y;

    cin >> x >> y;

    cout << x << "*" << y << endl;

    cout << karatsuba(x, y) << endl;

    // Given two non-negative integers num1 and num2
    //represented as strings, return the product of num1 and num2, also represented as a string.

    // Note: You must not use any built-in BigInteger library or convert the inputs to integer directly.

    // Example 1:
    // Input: num1 = "2", num2 = "3"
    // Output: "6"

    // Example 2:
    // Input: num1 = "123", num2 = "456"
    // Output: "56088"

    // Constraints:

    // 1 <= num1.length, num2.length <= 200
    // num1 and num2 consist of digits only.
    // Both num1 and num2 do not contain any leading zero, except the number 0 itself.

    return 0;
}

string karatsuba(string x, string y)
{

    //make equal length strings
    makeEqualLength(x, y);

    int length = x.length();

    if (length == 1)
    {
        return to_string((x[0] - '0') * (y[0] - '0'));
    }

    int mid = length / 2;

    string a = x.substr(0, mid);
    string b = x.substr(mid);

    string c = y.substr(0, mid);
    string d = y.substr(mid);

    string ac = karatsuba(a, c);
    string bd = karatsuba(b, d);

    string aPlusB = addK(a, b);
    string cPlusD = addK(c, d);
    string abcd = karatsuba(aPlusB, cPlusD);

    string adbc = subK(subK(abcd, ac), bd);

    int powBy2 = length - mid;
    appPreZeros(ac, 2 * powBy2, true);
    appPreZeros(adbc, powBy2, true);

    string res = addK(addK(ac, adbc), bd);

    return removeLeadingZeros(res);
}

string addK(string x, string y)
{

    makeEqualLength(x, y);

    int n = x.length();

    stack<int> s;

    int carry = 0;

    for (int i = n - 1; i >= 0; i--)
    {
        int a = x[i] - '0';
        int b = y[i] - '0';

        int c = a + b + carry;

        carry = c / 10;

        s.push(c % 10);
    }

    if (carry > 0)
    {
        s.push(carry);
    }

    string res = "";
    while (!s.empty())
    {
        string t = to_string(s.top());
        res += t;
        s.pop();
    }

    return res;
}

string subK(string x, string y)
{

    makeEqualLength(x, y);

    int n = x.length();

    stack<int> s;

    int borrow = 0;

    for (int i = n - 1; i >= 0; i--)
    {
        int a = x[i] - '0';
        int b = y[i] - '0';
        int c = 0;
        int t = a - b - borrow;

        if (t >= 0)
        {
            c = t;
            borrow = 0;
        }
        else
        {
            borrow = 1;
            c = t + 10;
        }

        s.push(c);
    }

    string res = "";
    while (!s.empty())
    {
        string t = to_string(s.top());
        res += t;
        s.pop();
    }

    return res;
}

void appPreZeros(string &x, int n, bool app)
{
    string zeros = string(n, '0');
    if (app)
    {
        x += zeros;
    }

    else
    {
        x = zeros + x;
    }
}

void makeEqualLength(string &x, string &y)
{
    //make equal length strings
    int n1 = x.length();
    int n2 = y.length();

    if (n1 > n2)
    {
        appPreZeros(y, n1 - n2, false);
    }
    else if (n2 > n1)
    {
        appPreZeros(x, n2 - n1, false);
    }
}

string removeLeadingZeros(string x)
{
    int n = x.length();
    int i = 0;
    while (i < n && x[i] == '0')
    {
        i++;
    }

    if (i == n)
    {
        return "0";
    }

    return x.substr(i);
}
