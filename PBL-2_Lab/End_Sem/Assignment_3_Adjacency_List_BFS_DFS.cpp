#include <iostream>
#include <stack>
#include <queue>
#include <string>

using namespace std;

struct node
{
    string name;
    int id;
    node *next;
};

class Graph
{
    node *head[20];
    string names[20];
    int n;

public:
    Graph()
    {
        cout << "Enter the number of users: ";
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cout << "Enter name for id " << i << endl;
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
                cout << "Enter id of friend  " << i;
                cin >> v;
                if (v != i && v >= 0 && v < n)
                {
                    node *curr = new node;
                    curr->id = v;
                    curr->name = names[v];
                    curr->next = head[i];
                    head[i] = curr;
                }
                cout << "do you want to add more friends? ";
                cin >> ans;
            } while (ans == 'y' || ans == 'Y');
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
                recursiveDFS(temp->id, visited);
            }
            temp = temp->next;
        }
    }
    void nonRecursiveDFS(int start)
    {
        bool visited[20] = {false};
        stack<int> s;
        s.push(start);
        visited[start] = true;
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

    void nonRecursiveBFS(int start)
    {
        bool visited[20] = {false};
        queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty())
        {
            int curr = q.front();
            q.pop();
            cout << names[curr] << " ";

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
    cout << "\nEnter starting ID: ";
    cin >> start;

    bool visited[20] = {false};
    cout << "\nRecursive DFS: ";
    g.recursiveDFS(start, visited);

    cout << "\nNon-Recursive DFS: ";
    g.nonRecursiveDFS(start);

    cout << "\nNon-Recursive BFS: ";
    g.nonRecursiveBFS(start);

    return 0;
}
