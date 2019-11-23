#include "../include/the_messenger.hpp"
#include <vector>
#include <string>
#include <iostream>

using namespace std;


class the_messenger_implementation : public the_messenger
{
public:
    int solve(int, int, int, string);
    int isSubstring(string, string);
};

int the_messenger_implementation :: solve(int x, int y, int l, string m)
{
    //x is the cost for each new single character added to the current message c
    //y is the cost for adding each substring of the current character c 
    //l is the length of the message
    // string m is the message itself
    string c = ""; //the current string
    int cost=0; //the cost variable
    //int m, n;
    int f;
    int res;
    int act;
    //initially always put the first character of m into c unless m itself is null
    //strcat(c, m[0]);
    //c.append(m[0]);
    c = m[0];
    //cout << c;
    cost = cost + x;
    for(int i=1; i<=l; i++)
    {
        if(c.length()==l)
                break;
        //f = c.length();
        for(int j=l-1; j>=i; j--)
        {
            if(c.length()==l)
                break;
            res = isSubstring(m.substr(i,j),c);
            if(res < 0 && j == i)
            {
                cost = cost + x;
                c = c + m[i];
            }
            if(res >= 0)
            {
                // if(x < y)
                // {
                //     act = x;
                // }
                // else
                // {
                //     act = y;
                // }
                act = std::min(x,y);
                //cout << act;
                cost = cost + act;
                c = c + m.substr(i,j);
            }
            // else
            // {
            //     continue;
            // }
            
            
            
            //c = c + m[]
        }
        if(c.length()==l)
                break;
    }
    return cost;


} 

int the_messenger_implementation :: isSubstring(string s1, string s2) 
{ 
    int M = s1.length(); 
    int N = s2.length(); 
  
    /* A loop to slide pat[] one by one */
    for (int i = 0; i <= N - M; i++) { 
        int j; 
  
        /* For current index i, check for pattern match */
        for (j = 0; j < M; j++) 
            if (s2[i + j] != s1[j]) 
                break; 
  
        if (j == M) 
            return i; 
    } 
  
    return -1; 
} 