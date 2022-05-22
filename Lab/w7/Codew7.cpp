#include<bits/stdc++.h>

using namespace std;

#define SET(a) memset(a,-1,sizeof(a))

int DynamicArray[310][310];
string strand1,strand2,s[10000];
int s1l,s2l;
int fillarray(int i, int j)
{
    if(i==s1l || j==s2l)    return 0;
    if(DynamicArray[i][j]!=-1)      return DynamicArray[i][j];
    int ret=0;
    if(strand1[i]==strand2[j])
        ret=1+fillarray(i+1,j+1);

    return DynamicArray[i][j]=ret;
}

int main()
{
    int kk=1;
    while(getline(cin,strand1))
    {
        if(kk!=1)
            getline(cin,strand1);
        getline(cin,strand2);
        s1l=strand1.length();
        s2l=strand2.length();
        int res=0;
        SET(DynamicArray);
        for(int i=0;i<s1l;i++)
            for(int j=0;j<s2l;j++)
                res=max(res,fillarray(i,j));
        if(kk!=1)
            cout<<endl;

        if(!res)
            cout<<"No common sequence."<<endl;
        else
        {
            int cnt=0;
            for(int i=0;i<s1l;i++)
                for(int j=0;j<s2l;j++)
                    if(DynamicArray[i][j]==res)
                    {
                        s[cnt]="";
                        for(int k=i;k<i+res;k++)
                            s[cnt]+=strand1[k];
                        cnt++;
                    }
            sort(s,s+cnt);
            cout<<s[0]<<endl;

            for(int i=1;i<cnt;i++)
                if(s[i]!=s[i-1])
                    cout<<s[i]<<endl;
            cout<<endl;
        }
        kk++;
    }
}
