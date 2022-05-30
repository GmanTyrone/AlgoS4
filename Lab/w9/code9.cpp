#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

vector<vii> AdjList;
priority_queue<ii, vector<ii>, greater<ii> > pq;

int main() {
    int N, n, m, S, T, a, b, w;
    vi dist;
    cin>>N;
    for(int i=0; i<N; i++){
        cin >> n >> m >> S >> T;
        AdjList.assign(n, vii());
        while (m--) {
            cin >> a >> b >> w;
            AdjList[a].push_back(ii(b, w));
            AdjList[b].push_back(ii(a, w));
        }

        dist.assign(n, INT_MAX);
        dist[S] = 0;
        pq.push(ii(0, S));
        while (!pq.empty()) {
            ii front = pq.top(); pq.pop();
            int d = front.first, u = front.second;
            if (d == dist[u]) {
                for (int j= 0 ; j< AdjList[u].size() ; j++){
                    ii v = AdjList[u][j];
                    if (dist[u] + v.second < dist[v.first]) {
                        dist[v.first] = dist[u] + v.second;
                        pq.push(ii(dist[v.first], v.first));
                    }
                }
            }
        }
        cout <<"Case #"<<i+1<<": ";
        if (dist[T] != INT_MAX)
            cout << dist[T] << endl;
        else
            cout << "unreachable" << endl;

    }
    return 0;
}
