#include <iostream>
#include <stack>
#include <queue>
using namespace std;

struct node
{
    char name[10];
    int id;
    node *next;
};

class Graph
{
public:
    node *head[20];
    string names[20];
    int n;
    Graph()
    {
        cout << "enter number of users:";
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cout << "enter the name for: " << i;
            cin >> names[i];
            head[i] = NULL;
        }
    }

    void create()
    {
        int v;
        char ans;
        for (int i = 0; i < n; i++)
        {
            do
            {
                cout << "enter the friend id of " << i;
                cin >> v;
                if (v != i && v > n && v <= 0)
                {
                    node *curr = new node;
                    curr->id = v;
                    curr->name = names[v];
                    curr->next = head[i];
                    head[i] = curr;
                }
                cout << "do you want to add more nodes? :";
                cin >> ans;
            } while (ans == 'Y' || ans == 'y');
        }
    }

    void recursiveDFS(int curr, bool visited[])
    {
        visited[curr] = true;
        cout << names[curr] << " ";
        node *temp = head[curr];
        while (temp != NULL)
        {
            if (!visited[temp->id])
            {
                visited[temp->id] = true;
                recursiveDFS(temp->id, visited);
            }
            temp = temp->next;
        }
    }

    void non_recursiveDFS(int start)
    {
        bool visited[20] = {false};
        stack<int> s;
        s.push(start);

        while (!s.empty())
        {
            int curr = s.top();
            s.pop();

            if(!visited[curr])
            {
                cout << names[curr] << " ";
                visited[curr] = true;
            }
            node *temp = head[curr]
            while(temp!=NULL)
            {
                if()
            }
        }
    }
};
