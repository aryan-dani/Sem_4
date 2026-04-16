#include <iostream>
using namespace std;

int bs(int arr[], int size, int target)
{
    int low = 0;
    int high = size - 1;

    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (arr[mid] == target)
        {
            return mid;
        }
        else if (target > arr[mid])
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return -1;
}

int rs(int arr[], int low, int high, int target)
{
    int mid = (low + high) / 2;
    if (low > high)
    {
        return -1;
    }
    if (arr[mid] == target)
    {
        return mid;
    }
    else if (target > arr[mid])
    {
        return rs(arr, mid + 1, high, target);
    }
    else
    {
        return rs(arr, low, mid - 1, target);
    }
}

int main()
{
    int arr[] = {2, 4, 5, 7, 19, 24, 56, 78, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 90;
    int paneer = bs(arr, n, target);
    int aaloo = rs(arr, 0, n - 1, target);
    if (paneer == -1)
    {
        cout << "element not in the iterative implementation of bs";
        cout << endl;
    }
    else
    {
        cout << "element present at index : " << paneer;
        cout << endl;
    }
    if (aaloo == -1)
    {
        cout << "element not in the recursive implementation of bs";
        cout << endl;
    }
    else
    {
        cout << "element present at index : " << aaloo;
        cout << endl;
    }
    return 0;
}
