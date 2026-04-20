#include <iostream>
#include <algorithm>
using namespace std;

#define MAXW 100
#define MAXN 100
int knapsack(int val[], int wt[], int n, int W)
{
    int B[MAXN + 1][MAXW + 1];
    for (int i = 0; i <= n; i++)
    {
        for (int w = 0; w <= W; w++)
        {
            if (i == 0 || w == 0)
            {
                B[i][w] = 0;
            }
            else if (wt[i - 1] <= w)
            {
                B[i][w] = max(val[i - 1] + B[i - 1][w - wt[i - 1]], B[i - 1][w]);
            }
            else
            {
                B[i][w] = B[i - 1][w];
            }
        }
    }
    return B[n][W];
}

int main()
{
    int n, W;
    cout << "Enter number of items in knapsack: ";
    cin >> n;
    cout << "enter total capacity of knapsack:";
    cin >> W;

    int val[MAXN];
    int wt[MAXW];
    cout << "enter profit values for each item: \n ";
    for (int i = 0; i < n; i++)
    {
        cin >> val[i];
    }

    cout << "enter weight values for each item: \n ";
    for (int i = 0; i < n; i++)
    {
        cin >> wt[i];
    }

    int result = knapsack(val, wt, n, W);
    cout << "Maximum Profit = " << result << endl;
    return 0;
}