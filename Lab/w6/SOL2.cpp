#include<bits/stdc++.h>
#define LL long long
#define N 2005
#define M 10005

using namespace std;

int dp[N][M], w[N], sum[N];
int pre[N][M], ans[N];

int main()
{
    int t, i, j, k, V, n, vj=-1;
    cin >> t; //testCases
    while (t--)
    {
        cin >> V;//Lenght of Ferry
        V *= 100;
        memset (dp, 0, sizeof(dp));
        dp[0][0] = 1;
        n = 0;
        sum[0] = 0;
        //K is cars lengths N is number of cars
        while(cin >> k, k)
        {
            ++n;
            w[n] = k;
            sum[n] = sum[n-1] + k;
        }
        //iterates over n O(n)
        for (i = 1; i <= n; i++)
        {
            //iterates over length of ferry now O(n*V)
            for (j = 0; j <= V; j++)
            {
                if (j >= w[i] && dp[i-1][j-w[i]]) {
                    k = i;
                    vj = j;
                    dp[i][j] = 1;
                    pre[i][j] = j-w[i];
                } else if (sum[i]-j <= V && dp[i-1][j]) {
                    k = i;
                    vj = j;
                    dp[i][j] = 1;
                    pre[i][j] = j;
                }
            }
        }
        i = k;
        while (i--)//another iteration over n O(2*n*V)
        {
            j = pre[i+1][vj];
            if (j == vj) ans[i] = 1;
            else ans[i] = 0;
            vj = j;
        }
        cout << k << endl;
        for (i = 0; i < k; i++)//Over n again O(3n*V)
        {
            if (ans[i]) puts ("port");
            else puts ("starboard");
        }
        if (t) puts("");
    }
    return 0;
}
