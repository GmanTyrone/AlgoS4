#include <iostream>
#include <bits/stdc++.h>

using namespace std;



//Point class
struct Point
{
	public:
	int x, y;
};

int N;
Point P[10000];

int xsort(const void* a, const void* b)
{
	Point *p1 = (Point *)a, *p2 = (Point *)b;
	return (p1->x - p2->x);
}

int ysort(const void* a, const void* b)
{
	Point *p1 = (Point *)a, *p2 = (Point *)b;
	return (p1->y - p2->y);
}

float dist(Point p1, Point p2)
{
	return sqrt( (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

// min of two floats
float min(float x, float y)
{
	return (x < y)? x : y;
}

float subarraySelect(Point subarray[], int size, float d)
{
	float min = d;
    // Sorts by Y
	qsort(subarray, size, sizeof(Point), ysort);

	// Tries the points to see if they are closer in y than min distance
	for (int i = 0; i < size; ++i)
		for (int j = i+1; j < size && (subarray[j].y - subarray[i].y) < min; ++j)
			if (dist(subarray[i],subarray[j]) < min) min = dist(subarray[i], subarray[j]);

	return min;
}

// Recursive function of finding points
float distPoints(Point P[], int n)
{
	// BASE CASE for 2 of 3 points
	if (n <= 3)
	{
	float min = FLT_MAX;
	for (int i = 0; i < n; ++i)
		for (int j = i+1; j < n; ++j)
			if (dist(P[i], P[j]) < min)
				min = dist(P[i], P[j]);
	return min;
    }

	// Find the middle point
	int mid = n/2;
	Point midPoint = P[mid];

	// Recursively return min distance from the left and right
	float dl = distPoints(P, mid);
	float dr = distPoints(P + mid, n - mid);

	// min between right and d
	float d = min(dl, dr);

	// points close to mid by min distance
	Point subarray[n];
	int j = 0;
	for (int i = 0; i < n; i++)
		if (abs(P[i].x - midPoint.x) < d)
			subarray[j] = P[i], j++;

	// Returns min between min distance and the min distance in the subarray
	return min(d, subarraySelect(subarray, j, d) );
}

// main function
float closest(Point P[], int n)
{
    //First sorts by X
	qsort(P, n, sizeof(Point), xsort);

	//Returns the points with minimum distance
	return distPoints(P, n);
}

int main()
{
    while (cin >> N && N)
    {
        for(int i=0;i<N;i++) cin >> P[i].x >> P[i].y;
        float X=closest(P, N);
        if(X<10000)printf("%.4lf\n",X);
        else cout<<"INFINITY"<<endl;
    }
    return 0;
}
