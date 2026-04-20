#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Implement Direct access file using hashing (linear probing with and without
// replacement) perform following operations on it a) Create Student Database [Roll
// no, Name, Marks] b) Display Database c) Add a record d) Search a
// record e) Modify a record

#define SIZE 10
class Record
{
public:
    int rno;
    string name;
    int marks;
};

class Hashing
{
    Record ht[SIZE];

public:
    void init()
    {
        for (int i = 0; i < SIZE; i++)
        {
            ht[i].rno = -1;
        }
    }
    int hashfunction(int key)
    {
        return (key % SIZE);
    }

    int findempty(int loc)
    {
        while (ht[loc].rno != -1)
        {
            loc = (loc + 1) % SIZE;
        }
        return loc;
    }

    void withoutreplacement(Record r)
    {
        int loc = hashfunction(r.rno);
        loc = findempty(loc);
        ht[loc] = r;
    }

    void withreplacement(Record r)
    {
        int loc = hashfunction(r.rno);
        if (ht[loc].rno == -1)
        {
            ht[loc] = r;
            return;
        }
        int oldHome = hashfunction(ht[loc].rno);
        if (oldHome != loc)
        {
            Record temp = ht[loc];
            ht[loc] = r;
            ht[findempty(loc + 1)] = temp;
        }
        else
        {
            ht[findempty(loc + 1)] = r;
        }
    }

    void search(int key)
    {
        int loc = hashfunction(key);
        int start = loc;
        while (ht[loc].rno != -1)
        {
            if (key = ht[loc].rno)
            {
                cout << "Element found at " << loc;
            }
            loc = (loc + 1) % SIZE;
            if (start == loc)
            {
                break;
            }
        }
        cout << "not found";
    }

    void disp()
    {
        cout << "Index\tRollNo\tName\tMarks";
        for (int i = 0; i < SIZE; i++)
        {
            if (ht[i].rno != -1)
            {
                cout << i << " " << ht[i].rno << "\t" << ht[i].name << "\t" << ht[i].marks << endl;
            }
            else
            {
                cout << "\t EMPTY\t";
            }
        }
    }

    void save()
    {
        ofstream fout("hash.txt");
        for (int i = 0; i < SIZE; i++)
        {
            if (ht[i].rno != -1)
            {
                fout << i << " " << ht[i].rno << "\t" << ht[i].name << "\t" << ht[i].marks << endl;
            }
        }
        cout << "written to file! ";
    }
};
