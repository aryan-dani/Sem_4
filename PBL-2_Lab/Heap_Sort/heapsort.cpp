#include <iostream>
using namespace std;

void adjust(int A[], int n, int i)
{
    while (2 * i <= n)
    {
        int j = 2 * i;
        if (j < n && A[j + 1] > A[j])
        {
            j = j + 1;
        }
        if (A[i] >= A[j])
        {
            break;
        }
        else
        {
            swap(A[i], A[j]);
            i = j;
        }
    }
}

void heapSort(int A[], int n)
{
    for (int i = n / 2; i >= 1; i--)
    {
        adjust(A, n, i);
    }

    while (n > 1)
    {
        swap(A[1], A[n]);
        n--;
        adjust(A, n, 1);
    }
}

int main()
{
    int n;
    int A[100]; 

    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter the elements: ";
    for (int i = 1; i <= n; i++)
    {
        cin >> A[i];
    }

    heapSort(A, n);

    cout << "Sorted Array: ";
    for (int i = 1; i <= n; i++)
    {
        cout << A[i] << " ";
    }
    cout << endl;

    return 0;
}