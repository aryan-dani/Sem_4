
int cost[10][10];
int n;

define INF
    Class Prims
{
    void input()
    {
        enter number of cities;
        cin n;
        cout << enter cost matrix;
        for (int i = 0 i < n)
        {
            visited[i] = 0;
            for (int j = 0; j < n)
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
        int mincost = 0;
        int u, v = 0;
        int visited[10];
        visited[0] = 1;
        for (int i = 1; i < n - 1; i++)
        {
            int min = INF;
            u, v = -1;
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
            cout << "min distance between " << u << "-" << v << " cost: " << min;
            mincost = mincost + min;
            visited[v] = 1;
        }
    }
}