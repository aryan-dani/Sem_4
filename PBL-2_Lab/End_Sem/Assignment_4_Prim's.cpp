#include <iostream>
using namespace std;

#define INF 999

class Graph
{
public:
    int cost[10][10];
    int n;
    int visited[10];

    void input()
    {
        cout << "enter number of cities: ";
        cin >> n;
        cout << "enter cost matrix";
        for (int i = 0; i < n; i++)
        {
            visited[i] = 0;
            for (int j = 0; j < n; j++)
            {
                cin >> cost[i][j];
                if (cost[i][j] == 0)
                {
                    cost[i][j] = INF;
                }
            }
        }
    }
    void Prims()
    {
        visited[0] = 1;
        int mincost = 0;
        int u = 0;
        int v = 0;
        for (int i = 0; i < n - 1; i++)
        {
            int min = INF;
            u = -1;
            v = -1;
            for (int j = 0; j < n; j++)
            {
                if (visited[j])
                {
                    for (int k = 0; k < n; k++)
                    {
                        if (!visited[k] && cost[j][k] < min)
                        {
                            min = cost[j][k];
                            u = j;
                            v = k;
                        }
                    }
                }
            }
            cout << "mincost: " << u << "-" << v << " cost is - " << min << endl;
            mincost += min;
            visited[v] = 1;
        }
        cout << "MST: " << mincost;
    }
};

int main()
{
    Graph g;
    g.input();
    g.Prims();
}