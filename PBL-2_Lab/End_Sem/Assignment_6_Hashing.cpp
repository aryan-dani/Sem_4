#include <iostream>
#include <fstream>
using namespace std;

#define SIZE 10

class Record
{
public:
    int rno;
    string name;
    int marks;

    void accept()
    {
        cin >> rno >> name >> marks;
    }
    void display()
    {
        cout << rno << "\t" << name << "\t" << marks;
    }
};

class Hashing
{
    Record ht[SIZE];

public:
    void init()
    {
        for (int i = 0; i < SIZE; i++)
            ht[i].rno = -1;
    }

    int hashFunction(int key)
    {
        return key % SIZE;
    }

    int findEmpty(int loc)
    {
        while (ht[loc].rno != -1)
            loc = (loc + 1) % SIZE;
        return loc;
    }

    void insertWithoutReplacement(Record r)
    {
        int loc = hashFunction(r.rno);
        loc = findEmpty(loc);
        ht[loc] = r;
    }

    void insertWithReplacement(Record r)
    {
        int loc = hashFunction(r.rno);

        if (ht[loc].rno == -1)
        {
            ht[loc] = r;
            return;
        }

        int oldHome = hashFunction(ht[loc].rno);

        if (oldHome != loc)
        {
            Record temp = ht[loc];
            ht[loc] = r;
            ht[findEmpty(loc + 1)] = temp;
        }
        else
        {
            ht[findEmpty(loc + 1)] = r;
        }
    }

    void search(int key)
    {
        int loc = hashFunction(key);
        int start = loc;

        while (ht[loc].rno != -1)
        {
            if (ht[loc].rno == key)
            {
                cout << "Found at index: " << loc << endl;
                return;
            }
            loc = (loc + 1) % SIZE;
            if (loc == start)
                break;
        }
        cout << "Not Found\n";
    }

    void display()
    {
        cout << "\nIndex\tRNo\tName\tMarks\n";
        for (int i = 0; i < SIZE; i++)
        {
            cout << i << "\t";
            if (ht[i].rno != -1)
                ht[i].display();
            else
                cout << "-\tEmpty\t-";
            cout << endl;
        }
    }

    void saveFile()
    {
        ofstream fout("hash.txt");

        for (int i = 0; i < SIZE; i++)
            if (ht[i].rno != -1)
                fout << ht[i].rno << " " << ht[i].name << " " << ht[i].marks << endl;

        cout << "Saved to file\n";
    }
};

int main()
{
    Hashing h;
    h.init();

    int choice;

    do
    {
        cout << "\n1.Insert  2.Display  3.Search  4.Save  5.Exit\n";
        cin >> choice;

        if (choice == 1)
        {
            int method, n;
            cout << "1.Without Replacement  2.With Replacement\n";
            cin >> method;

            cout << "How many records: ";
            cin >> n;

            for (int i = 0; i < n; i++)
            {
                Record r;
                cout << "Enter rno name marks: ";
                r.accept();

                if (method == 1)
                    h.insertWithoutReplacement(r);
                else
                    h.insertWithReplacement(r);
            }
        }

        else if (choice == 2)
            h.display();
        else if (choice == 3)
        {
            int key;
            cout << "Enter roll no: ";
            cin >> key;
            h.search(key);
        }
        else if (choice == 4)
            h.saveFile();

    } while (choice != 5);

    return 0;
}