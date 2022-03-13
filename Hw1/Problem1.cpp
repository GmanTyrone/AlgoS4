#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    string word;
    getline(cin,word);
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    for(int i=0,j=word.size()-1; i!=j;i++,j--)
    {
        if(word[i]!=word[j])
        {
            cout<<"Not Palindrome"<<endl;
            return 0;
        }
    }
    cout<<"Palindrome"<<endl;
    return 0;
}
