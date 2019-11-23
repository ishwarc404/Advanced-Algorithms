#include<iostream>
using namespace std;
double dp[110][110][110];
int used[110][110][110];
double solve(int a,int b,int c)
 {
  if(a<0 || b<0 || c<0) return 1.0;
  if(used[a][b][c]!=-1) return dp[a][b][c];
  else if( c==0  && b==0) return 1.0;// if c and b becomes 0 than the probability from below this step                                                                       //will always 1.0
  else if(a==0) return 0.0;// if a will be 0 than chance of serviving of a =0;
  else
  {
   used[a][b][c]=1;
    double up1=(double)(a*b);
     double up2=(double)(b*c);
      double up3=(double)(c*a);
    double down=(double)(a*b+b*c+c*a);
    dp[a][b][c]=((up1/down)*solve(a,b-1,c))+// probabilty of killing b
                                                ((up2/down)*solve(a,b,c-1))+  // probabilty of killing c
                                                 ((up3/down)*solve(a-1,b,c));  // probabilty of killing a
    return dp[a][b][c];
  }
 }
int main()
 {
   int a,b,c;
    memset(used,-1,sizeof used);
    cin>>a>>b>>c;
    double a1,b1,c1;
    dp[a][b][c]=1.00;
    a1=solve(a,b,c);
    b1=solve(b,c,a);
    c1=solve(c,a,b);
    printf("%.12lf %.12lf %.12lf",a1,b1,c1);
    
 }
