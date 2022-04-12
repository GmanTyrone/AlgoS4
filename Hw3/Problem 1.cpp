/*
a. The problem has overlapping subproblems which are evaluated again and again so its good for Dynamic programming.
b. Creates an arrays which stores a state (n,w) so it doesn't have to be calculated again
c. Time Complexity: O(N*W).
   Space Complexity: O(W)*/

#include <bits/stdc++.h>
using namespace std;
int knapSack(int W, int wt[], int val[], int n)
{
	// making and initializing dp array
	int dp[W + 1];
	memset(dp, 0, sizeof(dp));
	for (int i = 1; i < n + 1; i++) {
		for (int w = W; w >= 0; w--) {
			if (wt[i - 1] <= w)
				// finding the maximum value
				dp[w] = max(dp[w], dp[w - wt[i - 1]] + val[i - 1]);
		}
	}
	return dp[W]; // returning the maximum value of knapsack
}

// Driver code
int main()
{
    int n,budget;
    while (cin >> n){
        int preferences[n];
        int price[n];
        for(int i=0;i<n;i++)
            cin>>preferences[i];
        for(int i=0;i<n;i++)
            cin>>price[i];
        cin>>budget;

        cout << knapSack(budget, price, preferences, n);
    }
    return 0;
}
