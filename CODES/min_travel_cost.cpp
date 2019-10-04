#include<iostream>
#include<limits>
#include<algorithm>
using namespace std;

int prices[5][5] = { {INT_MAX,4,8,15,INT_MAX},{INT_MAX,INT_MAX,5,9,12},{INT_MAX,INT_MAX,INT_MAX,INT_MAX,9},{INT_MAX,INT_MAX,INT_MAX,INT_MAX,2},
{INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX} };

int cost = 0;

int ticket(int **prices,int start,int end)
{
    for (int i = 0; i < 5; i++)
    {
        
    }
    
}

int main()
{
    cout<<ticket(prices,0,4);
    return 0;
}