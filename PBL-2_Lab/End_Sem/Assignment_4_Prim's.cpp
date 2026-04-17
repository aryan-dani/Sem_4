#include <iostream>
using namespace std;

#define INF 999

class Graph
{
public:
    int cost[10][10];
    int n;
    Graph()
    {
        cout << "Enter number of cities: ";
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i == j)
                {
                    cost[i][j] = 0;
                }
                else
                {
                    cost[i][j] = INF;
                }
            }
        }
    }

    void create()
    {
        int u, v, w;
        int ch;
        do
        {
            cout << "enter (u,v,w) : ";
            cin >> u >> v >> w;
            cost[u][v] = w;
            cost[v][u] = w;
            cout << " do you want to add any more edges ? :";
            cin >> ch;
        } while (ch == 'y' || ch == 'Y');
    }

    void display()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << cost[i][j] << "\t";
            }
            cout << endl;
        }
    }

    void prims()
    {
        int start;
        cout << "Enter starting vertex: ";
        cin >> start;
        bool visited[10] = {false};
        int nearest[10];
        int mincost = 0;

        visited[start] = 1;

        cout << "edes in MST are: \n";
        for (int i = 1; i < n; i++)
        {
            int min = INF;
            int u = -1;
            int v = -1;
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
            if (u != -1 || v != -1)
            {
                cout << u << " - " << v << " cost: " << min << endl;
                mincost += min;
                visited[v] = 1;
            }
        }
        cout << "\nTotal Minimum Cost = " << mincost << endl;
    }
};

int main()
{
    Graph g;

    g.create();
    g.display();
    g.prims();

    return 0;
}