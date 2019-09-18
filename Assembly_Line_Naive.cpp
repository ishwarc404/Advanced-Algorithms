#include <iostream>
#include <algorithm>
using namespace std;


int g(int *,int,int);
int g(int *p,int i,int j)
{
  unsigned long int min = 9999999999999;
  int val;
  if(i==j)
  {
      return 0;
  }
  for(int k=i;k<j;k++)
  {

      val = g(p,i,k) + g(p,k+1,j) + (p[i] * p[k] * p[j]);
      if(val < min)
        min = val;
  } 
  return min;
}


int matrix(int *p)
{
    return g(p,1,6);
}

int main()
{
    int p[] = {30,35,15,5,10,20,25};

    cout<< matrix(p);

    return 0;
}