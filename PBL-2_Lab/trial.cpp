#include <iostream>
#include <algorithm>
using namespace std;

#define MAXW 100
#define MAXN 100

int knapsack(int val[], int wt[], int W, int n)
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
    int i = n;
    int w = W;
    cout << "ITEMS INSIDE KNAPSACK ARE: ";
    while (i > 0 && w > 0)
    {
        if (B[i - 1][w] != B[i][w])
        {
            cout << "Item id: " << i - 1 << " is in knapsack";
            w = w - wt[i - 1];
        }
        i--;
    }
    cout << endl;
    return B[n][W];
}

int main()
{
    cout << "enter number of items: ";
    int n;
    cin >> n;

    int val[] = {10, 40, 50};
    int wt[] = {5, 6, 8};
    int W = 7;
    int result = knapsack(val, wt, n, W);
    cout << "Answer is: " << result;
    return 0;
}