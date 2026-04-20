#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 100
#define MAXW 100

int knapsack(int W, int wt[], int val[], int n)
{
    int B[MAXN + 1][MAXW + 1];
    for (int i = 0; i <= n; i++)
    {
        for (int w = 0; w <= W; w++)
        {
            if (i == 0 || w == 0)
                B[i][w] = 0;

            else if (wt[i - 1] <= w)
                B[i][w] = max(val[i - 1] + B[i - 1][w - wt[i - 1]], B[i - 1][w]);
            else
                B[i][w] = B[i - 1][w];
        }
    }
    return B[n][W];
}

int main()
{
    int n, W;

    cout << "Enter number of items: ";
    cin >> n;

    int wt[MAXN], val[MAXN];

    cout << "Enter weights:\n";
    for (int i = 0; i < n; i++)
        cin >> wt[i];

    cout << "Enter values:\n";
    for (int i = 0; i < n; i++)
        cin >> val[i];

    cout << "Enter capacity of knapsack: ";
    cin >> W;

    int result = knapsack(W, wt, val, n);

    cout << "Maximum Profit = " << result << endl;

    return 0;
}