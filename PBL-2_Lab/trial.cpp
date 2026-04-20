#include <iostream>
using namespace std;

#define INF 999

class Graph
{
    int n, cost[10][10], visited[10];

public:
    void input()
    {
        cin >> n;

        for (int i = 0; i < n; i++)
        {
            visited[i] = 0;
            for (int j = 0; j < n; j++)
            {
                cin >> cost[i][j];
                if (cost[i][j] == 0)
                    cost[i][j] = INF;
            }
        }
    }

    void prims()
    {
        visited[0] = 1;
        int mincost = 0;

        for (int e = 0; e < n - 1; e++)
        {
            int min = INF, u = -1, v = -1;

            for (int i = 0; i < n; i++)
            {
                if (visited[i])
                {
                    for (int j = 0; j < n; j++)
                    {
                        if (!visited[j] && cost[i][j] < min)
                        {
                            min = cost[i][j];
                            u = i;
                            v = j;
                        }
                    }
                }
            }

            cout << u << " - " << v << " = " << min << endl;

            mincost += min;
            visited[v] = 1;
        }

        cout << "Minimum cost = " << mincost;
    }
};

int main()
{
    Graph g;
    g.input();
    g.prims();
}