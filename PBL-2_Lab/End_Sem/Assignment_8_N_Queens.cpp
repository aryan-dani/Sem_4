#include <iostream>
#include <cmath>
using namespace std;

int board[20], countSol = 0;

bool isSafe(int row, int col)
{
    for (int i = 1; i < row; i++)
        if (board[i] == col || abs(board[i] - col) == abs(i - row))
            return false;
    return true;
}

void solve(int row, int n)
{
    for (int col = 1; col <= n; col++)
    {
        if (isSafe(row, col))
        {
            board[row] = col;

            if (row == n)
            {
                countSol++;
                cout << "\nSolution " << countSol << ":\n";

                for (int i = 1; i <= n; i++)
                {
                    for (int j = 1; j <= n; j++)
                        cout << (board[i] == j ? "Q " : ". ");
                    cout << endl;
                }
            }
            else
            {
                solve(row + 1, n);
            }
        }
    }
}

int main()
{
    int n;
    cout << "Enter N: ";
    cin >> n;

    solve(1, n);

    cout << "\nTotal Solutions = " << countSol;
    return 0;
}