#include <bits/stdc++.h>

using namespace std;
#define city 20
#define INF 0x3f3f3f3f
#define DBL_MAX 1.7976931348623158e+308

double DP[(1 << city)][city];

struct town {
    town(int num, int p, int q) {
        this->num = num;
        this->p = p;
        this->q = q;
    }
    int num, p, q;
};

double DPsl(double **map, int status, int at) {
    if (DP[status][at] != -1) {
        return DP[status][at];
    }
    int from = 1 << at;
    DP[status][at] = DBL_MAX;
    for (int i = 0; i < city; i++) {
        if (!(1 << i & status) || i == at) continue;
        DP[status][at] = min(DP[status][at], DPsl(map, status - from, i) + map[at][i]);
    }
    return DP[status][at];
}

double Euclidean(town from, town to) {
    return sqrt((from.p - to.p) * (from.p - to.p) + (from.q - to.q) * (from.q - to.q));
}

void initDP(double **map, int size) {
    for (int i = 0; i < 1 << city; i++) {
        for (int j = 0; j < city; j++) {
            DP[i][j] = -1;
        }
    }
    for (int i = 0; i < size; i++) {
        DP[1 << i][i] = map[0][i];
    }
    return;
}

int main(void) {
    int m, p, q;
    vector<town> country;
    while (cin >> m >> p >> q) {
        country.push_back(town(m, p, q));
    }
    if(country.size() > 51) throw std::runtime_error("error");

    double map[country.size()][country.size()] = {0};
    double **pointArray = new double *[country.size()];
    memset(map, 0, sizeof(map));

    for (int i = 0; i < country.size(); i++) {
        for (int j = i + 1; j < country.size(); j++) {
            map[i][j] = map[j][i] = Euclidean(country[i], country[j]);
        }
        pointArray[i] = map[i];
    }

    initDP(pointArray, city);
    int visite = (1 << city) - 1;
    cout<<fixed <<setprecision(3)<<DPsl(pointArray, visite, 0) << endl;
}
