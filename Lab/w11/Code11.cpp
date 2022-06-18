#include <bits/stdc++.h>
#define eps 1e-6

using namespace std;

double W[105][105];
int N, M;
int mx[105], my[105];
double lx[105], ly[105];
int x[105], y[105];
int hungary(int nd) {
    int i;
    x[nd] = 1;
    for(i = 1; i <= M; i++) {
        if(y[i] == 0 && fabs(W[nd][i]-lx[nd]-ly[i]) < eps) {
            y[i] = 1;
            if(my[i] == 0 || hungary(my[i])) {
                my[i] = nd;
                return 1;
            }
        }
    }
    return 0;
}
double minTime() {
    int i, j, k;
    double d;
    //sets the arrays to
    memset(mx, 0, sizeof(mx));
    memset(my, 0, sizeof(my));
    memset(lx, 0, sizeof(lx));
    memset(ly, 0, sizeof(ly));
    for(i = 1; i <= N; i++) //O(n) times
        for(j = 1, lx[i] = W[i][j]; j <= M; j++)//nested O(m)
            lx[i] = lx[i] > W[i][j] ? lx[i] : W[i][j];
    for(i = 1; i <= N; i++) {//O(n)
        while(1) {
            //sets them to 0
            memset(x, 0, sizeof(x));
            memset(y, 0, sizeof(y));
            if(hungary(i))  break;//which can go for O(m)
            d = -1;//-1
            for(j = 1; j <= N; j++) { //nested O(n)
                if(x[j]) {
                    for(k = 1; k <= M; k++)
                        if(!y[k])
                        d = d < lx[j]+ly[k]-W[j][k] ? d : lx[j]+ly[k]-W[j][k];
                }
            }
            if(d == -1)  break; //-1
            for(j = 1; j <= N; j++) //second O(n)
                if(x[j])    lx[j] -= d;
            for(j = 1; j <= M; j++)//O(m)
                if(y[j])    ly[j] += d;
        }
    }
    double res = 0;
    for(i = 1; i <= M; i++) {
        if(my[i])
            res += W[my[i]][i];
    }
    return res;
}
int main() {
    int n, m;
    while ((cin>>n>>m)&&n&&m){
        if(n == 0 && m == 0)
            break;
        N = n, M = m;
        int i, j;
        for(i = 1; i <= n; i++) {
            for(j = 1; j <= m; j++) {
                cin >> W[i][j];
                W[i][j] *= -1;
            }
        }
        cout << setprecision(2) << fixed << -minTime()/n+eps << endl;
    }
    return 0;
}
