#include <iostream>
#include <climits>
using namespace std;

#define MAX 100 // Maximum number of vertices

int minKey(int key[], bool mstSet[], int V)
{
    int min = INT_MAX, minIndex;

    for (int v = 0; v < V; v++)
    {
        if (!mstSet[v] && key[v] < min)
        {
            min = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}

void printMST(int parent[], int graph[MAX][MAX], int V)
{
    int totalCost = 0; // Variable to store the total cost of the MST
    cout << "Edge \tWeight\n";
    for (int i = 1; i < V; i++)
    {
        cout << parent[i] << " - " << i << " \t" << graph[i][parent[i]] << "\n";
        totalCost += graph[i][parent[i]]; 
    }
    cout << "\nTotal Cost of MST: " << totalCost << "\n"; 
}

void primMST(int graph[MAX][MAX], int V)
{
    int key[MAX];     // Key values to pick minimum weight edge
    bool mstSet[MAX]; // To represent vertices included in MST
    int parent[MAX];  // Array to store constructed MST

    for (int i = 0; i < V; i++)
    {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    key[0] = 0;     // Start from the first vertex
    parent[0] = -1; // First node is always the root of MST

    for (int count = 0; count < V - 1; count++)
    {
        int u = minKey(key, mstSet, V);
        mstSet[u] = true;

        for (int v = 0; v < V; v++)
        {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v])
            {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printMST(parent, graph, V);
}

int main()
{
    int V;
    int graph[MAX][MAX];

    cout << "Enter the number of vertices: ";
    cin >> V;

    cout << "Enter the adjacency matrix (use 0 for no edge):\n";
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            cin >> graph[i][j];
        }
    }

    cout << "\nMinimum Spanning Tree using Prim's Algorithm:\n";
    primMST(graph, V);

    return 0;
}
