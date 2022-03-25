#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int max(int a, int b, int c)
{
    if (a>b && a>c) return a;
    else if (b>c) return b;
    else return c;
}

//Returns max from right, left, and total sums
int maxCrossingSum(int arr[], int l, int m, int h)
{
	// sum to the left
	int sum = 0;
	int left_sum = INT_MIN;
	for (int i = m; i >= l; i--) {
		sum = sum + arr[i];
		if (sum > left_sum)
			left_sum = sum;
	}

	// sum to the right
	sum = 0;
	int right_sum = 0;
	for (int i = m + 1; i <= h; i++) {
		sum = sum + arr[i];
		if (sum > right_sum)
			right_sum = sum;
	}

	//max of (total,left, right)
	return max(left_sum + right_sum, left_sum, right_sum);
}

int maxSubArraySum(int arr[], int lo, int hi)
{
	//Base case array size 1
	if (lo == hi)
		return arr[lo];

	//middle
	int mid = (lo + hi) / 2;

	//recursive max call
	return max(maxSubArraySum(arr, lo, mid),
			maxSubArraySum(arr, mid + 1, hi),
			maxCrossingSum(arr, lo, mid, hi));
}

int main()
{
	int arr[] = { 2, 3, 4, 5, 7 };
	int n = sizeof(arr) / sizeof(arr[0]);
	int max_sum = maxSubArraySum(arr, 0, n - 1);
	printf("Maximum contiguous sum is %d\n", max_sum);
	getchar();
	return 0;
}
