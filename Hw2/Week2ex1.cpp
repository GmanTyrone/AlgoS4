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
int maxMidsum(int arr[], int l, int m, int h)
{
	// sum to the left
	int sum = 0;
	int left_sum = INT_MIN;
	for (int i = m; i >= l; i--) {
		sum = sum + arr[i];
		if (sum > left_sum)left_sum = sum;
	}

	// sum to the right
	sum = 0;
	int right_sum = 0;
	for (int i = m + 1; i <= h; i++) {
		sum = sum + arr[i];
		if (sum > right_sum)right_sum = sum;
	}

	//max of (total,left, right)
	return max(left_sum + right_sum, left_sum, right_sum);
}

int maxSubSum(int arr[], int low, int high)
{
	//Base case array size 1
	if (low == high)
		return arr[low];

	int mid = (low + high) / 2;
	//recursive max call
	return max(maxSubSum(arr, low, mid),maxSubSum(arr, mid + 1, high),maxMidsum(arr, low, mid, high));
}

int main()
{
	int arr[] = { 3, -4, 5, -2, -2, 6, -3, 5, -3, 2};
	int n = end(arr)-begin(arr);
	int max_sum = maxSubSum(arr, 0, n - 1);
	cout<<"Maximum Subarray Sum: "<<max_sum<<endl;
	return 0;
}
