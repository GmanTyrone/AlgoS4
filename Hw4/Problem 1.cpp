/*
410921353
Luis Franco
Given a set of n keywords S = {k1 , k2 ,…, kn } where no word is a part of another word.
Find a sentence string T such that for all ki belongs to S => ki belongs to T and | T |(i.e. the length of T) is minimized.

Time complexity: O(n^2 * 2^n)
Space complexity: O(n * 2^n)
*/

#include<bits/stdc++.h>

using namespace std;

string sentenceString(vector<string>& A) {
        //Gets the number of words in the array
        const int n = A.size();
        //Generate vector to store the values
        vector<vector<int> > values(n, vector<int>(n));

        //Iterate over each word
        for(int i = 0; i < n; i++)
        //Iterate over each word (nested)
            for(int j = 0; j < n; j++){
                //Gets the length of the word j
                values[i][j] = A[j].length();
                //From 1 to the minimal length between the 2 words in test
                for(int k = 1; k <= min(A[i].length(), A[j].length()); k++){
                    //concatenate the substrings with the maximum possible k (maximum common letters)
                    if(A[i].substr(A[i].length()- k) == A[j].substr(0, k)){
                      //and store in the vector
                        values[i][j] = A[j].length() - k;
                    }
                }
            }

        vector<vector<int> > dp(1<<n, vector<int>(n, INT_MAX/2));
        vector<vector<int> > parent(1<<n, vector<int>(n, -1));
        for(int i = 0; i < n; i++){ dp[1<<i][i] = A[i].length();}

        for(int s = 1; s < (1<<n); s++){
            for(int j = 0; j < n; j++){
                if(!s&(1<<j)) continue;
                int ps = s & ~(1<<j);
                for(int i = 0; i < n; i++){
                    if(dp[s][j] > dp[ps][i] + values[i][j]){
                        dp[s][j] = dp[ps][i] + values[i][j];
                        parent[s][j] = i;
                    }
                }
            }
        }

        string result;
        //Generates iterator
        auto it = min_element(begin(dp.back()), end(dp.back()));
        int cur = it - begin(dp.back());
        int s = (1 << n) - 1;
        while(s){
            int pre = parent[s][cur];
            //Concatenates whole word to result
            if(pre < 0) result = A[cur] + result;
            //Concatenates word without shared letters to previous, to the result
            else result = A[cur].substr(A[cur].length() - values[pre][cur]) + result;
            s &= ~(1<<cur);
            cur = pre;
        }
        return result;
    }

  int main(){

     vector<string> testarray = {"hello", "low", "owl"};

	cout << "Minimized string = "
		<< sentenceString(testarray);
    return 0;
}
