#include <bits/stdc++.h>

using namespace std;

bool compare(pair<double, double> a, pair<double, double> b) {
    if (a.first == b.first)
        return a.second > b.second;
    else
        return a.first < b.first;
}

int main() {
    int n;
    double p, r;
    double l, w, dx;

    while (cin >> n >> l >> w) {
        w /= 2.0;
        vector<pair<double, double> > v;
        for (int i=0; i<n; i++) {//O(n)
            cin >> p >> r;
            if (r > w){
                dx = sqrt(r*r - w*w);
                v.push_back({p-dx, p+dx});
            }
        }
        sort(v.begin(), v.end(), compare);//O(nlgn)

        int count = 0;
        double right = 0.0;
        for (int i = 0; i < v.size(); i++){//at worst O(n)
            if (v[i].first > right) break;
            for (int j = i+1; j < v.size() && v[j].first <= right; j++){
                if (v[j].second > v[i].second){
                    i = j;
                }
            }
            count++;
            right = v[i].second;
            if (right >= l) break;
        }

        if (right >= l) cout << count << endl;
        else cout << "-1" << endl;
    }
    return 0;
}
