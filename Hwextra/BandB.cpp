#include <bits/stdc++.h>

using namespace std;

const int N = 20;
int final_path[N + 1];
bool visited[N];
double solution = INT_MAX;

struct coordinate {
    int x;
    int y;
};

double firstMin(double adj[N][N], int i) {
    double min = INT_MAX;
    for (int j = 0; j < N; j++)
        if (adj[i][j] < min && i != j)
            min = adj[i][j];
    
    return min;
}

double secndMin(double adj[N][N], int i) {
    double first = INT_MAX;
    double second = INT_MAX;

    for (int j = 0; j < N; j++) {
        if (i == j)
            continue;

        if (adj[i][j] <= first) {
            second = first;
            first = adj[i][j];
        }

        else if (adj[i][j] <= second && adj[i][j] != first)
            second = adj[i][j];
    }

    return second;
}

void recordTsp(double adj[N][N], double bound1, double curW, int level, int curPath[]) {
    if (level == N) {
        if (adj[curPath[level - 1]][curPath[0]] != 0) {
            double curSol = curW + adj[curPath[level - 1]][curPath[0]];

            if (curSol < solution) 
                solution = curSol;
        }
        return;
    }

    for (int i = 0; i < N; i++) {
        if (adj[curPath[level - 1]][i] != 0 && visited[i] == false) {
            double tmp = bound1;
            curW += adj[curPath[level - 1]][i];

            if (level == 1)
                bound1 -= ((firstMin(adj, curPath[level - 1]) + firstMin(adj, i)) / 2);

            else
                bound1 -= ((secndMin(adj, curPath[level - 1]) + firstMin(adj, i)) / 2);
            
            if (bound1 + curW < solution) {
                curPath[level] = i;
                visited[i] = true;

                recordTsp(adj, bound1, curW, level + 1, curPath);
            }

            curW -= adj[curPath[level - 1]][i];
            bound1 = tmp;

            memset(visited, false, sizeof(visited));
            for (int j = 0; j <= level - 1; j++)
                visited[curPath[j]] = true;
        }
    }
}

void TSP(double adj[N][N]) {
    int curPath[N + 1];

    int bound1 = 0;
    memset(curPath, -1, sizeof(curPath));
    memset(visited, 0, sizeof(visited));

    for (int i = 0; i < N; i++)
        bound1 += (firstMin(adj, i) + secndMin(adj, i));

    bound1 = (bound1 & 1) ? bound1 / 2 + 1 : bound1 / 2;

    visited[0] = true;
    curPath[0] = 0;
    
    recordTsp(adj, bound1, 0, 1, curPath);
}

double distance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}

int main() {
    coordinate coorList[N];

    int n, x, y;
    for (int i = 0; i < N; i++) {
        scanf("%d%d%d", &n, &x, &y);
        coorList[i].x = x;
        coorList[i].y = y;
    }

    double adj[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j)
                adj[i][j] = 0;

            else 
                adj[i][j] = distance(coorList[i].x, coorList[i].y, coorList[j].x, coorList[j].y);
        }
    }

    TSP(adj);
    printf("%.3lf\n", solution);

    return 0;
}
