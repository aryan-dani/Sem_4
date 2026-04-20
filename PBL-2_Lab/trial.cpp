#include <iostream>
#include <stack>
#include <queue>
#include <string>
using namespace std;

struct node
{
    int id;
    string name;
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
        cout << "Enter number of users: (facebook) ";
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cout << "enter name for id " << i;
            cin >> names[i];
            head[i] = NULL;
        }
    }

    void create()
    {
        char ans;
        int v;

        for (int i = 0; i < n; i++)
        {
            do
            {
                cout << "Enter friend id for " << i;
                cin >> v;
                if (v != i && v >= 0 && v < n)
                {
                    node *curr = new node;
                    curr->id = v;
                    curr->name = names[v];
                    curr->next = head[i];
                    head[i] = curr;
                }
                cout << " do you want to add more nodes: ";
                cin >> ans;
            } while (ans == 'y' || ans == 'Y');
        }
    }

    void recursiveDFS(int start, bool visited[])
    {
        cout << "Names: " << names[start];
        visited[start] = true;
        node *temp = head[start];
        while (temp != NULL)
        {
            if (!visited[temp->id])
            {
                recursiveDFS(temp->id, visited);
            }
            temp = temp->next;
        }
    }

    void nonrecursiveDFS(int start)
    {
        bool visited[20] = {false};
        visited[start] = true;
        stack<int> s;
        s.push(start);
        while (!s.empty())
        {
            int curr = s.top();
            s.pop();
            cout << names[curr] << " ";
            node *temp = head[curr];
            while (temp != NULL)
            {
                if (!visited[temp->id])
                {
                    visited[temp->id] = true;
                    s.push(temp->id);
                }
                temp = temp->next;
            }
        }
    }

    void nonrecursiveBFS(int start)
    {
        bool visited[20] = {false};
        visited[start] = true;
        queue<int> q;
        q.push(start);
        while (!q.empty())
        {
            int curr = q.front();
            q.pop();
            cout << "Names: " << names[curr];
            node *temp = head[curr];
            while (temp != NULL)
            {
                if (!visited[temp->id])
                {
                    visited[temp->id] = true;
                    q.push(temp->id);
                }
                temp = temp->next;
            }
        }
    }
};

int main()
{
    Graph g;
    g.create();
    int start;
    cout << "enter node to start traversing: ";
    cin >> start;

    bool visited[20] = {false};
    g.recursiveDFS(start, visited);
    g.nonrecursiveBFS(start);
    g.nonrecursiveDFS(start);
}