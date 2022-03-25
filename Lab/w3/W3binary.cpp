#include<iostream>
#include <bits/stdc++.h>

using namespace std;

double vol[10000];
int N;

int pieces(double mid)
{
    int cnt=0;
    for(int i=0;i<N;i++)
        cnt+=(int)(vol[i]/mid);
return cnt;
}


int main()
{
    int tc,F;

    cin>>tc;
    while(tc--)
    {
        cin>>N>>F;
        F++;
        for(int i=0;i<N;i++)
        {
            cin>>vol[i];
            vol[i]=(vol[i]*vol[i]*M_PI);
        }

        //binary search
        double high=INT_MAX,low=0,mid;
        for(int i=0;i<100;i++)
        {
            mid=(high+low)/2;
            if(pieces(mid)>=F)
                low=mid;
            else high=mid;
        }

        printf("%.4lf\n",mid);

    }
    return 0;
}
