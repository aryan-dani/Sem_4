#include <iostream>
#include <string>
#include <stack>
#include <queue>

using namespace std;

struct node
{
    int id;
    string name;
    node *next;
};

class graph
{
    node *head[20];
    string names[20];
    int n;

public:
    graph()
    {
        cout << "Enter number of users: ";
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cout << "Enter name for ID " << i << ": ";
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
                cout << "Enter Friend ID for " << names[i] << ": ";
                cin >> v;
                if (v != i && v < n && v >= 0)
                {
                    node *curr = new node;
                    curr->id = v;
                    curr->name = names[v];
                    curr->next = head[i];
                    head[i] = curr;
                }
                cout << "Add another? (y/n): ";
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

        while (!s.empty())
        {
            int curr = s.top();
            s.pop();

            if (!visited[curr])
            {
                cout << names[curr] << " ";
                visited[curr] = true;
            }

            node *temp = head[curr];
            while (temp != NULL)
            {
                if (!visited[temp->id])
                {
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
    graph g;
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