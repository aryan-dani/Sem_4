#include <iostream>
#include <queue>

using namespace std;

class avl_node
{
    string word, meaning;
    avl_node *left, *right;

public:
    friend class avlTree;
};

class avlTree
{
    avl_node *root;

public:
    int height(avl_node *);
    int diff(avl_node *);
    avl_node *ll_rotation(avl_node *);
    avl_node *rr_rotation(avl_node *);
    avl_node *lr_rotation(avl_node *);
    avl_node *rl_rotation(avl_node *);
    avl_node *balance(avl_node *);
    avl_node *insert();
    avl_node *insert(avl_node *, avl_node *);
    void display_levelwise();
    void inorder(avl_node *);
    void preorder(avl_node *);
    void postorder(avl_node *);

    avlTree()
    {
        root = NULL;
    }

    void insert_word()
    {
        avl_node *temp = insert();
        root = insert(root, temp);
    }

    void show()
    {
        display_levelwise();
    }

    void show_inorder()
    {
        inorder(root);
    }
};

avl_node *avlTree::insert()
{
    avl_node *temp = new avl_node;
    cout << "Enter word: ";
    cin >> temp->word;
    cout << "Enter meaning: ";
    cin >> temp->meaning;
    temp->left = temp->right = NULL;
    return temp;
}

avl_node *avlTree::insert(avl_node *root, avl_node *temp)
{
    if (root == NULL)
        return temp;

    if (temp->word < root->word)
    {
        root->left = insert(root->left, temp);
        root = balance(root);
    }
    else if (temp->word > root->word)
    {
        root->right = insert(root->right, temp);
        root = balance(root);
    }

    return root;
}

int avlTree::height(avl_node *temp)
{
    int h = 0;
    if (temp != NULL)
    {
        int l_height = height(temp->left);
        int r_height = height(temp->right);
        h = max(l_height, r_height) + 1;
    }
    return h;
}

int avlTree::diff(avl_node *temp)
{
    int l_height = height(temp->left);
    int r_height = height(temp->right);
    int b_factor = (l_height - r_height);
    return b_factor;
}

avl_node *avlTree::balance(avl_node *temp)
{
    int bal_factor = diff(temp);

    if (bal_factor > 1)
    {
        if (diff(temp->left) > 0)
            temp = ll_rotation(temp);
        else
            temp = lr_rotation(temp);
    }
    else if (bal_factor < -1)
    {
        if (diff(temp->right) > 0)
            temp = rl_rotation(temp);
        else
            temp = rr_rotation(temp);
    }

    return temp;
}

avl_node *avlTree::ll_rotation(avl_node *parent)
{
    avl_node *temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}

avl_node *avlTree::rr_rotation(avl_node *parent)
{
    avl_node *temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

avl_node *avlTree::lr_rotation(avl_node *parent)
{
    avl_node *temp = parent->left;
    parent->left = rr_rotation(temp);
    return ll_rotation(parent);
}

avl_node *avlTree::rl_rotation(avl_node *parent)
{
    avl_node *temp = parent->right;
    parent->right = ll_rotation(temp);
    return rr_rotation(parent);
}

void avlTree::display_levelwise()
{
    if (root == NULL)
    {
        cout << "Tree is empty\n";
        return;
    }

    queue<avl_node *> q;
    q.push(root);

    while (!q.empty())
    {
        int levelSize = q.size();

        while (levelSize--)
        {
            avl_node *temp = q.front();
            q.pop();

            cout << temp->word << " ";

            if (temp->left != NULL)
                q.push(temp->left);

            if (temp->right != NULL)
                q.push(temp->right);
        }

        cout << endl;
    }
}

void avlTree::inorder(avl_node *tree)
{
    if (tree != NULL)
    {
        inorder(tree->left);
        cout << tree->word << " : " << tree->meaning << endl;
        inorder(tree->right);
    }
}

void avlTree::preorder(avl_node *tree)
{
    if (tree != NULL)
    {
        cout << tree->word << " ";
        preorder(tree->left);
        preorder(tree->right);
    }
}

void avlTree::postorder(avl_node *tree)
{
    if (tree != NULL)
    {
        postorder(tree->left);
        postorder(tree->right);
        cout << tree->word << " ";
    }
}

int main()
{
    avlTree obj;
    int choice;

    do
    {
        cout << "\n1.Insert\n2.Display Tree\n3.Inorder\n4.Exit\nEnter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            obj.insert_word();
            break;
        case 2:
            obj.show();
            break;
        case 3:
            obj.show_inorder();
            break;
        }

    } while (choice != 4);

    return 0;
}