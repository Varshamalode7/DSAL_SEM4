                        //Assignment_1
                        
// /*Beginning with an empty binary search tree. Construct the binary
// search tree by inserting the values in given order. After constructing
// binary search tree perform following operations 1) Insert a new node 2)
// Find numbers of node in longest path 3) Minimum and maximum data
// value found in tree 4) Change a tree so that the roles of the left and
// right pointers are swapped at every node 5)Search an element*/

#include <iostream>
using namespace std;

class Node
{
    int key;
    Node *left, *right;

public:
    Node(int x)
    {
        key = x;
        left = right = NULL;
    }
    friend class BST;
};

class BST
{
public:
    Node *root = NULL;
    Node *create(int item)
    {
        Node *temp = new Node(item);
        return temp;
    }
    Node *insert(Node *node, int key)
    {
        if (node == NULL)
            return create(key);
        if (key < node->key)//key-->insert new key && node->key is inserted key
            node->left = insert(node->left, key);
        else
            node->right = insert(node->right, key);
        return node;
    }
    void inorder(Node *root)
    {
        if (root != NULL)
        {
            inorder(root->left);//if root ka left is not equal to null then go to inorder fun ,otherwise go to next line
            cout << root->key << " -> ";
            inorder(root->right);
        }
    }
    void preorder(Node *root)
    {
        if (root != NULL)
        {
            cout << root->key << " -> ";
            preorder(root->left);
            preorder(root->right);
        }
    }
    void postorder(Node *root)
    {
        if (root != NULL)
        {
            postorder(root->left);
            postorder(root->right);
            cout << root->key << " -> ";
        }
    }
    void swapping(Node *root)
    {
        Node *p = root;
        if (p)
        {
            if (p->left || p->right)
            {
                Node *temp;
                temp = p->left;
                p->left = p->right;
                p->right = temp;
            }
            swapping(p->left);
            swapping(p->right);
        }
    }
    int minvalue(Node *node)
    {
        Node *current = node;
        while (current->left != NULL)
        {
            current = current->left;
        }
        return (current->key);
    }
    int maxvalue(Node *node)
    {
        Node *current = node;
        while (current->right != NULL)
            current = current->right;
        return (current->key);
    }
    void search(Node *&parent, Node *&curr, int key)
    {
        while (curr != NULL)
        {
            if (curr->key == key)
            {
                cout << "Element present in BST" << endl;
                return;
            }
            else if (curr->key > key)
            {
                parent = curr;
                curr = curr->left;
            }
            else
            {
                parent = curr;
                curr = curr->right;
            }
        }
        cout << "Element Not Found" << endl;
        return;
    }
    int maxdepth(Node *node)
    {
        if (node == NULL)
            return 0;
        else
        {
            int ldepth = maxdepth(node->left);
            int rdepth = maxdepth(node->right);
            if (ldepth > rdepth)
                return (ldepth + 1);
            else
                return (rdepth + 1);
        }
    }
    void deletenode(Node *&root, int key)
    {
        Node *parent = NULL;
        Node *curr = root;
        search(parent, curr, key);
        if (curr == NULL)
        {
            cout << key << " not present in BST" << endl;
            return;
        }
        if (curr->left == NULL && curr->right == NULL)
        {
            if (curr != root)
            {
                if (parent->left == curr)
                    parent->left = NULL;
                else
                    parent->right = NULL;
            }
            else
                root = NULL;

            delete curr;
        }
        else if (curr->left && curr->right)
        {
            Node *succ = new Node(minvalue(curr->right));
            int val = succ->key;
            deletenode(root, succ->key);
            curr->key = val;
        }
        else
        {
            Node *child = (curr->left) ? curr->left : curr->right;

            if (curr != root)
            {
                if (curr == parent->left)
                    parent->left = child;
                else
                    parent->right = child;
            }

            else
                root = child;
            delete curr;
        }
    }
};

int main()
{
    BST obj;
    while (true)
    {
        cout << "1. Creating the BST" << endl;
        cout << "2. Displaying the BST" << endl;
        cout << "3. Number of nodes in longest path from root" << endl;
        cout << "4. Minimum and Maximum data value found in the BST" << endl;
        cout << "5. Change the tree so that the roles of the left and right pointers are swapped at every node" << endl;
        cout << "6. Search a value" << endl;
        cout << "7. Deleting a value" << endl;
        cout << "8. Exit" << endl;
        int choice;
        cout << "Enter your choice" << endl;
        cin >> choice;
        if (choice == 1)
        {
            cout << "Enter the number of elements:" << endl;
            int n;
            cin >> n;
            cout << "Enter the elements:" << endl;
            int ele;
            for (int i = 1; i <= n; i++)
            {
                cin >> ele;
                obj.root = obj.insert(obj.root, ele);
            }
        }
        else if (choice == 2)
        {
            cout << "Preorder Traversal:";
            obj.preorder(obj.root);
            cout << endl;
            cout << "Inorder Traversal:";
            obj.inorder(obj.root);
            cout << endl;
            cout << "Postorder Traversal:";
            obj.postorder(obj.root);
            cout << endl;
        }
        else if (choice == 3)
        {
            cout << "Number of nodes in longest path from root are:" << obj.maxdepth(obj.root) << endl;
        }
        else if (choice == 4)
        {
            cout << "Minimum data value in BST is:" << obj.minvalue(obj.root) << endl;
            cout << "Maximum data value in BST is:" << obj.maxvalue(obj.root) << endl;
        }
        else if (choice == 5)
        {
            cout << "Before swapping" << endl;
            cout << "Inorder Traversal:";
            obj.inorder(obj.root);
            cout << endl;
            cout << "After swapping" << endl;
            cout << "Inorder Traversal:";
            obj.swapping(obj.root);
            obj.inorder(obj.root);
            cout << endl;
        }
        else if (choice == 6)
        {
            cout << "Enter the element to be searched for:" << endl;
            int item;
            cin >> item;
            Node *parent = NULL;
            obj.search(parent, obj.root, item);
        }
        else if (choice == 7)
        {
            int item;
            cout << "Enter the value to be deleted" << endl;
            cin >> item;
            obj.deletenode(obj.root, item);
            cout << "Element deleted successfully" << endl; 
            cout << "Inorder Traversal after deletion is:";
            obj.inorder(obj.root);
            cout << endl;
        }
        else if (choice == 8)
        {
            cout << "Program exited successfully" << endl;
            break;
        }
        else if (choice == 9)
        {
            cout << "Invalid choice. PLease enter a valid choice from 1 to 8." << endl;
        }
    }

    return 0;
}
