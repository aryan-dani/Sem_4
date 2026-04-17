#include <iostream>
#include <algorithm>
using namespace std;

class Mobile
{
public:
    long long mob_no;
    float bill;
    char name[10];
};

class MobileList
{
private:
    Mobile m[5];
    int n;

public:
    long long passes;
    long long comparisons;

    void accept()
    {

        cout << "Enter number of users: ";
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cout << "what's your mobile number tell me your dial number: ";
            cin >> m[i].mob_no;
            cout << "what is the bill? : ";
            cin >> m[i].bill;
            cout << "naam kya hai?";
            cin >> m[i].name;
        }
    }

    void disp()
    {
        for (int i = 0; i < n; i++)
        {
            cout << " mobile number: ";
            cout << m[i].mob_no << endl;
            cout << "the bill : ";
            cout << m[i].bill << endl;
            cout << "naam: ";
            cout << m[i].name << endl;
        }
    }

    int partition(int high, int low, bool asc)
    {
        int i = low - 1;
        long long pivot = m[high].mob_no;
        for (int j = low; j < high; j++)
        {
            comparisons++;
            if (asc && m[j].mob_no < pivot || !asc && m[j].mob_no > pivot)
            {
                i++;
                swap(m[i], m[j]);
                passes++;
            }
        }
        swap(m[i + 1], m[high]);
        passes++;
        return i + 1;
    }

    void quicksort(int high, int low, bool asc)
    {
        if (low < high)
        {
            int p = partition(high, low, asc);
            quicksort(high, p + 1, asc);
            quicksort(p - 1, low, asc);
        }
    }
    void sort_ascending()
    {
        comparisons = 0;
        passes = 0;
        quicksort(n - 1, 0, 1);
    }
    void sort_descending()
    {
        comparisons = 0;
        passes = 0;
        quicksort(n - 1, 0, 0);
    }
};

int main()
{

    MobileList m;
    m.accept();

    cout << "display of data";
    m.disp();

    cout << "after sorting (ascending): \n\n";
    m.sort_ascending();
    m.disp();

    cout << "after sorting (descending): \n\n";
    m.sort_descending();
    m.disp();

    return 0;
}
