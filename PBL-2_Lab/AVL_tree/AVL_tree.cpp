#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct Node
{
    string word;
    string meaning;
    Node *left;
    Node *right;
    int height;
};

int getHeight(Node *n)
{
    if (n == NULL)
        return 0;
    return n->height;
}

int getBF(Node *n)
{
    if (n == NULL)
        return 0;
    return getHeight(n->left) - getHeight(n->right);
}

Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *temp = x->right;

    x->right = y;
    y->left = temp;

    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));

    return x;
}

Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *temp = y->left;

    y->left = x;
    x->right = temp;

    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));

    return y;
}

Node *insert(Node *root, string w, string m)
{
    if (root == NULL)
    {
        Node *newNode = new Node;
        newNode->word = w;
        newNode->meaning = m;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->height = 1;
        return newNode;
    }

    if (w < root->word)
        root->left = insert(root->left, w, m);
    else if (w > root->word)
        root->right = insert(root->right, w, m);
    else
        return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int bf = getBF(root);

    if (bf > 1 && w < root->left->word)
        return rightRotate(root);

    if (bf < -1 && w > root->right->word)
        return leftRotate(root);

    if (bf > 1 && w > root->left->word)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (bf < -1 && w < root->right->word)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void display(Node *root)
{
    if (root != NULL)
    {
        display(root->left);
        cout << root->word << " : " << root->meaning << endl;
        display(root->right);
    }
}

void search(Node *root, string key)
{
    Node *curr = root;
    int count = 0;
    while (curr != NULL)
    {
        count++;
        if (key == curr->word)
        {
            cout << "Found: " << curr->meaning << endl;
            cout << "Comparisons: " << count << endl;
            cout << "Update meaning? (y/n): ";
            char choice;
            cin >> choice;
            if (choice == 'y')
            {
                cout << "New meaning: ";
                cin.ignore();
                getline(cin, curr->meaning);
            }
            return;
        }
        if (key < curr->word)
            curr = curr->left;
        else
            curr = curr->right;
    }
    cout << "Not found after " << count << " comparisons." << endl;
}

int main()
{
    Node *root = NULL;
    int choice;
    string w, m;

    do
    {
        cout << "\n1. Add Word\n2. Display Dictionary\n3. Search/Update\n4. Exit\nChoice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Word: ";
            cin >> w;
            cout << "Meaning: ";
            cin.ignore();
            getline(cin, m);
            root = insert(root, w, m);
            break;
        case 2:
            display(root);
            break;
        case 3:
            cout << "Search for: ";
            cin >> w;
            search(root, w);
            break;
        }
    } while (choice != 4);

    return 0;
}