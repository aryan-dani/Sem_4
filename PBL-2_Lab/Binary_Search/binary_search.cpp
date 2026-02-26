#include <iostream>
using namespace std;

int binarySearchIterative(int arr[], int size, int target)
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
        else if (arr[mid] < target)
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

int binarySearchRecursive(int arr[], int low, int high, int target)
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
        return binarySearchRecursive(arr, low, mid - 1, target);
    }
    else
    {
        return binarySearchRecursive(arr, mid + 1, high, target);
    }
}

void printScenario(string scenarioName, int arr[], int n, int target)
{
    cout << "\n--- " << scenarioName << " (Target: " << target << ") ---" << endl;

    int resIter = binarySearchIterative(arr, n, target);
    if (resIter != -1)
        cout << "Iterative: Found at index " << resIter << endl;
    else
        cout << "Iterative: Element not found" << endl;

    int resRec = binarySearchRecursive(arr, 0, n - 1, target);
    if (resRec != -1)
        cout << "Recursive: Found at index " << resRec << endl;
    else
        cout << "Recursive: Element not found" << endl;
}

int main()
{
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "=== BINARY SEARCH TIME COMPLEXITY ===" << endl;
    cout << "Best Case:    O(1)      (Element is at the middle)" << endl;
    cout << "Average Case: O(log n)  (Element is elsewhere)" << endl;
    cout << "Worst Case:   O(log n)  (Element at ends or not found)" << endl;

    printScenario("BEST CASE (Found at mid)", arr, n, 16);
    printScenario("WORST CASE (Found at end)", arr, n, 91);
    printScenario("NOT FOUND CASE", arr, n, 100);

    return 0;
}