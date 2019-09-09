#include <iostream>
#include <algorithm>
using namespace std;
int f2(int, int *, int *, int *, int *);

int f1(int n, int *t1, int *t2, int *a1, int *a2)
{
    if (n == 0)
    {
        return 2 + a1[0];
    }

    int val = min(f1(n - 1, t1, t2, a1, a2), (f2(n - 1, t1, t2, a1, a2) + t2[n - 1])) + a1[n];

    return val;
}

int f2(int n, int *t1, int *t2, int *a1, int *a2)
{
    if (n == 0)
    {
        return 4 + a2[0];
    }

    int val = min(
                  f2(n - 1, t1, t2, a1, a2),
                  (f1(n - 1, t1, t2, a1, a2) + t1[n - 1])) +
              a2[n];

    return val;
}

int assembly(int n, int *t1, int *t2, int *a1, int *a2)
{
    // if(n==0)
    // {
    //     return 2 + a1[1];
    // }

    {
        return min(f1(n, t1, t2, a1, a2) + 3, f2(n, t1, t2, a1, a2) + 2);
    }
}

int main()
{
    int e1 = 2, e2 = 4, x1 = 3, x2 = 2;
    int a1[] = {7, 9, 3, 4, 8, 4};
    int a2[] = {8, 5, 6, 4, 5, 7};
    int t1[] = {2, 3, 1, 3, 4};
    int t2[] = {2, 1, 2, 2, 1};

    cout << assembly(5, t1, t2, a1, a2);

    return 0;
}