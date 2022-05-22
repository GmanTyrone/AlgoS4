#include<bits/stdc++.h>

using namespace std;

set<string> DNAsequence(const string& a, const string& b) {

   int maxLen = 0;
   vector<vector<int> > longestSequence(a.size(), vector<int>(b.size()));
   set<string> result;

   for(int i = 0; i < a.size(); ++i) {
      for(int j = 0; j < b.size(); ++j) {
         if (a[i] == b[j]) {
            int &next = longestSequence[i][j];
            //because next is a pointer, it also updates the array
            next = i == 0 || j == 0 ? 1 : longestSequence[i - 1][j - 1] + 1;
            int prev = i - next + 1; //Points at the start of the substring

            if (next > maxLen) {
               result.clear();//Clears the set if a nex maxLen is found
               result.insert(a.substr(prev, next));
               maxLen = next;//updates the maxlen
            } else if (next == maxLen) {
                //prev points subscripts the string, and gets "next" ammount of letters
               result.insert(a.substr(prev, next));
            }
         }
      }
   }

   return result;
}

int main() {
   string a, b;
   bool first = true;

   while(cin >> a >> b) {
      if (!first)
         cout << endl;
      else
         first = false;

      set<string> result = DNAsequence(a, b);

      if (result.empty())
         cout << "No common sequence."<<endl;
      else {
         for(set<string>::const_iterator it = result.begin();
               it != result.end(); ++it)
            cout << *it <<endl;
      }
   }
}
