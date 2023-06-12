// A Dictionary stores keywords & its meanings. Provide facility for
// adding new keywords, deleting keywords, updating values of any
// entry. Provide facility to display whole data sorted in ascending/
// Descending order. Also find how many maximum comparisons may
// require for finding any keyword. Use Height balance tree and find the
// complexity for finding a keyword.

#include <iostream>
using namespace std;

class node
{
public:
    string key;
    string meaning;
    node *left;
    node *right;
    node()
    {
        key = "";
        meaning = "";
        left = NULL;
        right = NULL;
    }
    node(string key, string meaning)
    {
        this->key = key;
        this->meaning = meaning;
        left = NULL;
        right = NULL;
    }
};

class AVL
{
public:
    node *root;
    AVL()
    {
        root = NULL;
    }
    node *getroot()
    {
        return root;
    }
    void creat();
    node *insert(node *cur, node *temp);
    node *balance(node *temp);
    int diff(node *temp);
    int height(node *temp);
    int max(int a, int b);
    node *LL(node *par);
    node *RR(node *par);
    node *LR(node *par);
    node *RL(node *par);
    void ascending(node *temp);
    void descending(node *temp);
    bool search(int &count_com, node *root, string key);
    // node *update(node *root, string key);
    node *delete_node(node *curr, string key);
    node *minval(node *curr);
};

void AVL::creat()
{
    string key, meaning;
    while (true)
    {
        cout << "\nEnter Keyword/stop(to stop) : ";
        cin >> key;
        if (key == "stop")
        {
            break;
        }
        cout << "Enter meaning : ";
        cin >> meaning;
        node *temp = new node(key, meaning);
        root = insert(root, temp);
    }
}

node *AVL::insert(node *curr, node *temp)
{
    if (curr == NULL)
    {
        return temp;
    }
    if (temp->key < curr->key)
    {
        curr->left = insert(curr->left, temp);
        curr = balance(curr);
    }
    if (temp->key > curr->key)
    {
        curr->right = insert(curr->right, temp);
        curr = balance(curr);
    }
    return curr;
}

node *AVL ::balance(node *temp)
{
    int bal;
    bal = diff(temp);
    if (bal >= 2)
    {
        if (diff(temp->left) < 0)
        {
            temp = LR(temp);
        }
        else
        {
            temp = LL(temp);
        }
    }
    else if (bal <= -2)
    {
        if (diff(temp->right) > 0)
        {
            temp = RL(temp);
        }
        else
        {
            temp = RR(temp);
        }
    }
    return temp;
}

int AVL::diff(node *temp)
{
    int l = height(temp->left);
    int r = height(temp->right);
    return (l - r);
}

int AVL::height(node *temp)
{
    if (temp == NULL)
    {
        return -1;
    }
    else
    {
        return (max(height(temp->left), height(temp->right)) + 1);
    }
}
int AVL::max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

node *AVL::LL(node *par)
{
    node *temp, *temp1;
    temp = par->left;
    temp1 = temp->right;

    temp->right = par;
    par->left = temp1;
    return temp;
}

node *AVL::RR(node *par)
{
    node *temp, *temp1;
    temp = par->right;
    temp1 = temp->left;

    temp->left = par;
    par->right = temp1;
    return temp;
}

node *AVL::LR(node *par)
{
    par->left = RR(par->left);
    return (LL(par));
}

node *AVL::RL(node *par)
{
    par->right = LL(par->right);
    return (RR(par));
}

void AVL::ascending(node *temp)
{
    if (temp != NULL)
    {
        ascending(temp->left);
        cout << temp->key << " : " << temp->meaning << endl;
        ascending(temp->right);
    }
}

void AVL::descending(node *temp)
{
    if (temp != NULL)
    {
        descending(temp->right);
        cout << temp->key << " : " << temp->meaning << endl;
        descending(temp->left);
    }
}

bool AVL::search(int &count_com, node *root, string key1)
{
    count_com++;
    if (root != NULL)
    {
        if (root->key == key1)
        {
            return true;
        }
        if (root->key > key1)
        {
            return search(count_com, root->left, key1);
        }
        else
        {
            return search(count_com, root->right, key1);
        }
    }
    return false;
}

node *AVL::delete_node(node *curr, string key1)
{
    if (curr == NULL)
    {
        cout << "key is not present.." << endl;
        return curr;
    }
    if (key1 < curr->key)
    {
        curr->left = delete_node(curr->left, key1);
    }
    else if (key1 > curr->key)
    {
        curr->right = delete_node(curr->right, key1);
    }
    else // key is found
    {
        node *l = curr->left;
        node *r = curr->right;
        delete curr;

        if (r == NULL)
        {
            return l;
        }
        node *temp = r;
        while (temp->left != NULL)
        {
            temp = temp->left;
        }
        temp->right = minval(r);
        temp->left = l;

        cout << "Key is deleted..." << endl;
        return balance(temp);
    }
    return balance(curr);
}

node *AVL::minval(node *temp)
{
    while (temp != NULL)
    {
        temp = temp->left;
    }
    return temp;
}

int main()
{
    AVL avl;
    int choice;
    string keyval;
    int count_com = 0;

    while (true)
    {
        cout << "1.create" << endl;
        cout << "2.ascending" << endl;
        cout << "3.descending" << endl;
        cout << "4.search" << endl;
        cout << "5.comparison" << endl;
        cout << "6.delete and ascending" << endl;

        cout << "Enter your choice" << endl;
        cin >> choice;

        if (choice == 1)
        {
            avl.creat();
        }
        else if (choice == 2)
        {
            cout << "\n\nAvL tree Traversal in ascending Order : \n\n";
            avl.ascending(avl.getroot());
        }
        else if (choice == 3)
        {
            cout << "\n\nAvL tree Traversal in descending Order : \n\n";
            avl.descending(avl.getroot());
        }
        else if (choice == 4)
        {
            cout << "Enter key you wish to seasrch : ";
            cin >> keyval;
            bool result = avl.search(count_com, avl.getroot(), keyval); // menu 4

            if (result)
            {
                cout << "Key is Present in the dictionary..." << endl;
            }
            else
            {
                cout << "key is Not present in the dictionary..." << endl;
            }
            cout << "\nTotal Number of comparisons required : " << count_com << endl;
        }
        else if (choice == 5)
        {
            cout << "\nEnter keyYou wish to delete : ";
            cin >> keyval;
            avl.delete_node(avl.getroot(), keyval); // menu 5

            avl.ascending(avl.getroot());
        }
        else
        {
            cout << "Exit program" << endl;
        }
    }
    return 0;
}
