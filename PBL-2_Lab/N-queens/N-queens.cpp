#include <iostream>
#include <cmath>

using namespace std;

int board[20];
int solutionCount = 0;

bool place(int row, int col)
{
    for (int i = 1; i < row; i++)
    {
        if (board[i] == col || abs(board[i] - col) == abs(i - row))
        {
            return false;
        }
    }
    return true;
}

void nQueens(int row, int n)
{
    for (int col = 1; col <= n; col++)
    {
        if (place(row, col))
        {
            board[row] = col;

            if (row == n)
            {
                solutionCount++;
                cout << "Solution " << solutionCount << ":\n";
                for (int i = 1; i <= n; i++)
                {
                    for (int j = 1; j <= n; j++)
                    {
                        if (board[i] == j)
                            cout << "Q ";
                        else
                            cout << ". ";
                    }
                    cout << "\n";
                }
                cout << "\n";
                cout << "-------------------------\n";
            }
            else
            {
                nQueens(row + 1, n);
            }
        }
    }
}

int main()
{
    int n;
    cout << "Enter N: ";
    cin >> n;

    nQueens(1, n);

    cout << "Total Solutions: " << solutionCount << "\n";

    return 0;
}