#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int n;

	while (cin >> n)
	{
		//Sequence and gets sequence
		vector<int> sequence(n);
		for (int i = 0; i < n; ++i) cin >> sequence[i];


		//Increasing and decreasing sequences
		vector<int> increasing;
		vector<int> decreasing;
		increasing.emplace_back(sequence[0]);
		decreasing.emplace_back(sequence[n - 1]);

		vector<int> num1(n);
		vector<int> num2(n);
		num1[0] = 1;
		num2[n - 1] = 1;
		int cnt1 = 1;
		int cnt2 = 1;

		for (int i = 1; i < n; ++i)
		{
			//increasing
			if (sequence[i] > increasing.back())
			{
				increasing.emplace_back(sequence[i]);
				//adds one element
				num1[i] = ++cnt1;
			}
			else
			{
				//position of next value greater than current one
				auto iterator = lower_bound(increasing.begin(), increasing.end(), sequence[i]);
				//moves the iterator
				*iterator = sequence[i];

				num1[i] = (iterator - increasing.begin() + 1);
			}

			//decreasing
			int j = n - i - 1;
			if (sequence[j] > decreasing.back())
			{
				decreasing.emplace_back(sequence[j]);
				num2[j] = ++cnt2;
			}
			else
			{
				auto iterator = lower_bound(decreasing.begin(), decreasing.end(), sequence[j]);
				*iterator = sequence[j];
				num2[j] = (iterator - decreasing.begin() + 1);
			}
		}

		//Returns minimum count
		int t = min(cnt1, cnt2);

		//Looks for the actual biggest sequence
		for (; t > 0; --t)
            for (int i = 0; i < n; ++i)
                if (num1[i] >= t && num2[i] >= t) goto out;

	out:
		cout << t * 2 - 1 << "\n";
	}
}
