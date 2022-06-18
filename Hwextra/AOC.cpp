#include <bits/stdc++.h>

using namespace std;

#define INF 0x3f3f3f3f
#define ALPHA 2
#define BETA 5
#define RHO 0.7
#define ANTS 5
#define DBL_MAX 1.7976931348623158e+308
#define DBL_MIN 2.2250738585072014e-308

double randFloat(double lowerbound, double upperbound);

class ROAD {
   public:
    ROAD() {}
    ROAD(class town *C, class town *D, double w) {
        this->C = C;
        this->D = D;
        this->w = w;
        this->re_w = 1 / w;
        this->Pheromones = 1000;
        this->score = re_w * Pheromones;
    }

    class town *C, *D;
    double w;
    double re_w, Pheromones, score;
};

class town {
   public:
    town(){};
    town(int n, double x, double y) {
        this->number = n;
        this->x = x;
        this->y = y;
    }

    double x, y;
    int number;
    unordered_map<int, ROAD *> to;

   private:
};
class ants {
   public:
    ants() { distance = 0; }
    vector<ROAD *> path;
    double distance;

    friend bool operator<(const ants &c1, const ants &c2) {
        return c1.distance < c2.distance;
    }
    friend bool operator>(const ants &c1, const ants &c2) {
        return c1.distance > c2.distance;
    }
};

class country {
   public:
    country() {}

    void insrtTown(int number, double x, double y) {
        city.push_back(town(number, x, y));
    }
    void insertraod(double w);
    void init() {
        for (int i = 0; i < city.size(); i++) {
            for (int j = i + 1; j < city.size(); j++) {
                double distance = Euclidean(i, j);
                ROAD *tmp = new ROAD(&city[i], &city[j], distance);
                city[i].to.insert(std::pair<int, ROAD *>(j, tmp));
                city[j].to.insert(std::pair<int, ROAD *>(i, tmp));
            }
        }
    }
    double ACO() {
        init();
        double min_distance = DBL_MAX;
        for (int t = 0; t < 700; t++) {
            priority_queue<ants, vector<ants>, std::greater<ants>> ANTs;
            set<int> S;
            for (int a = 0; a < ANTS; a++) {
                ants walker;
                int start = rand() % city.size();
                int end = start;
                for (int i = 0; i < city.size(); i++) {
                    S.insert(start);
                    int next = Roulette(start, S);
                    if (next == -1) break;

                    walker.distance += city[start].to[next]->w;
                    walker.path.push_back(city[start].to[next]);

                    start = next;
                }

                walker.distance += city[start].to[end]->w;
                walker.path.push_back(city[start].to[end]);

                S.clear();
                ANTs.push(walker);
            }

            if (ANTs.size() && min_distance > ANTs.top().distance) {
                min_distance = ANTs.top().distance;  // find min distance;
            }

            for (int i = 0; i < city.size(); i++) {
                for (int j = i + 1; j < city.size(); j++) {
                    city[i].to[j]->Pheromones *= RHO;
                }
            }

            for (int a = 0; a < ANTs.size(); a++) {
                double dis = 1 / ANTs.top().distance;
                for (int i = 0; i < ANTs.top().path.size(); i++) {
                    ANTs.top().path[i]->Pheromones += dis;
                }
                ANTs.pop();
            }

            for (int i = 0; i < city.size(); i++) {
                for (int j = i + 1; j < city.size(); j++) {
                    double tmp = ALPHA * city[i].to[j]->re_w * BETA * city[i].to[j]->Pheromones;
                    if (tmp == 0) tmp = DBL_MIN;
                    city[i].to[j]->score = tmp;
                }
            }
        }
        return min_distance;
    }
    double Euclidean(int from, int to) {
        return sqrt((city[from].x - city[to].x) * (city[from].x - city[to].x) + (city[from].y - city[to].y) * (city[from].y - city[to].y));
    }
    void print() {
        cout << "  ";
        for (int i = 0; i < city.size(); i++) {
            cout << setw(6) << i;
        }
        cout << endl;
        for (int i = 0; i < city.size(); i++) {
            cout << i << " ";
            for (int j = 0; j < city.size(); j++) {
                if (i == j) {
                    cout << setw(6) << 0;
                    continue;
                }
                cout.precision(4);
                cout << setw(6) << city[i].to[j]->w;
            }
            cout << endl;
        }
    }
    void printpath(ants);
    void clear() {
        for (int i = 0; i < city.size(); i++) {
            for (int j = i + 1; j < city.size(); j++) {
                delete city[i].to[j];
            }
        }
        city.clear();
        return;
    }

    vector<town> city;
    int Roulette(int start, set<int> S) {
        double wheel = GetWheel(start, S);
        wheel = randFloat(0, wheel);
        int next = -1;
        for (int i = 0; i < city.size() && wheel >= 0; i++) {
            if (S.count(i)) continue;
            wheel -= city[start].to[i]->score;
            next = i;
        }
        return next;
    }
    double GetWheel(int start, set<int> S) {
        double wheel = 0;
        for (int i = 0; i < city.size(); i++) {
            if (S.count(i)) continue;
            wheel += city[start].to[i]->score;
        }
        return wheel;
    }
};


double randFloat(double lowerbound, double upperbound) {
    return double(rand()) / (RAND_MAX) * (upperbound - lowerbound) + lowerbound;
}

int main(void) {

    int n, t = 0;
    double x, y;
    country thisCountry;
    double ans = 0;

    while (cin >> n >> x >> y) {
        thisCountry.insrtTown(n, x, y);
    }
    
    cout << thisCountry.ACO() << endl;

    return 0;
}