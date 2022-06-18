#include <bits/stdc++.h>
using namespace std;

struct edg
{
	int x, y, t;
};

int dist[2005];

int main()
{
	vector<edg>list;
	int cases, n, m;
	int num;
	bool flag;
	edg tmp;
	cin>>cases;

	while (cases--)
	{
		list.clear();

		cin>>n>>m; //n systems (vertexs) and m wormholes (edges)
		num = m;
		while (num--)//Looks for the m edges
		{
			cin>>tmp.x>>tmp.y>>tmp.t;//Reads the edge information and pushes it to the list
			list.push_back(tmp);
		}
		dist[0] = 0;//initiates with 0
		for(int i=0;i<n;++i)//goes over n vertexs
		{
			flag = false; //existance of path default false
			for(int j=0;j<m;++j)//goes over m edges
			{//if theres a connection and the distance from vertex 1 to 2 is less than the computed distance at vertex 2
				if (dist[list[j].x] != INT_MAX && dist[list[j].x] + list[j].t < dist[list[j].y])
				{//turn the distance at vertex 2 to the computed distance
					dist[list[j].y] = dist[list[j].x] + list[j].t;
					flag = true;//Since array is filled with 0's that means theres a negative loop
				}
			}
			cout<<dist[i]<<endl;
		}

		if (flag)
			puts("possible");
		else
			puts("not possible");
	}
	return 0;
}
