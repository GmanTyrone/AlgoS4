#include <iostream>
#include <bits/stdc++.h>

using namespace std;

#define N 10000
#define MAX 10000

struct Point{
    double x, y;
    double pointsDistance(const Point& a)
    {
        return sqrt((a.x - x) * (a.x - x) + (a.y - y) * (a.y - y));
    }
}

point[N];

double closestPoints(int left, int right)
{
    if (left >= right) return MAX;
    else if (right - left < 3) {
        double d = MAX;
        for (int i = left; i < right; i++)
            for (int j = i + 1; j <= right; j++)
                d = min(d, point[i].pointsDistance(point[j]));
        return d;
    }
    int mid = (left + right) / 2;
    // shortest distance between left and right
    double d = min(closestPoints(left, mid), closestPoints(mid + 1, right));
    if (d == 0)
        return 0;
    int n = 0;
    Point subarray[N];

    // points near the middle at min distance
    for (int i = mid; i >= left && point[mid].x - point[i].x < d; i--)subarray[n++] = point[i];
    for (int i = mid + 1; i <= right && point[i].x - point[mid].x < d; i++)subarray[n++] = point[i];

    //sort by y
    sort(subarray, subarray + n, [](const Point& a, const Point& b)->bool {return a.y < b.y; });

    //shortest distance in subarray
    for (int i = 0; i < n; i++)
        for (int j = 1; j <= 3 && i + j < n; j++)
            d = min(d, subarray[i].pointsDistance(subarray[i + j]));
    return d;
}

int main()
{
    int n;
    while (cin >> n && n)
    {
        for (int i = 0; i < n; i++)
            cin >> point[i].x >> point[i].y;
        //preprocess, sort by x
        sort(point, point + n, [](const Point& a, const Point& b) -> bool {return a.x < b.x; })
        double result = closestPoints(0, n - 1);
        if (result >= 10000)cout << "INFINITY";
        else cout<<setprecision(4)<<fixed<<result;
        cout<<endl;
    }
    return 0;
}
