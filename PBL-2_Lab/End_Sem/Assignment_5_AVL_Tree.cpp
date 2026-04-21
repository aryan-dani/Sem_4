#include <iostream>
#include <queue>
using namespace std;

class Node
{
public:
    string word, meaning;
    int height;
    Node *left, *right;

    Node(string w, string m)
    {
        word = w;
        meaning = m;
        height = 1;
        left = right = NULL;
    }
};

class AVL
{
    Node *root;

    int getHeight(Node *n)
    {
        return n ? n->height : 0;
    }

    int getBalance(Node *n)
    {
        return n ? getHeight(n->left) - getHeight(n->right) : 0;
    }

    Node *rotateRight(Node *y)
    {
        Node *x = y->left;
        Node *t = x->right;

        x->right = y;
        y->left = t;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    Node *rotateLeft(Node *x)
    {
        Node *y = x->right;
        Node *t = y->left;

        y->left = x;
        x->right = t;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    Node *insert(Node *root, string w, string m)
    {
        if (!root)
            return new Node(w, m);

        if (w < root->word)
            root->left = insert(root->left, w, m);
        else if (w > root->word)
            root->right = insert(root->right, w, m);
        else
        {
            cout << "Word already exists. Use update option.\n";
            return root;
        }

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));

        int balance = getBalance(root);

        // LL
        if (balance > 1 && w < root->left->word)
            return rotateRight(root);

        // RR
        if (balance < -1 && w > root->right->word)
            return rotateLeft(root);

        // LR
        if (balance > 1 && w > root->left->word)
        {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        // RL
        if (balance < -1 && w < root->right->word)
        {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    void inorder(Node *root)
    {
        if (!root)
            return;
        inorder(root->left);
        cout << root->word << " : " << root->meaning << endl;
        inorder(root->right);
    }

    Node *search(Node *root, string key, int &comparisons)
    {
        if (!root)
            return NULL;

        comparisons++;

        if (key == root->word)
            return root;
        else if (key < root->word)
            return search(root->left, key, comparisons);
        else
            return search(root->right, key, comparisons);
    }

public:
    AVL() { root = NULL; }

    void insertWord()
    {
        string w, m;
        cout << "Enter word: ";
        cin >> w;

        cout << "Enter meaning: ";
        cin.ignore();
        getline(cin, m);

        root = insert(root, w, m);
    }

    void show()
    {
        if (!root)
        {
            cout << "Dictionary is empty\n";
            return;
        }
        inorder(root);
    }

    void findWord()
    {
        string key;
        cout << "Enter word to search: ";
        cin >> key;

        int comparisons = 0;
        Node *res = search(root, key, comparisons);

        if (res)
            cout << "Meaning: " << res->meaning << endl;
        else
            cout << "Word not found\n";

        cout << "Comparisons made: " << comparisons << endl;
    }

    void updateMeaning()
    {
        string key, newMeaning;
        cout << "Enter word to update: ";
        cin >> key;

        int comparisons = 0;
        Node *res = search(root, key, comparisons);

        if (res)
        {
            cout << "Enter new meaning: ";
            cin.ignore();
            getline(cin, newMeaning);
            res->meaning = newMeaning;
            cout << "Updated successfully\n";
        }
        else
        {
            cout << "Word not found\n";
        }

        cout << "Comparisons made: " << comparisons << endl;
    }

    void maxComparisons()
    {
        cout << "Maximum comparisons (height of AVL tree): " << getHeight(root) << endl;
    }
};

int main()
{
    AVL obj;
    int ch;

    do
    {
        cout << "\n1.Insert\n2.Display\n3.Search\n4.Update\n5.Max Comparisons\n6.Exit\nChoice: ";
        cin >> ch;

        if (ch == 1)
            obj.insertWord();
        else if (ch == 2)
            obj.show();
        else if (ch == 3)
            obj.findWord();
        else if (ch == 4)
            obj.updateMeaning();
        else if (ch == 5)
            obj.maxComparisons();

    } while (ch != 6);

    return 0;
}