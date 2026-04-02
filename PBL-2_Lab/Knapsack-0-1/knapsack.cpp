#include <iostream>
using namespace std;

int main()
{
    int weights[] = {2, 3, 4};
    int profits[] = {40, 50, 60};
    int capacity = 5;

    int n = 3;
    int maxProfit = 0;

    int bestSet[10]; // store best chosen items
    int bestSize = 0;

    // Try all subsets
    for (int i = 0; i < (1 << n); i++)
    {
        int totalWeight = 0, totalProfit = 0;

        int chosen[10];
        int size = 0;

        for (int j = 0; j < n; j++)
        {
            if (i & (1 << j))
            {
                totalWeight += weights[j];
                totalProfit += profits[j];
                chosen[size++] = j;
            }
        }

        if (totalWeight <= capacity && totalProfit > maxProfit)
        {
            maxProfit = totalProfit;

            bestSize = size;
            for (int k = 0; k < size; k++)
            {
                bestSet[k] = chosen[k];
            }
        }
    }

    cout << "Maximum Profit: " << maxProfit << endl;
    cout << "Selected item indices: ";
    for (int i = 0; i < bestSize; i++)
    {
        cout << bestSet[i] << " ";
    }

    return 0;
}