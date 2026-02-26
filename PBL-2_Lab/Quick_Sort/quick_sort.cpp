// Write a program to perform quick/merge sort using Divide and Conquer strategy and verify the time complexity
//  a. Accept Mobile user Information(e.g. MobileNo, Name, BillAmount etc.).
//  b. Display data in descending order of MobileNo. (Recursive Quick Sort)
//  d. Display the number of passes and comparisons for different test cases (Worst, Average, Best case).

#include <iostream>
#include <string.h>
using namespace std;

class Mobile
{
public:
    long long mob_no;
    string name;
    float bill;
};

class MobileList
{
    Mobile a[51];
    int n;

public:
    long long comparisons;
    long long passes;

    void getData()
    {
        cout << "Enter number of users: ";
        cin >> n;

        for (int i = 1; i <= n; i++)
        {
            cout << "\nEnter mobile number: ";
            cin >> a[i].mob_no;
            cout << "Enter name: ";
            cin >> a[i].name;
            cout << "Enter bill amount:";
            cin >> a[i].bill;
        }
    }

    void display()
    {
        cout << "The details are \n";
        for (int i = 1; i <= n; i++)
        {
            cout << a[i].mob_no << "\t" << a[i].name << "\t" << a[i].bill << endl;
        }
    }

    void swap(Mobile &x, Mobile &y)
    {
        Mobile temp = x;
        x = y;
        y = temp;
    }

    int partition(int low, int high)
    {
        long long pivot = a[low].mob_no;
        int i = low + 1;
        int j = high;

        while (i <= j)
        {
            while (i <= high && a[i].mob_no >= pivot)
            {
                comparisons++;
                i++;
            }
            while (a[j].mob_no < pivot)
            {
                comparisons++;
                j--;
            }
            if (i < j)
            {
                swap(a[i], a[j]);
                passes++;
            }
        }
        swap(a[low], a[j]);
        passes++;
        return j;
    }

    void quicksort(int low, int high)
    {
        if (low < high)
        {
            int p = partition(low, high);
            quicksort(low, p - 1);
            quicksort(p + 1, high);
        }
    }
    void sortData()
    {
        comparisons = 0;
        passes = 0;
        quicksort(1, n);
    }
};

int main()
{
    MobileList m;
    m.getData();
    m.sortData();
    m.display();

    cout << "\n Total Comparisions: " << m.comparisons;
    cout << "\n Total Passes: " << m.passes;
}