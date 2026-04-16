#include <iostream>
using namespace std;

int bs1(int arr[], int size, int target)
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
        else if (arr[mid] > target)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return -1;
}

int bs2(int arr[], int low, int high, int target)
{
    if (low > high)
    {
        return -1;
    }

    int mid = (low + high) / 2;
    if (arr[mid] == target)
    {
        return mid;
    }
    else if (arr[mid] > target)
    {
        return bs2(arr, low, mid - 1, target);
    }
    else
    {
        return bs2(arr, mid + 1, high, target);
    }
    return -1;
}

int main()
{
    int arr[] = {2, 5, 6, 7, 90, 12, 45, 32, 78, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 7;
    int val = bs1(arr, n, target);
    int val2 = bs2(arr, 0, n - 1, target);
    if (val == -1)
    {
        cout << "element not found";
    }
    else
    {
        cout << "element found at index" << val << endl;
    }
    if (val2 == -1)
    {
        cout << "element not found";
    }
    else
    {
        cout << "element found at index" << val2;
    }
    return 0;
}