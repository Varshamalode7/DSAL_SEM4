// // /*Beginning with an empty binary tree, Construct binary tree by inserting the values in the order given. After constructing a binary tree perform following operations on it-
// // 1)Perform in order / pre order and post order traversal(insert)
// // 2)Change a tree so that the roles of the left and right pointers are swapped at every node(mirror image)
// // 3)Find the height of tree
// // 4)Copy this tree to another [operator=]
// // 5)Count number of leaves, number of internal nodes.
// // 6)Erase(delete) all nodes in a binary tree.
// // (implement both recursive and non-recursive methods)*/

#include <iostream>
#include <queue>
#include <stack>
using namespace std;

class BS
{
    int data;
    BS *left;
    BS *right;

public:
    BS()
    {
        data = 0;
        left = NULL;
        right = NULL;
    }
    BS(int x)
    {
        data = x;
        left = NULL;
        right = NULL;
    }
    BS *insert(BS *root, int val)
    {
        if (root == NULL)
        {
            return new BS(val);
        }
        else
        {
            queue<BS *> q;
            q.push(root);
            while (!q.empty())
            {
                BS *temp = q.front();
                q.pop();
                if (temp->left != NULL)
                {
                    q.push(temp->left);
                }
                else
                {
                    temp->left = new BS(val);
                    return root;
                }
                if (temp->right != NULL)
                {
                    q.push(temp->right);
                }
                else
                {
                    temp->right = new BS(val);
                    return root;
                }
            }
        }
        return root;
    }
     void inorder_re(BS *root)
    {
        if (root == NULL)
        {
            return;
        }
        inorder_re(root->left);
        cout << root->data << " ";
        inorder_re(root->right);
    }

    void inorder_it(BS *root)
    {
        stack<BS *> s;
        BS *temp = root;
        while (!s.empty() || temp != NULL)
        {
            if (temp != NULL)
            {
                s.push(temp);
                temp = temp->left;
            }
            else
            {
                temp = s.top();
                s.pop();
                cout << temp->data << " ";
                temp = temp->right;
            }
        }
    }
     void preorder_re(BS *root)
    {
        if (root == NULL)
        {
            return;
        }
        cout << root->data << " ";
        preorder_re(root->left);
        preorder_re(root->right);
    }
    void preorder_it(BS *root)
    {
        if (root == NULL)
        {
            return;
        }
        else
        {
            stack<BS *> s;
            s.push(root);
            while (!s.empty())
            {
                BS *temp = s.top();
                s.pop();
                cout << temp->data << " ";
                if (temp->right)
                {
                    s.push(temp->right);
                }
                if (temp->left)
                {
                    s.push(temp->left);
                }
            }
        }
    }
    void postorder_re(BS *root)
    {
        if (root == NULL)
        {
            return;
        }
        postorder_re(root->left);
        postorder_re(root->right);
        cout << root->data << " ";
    }
    
    void postorder_it(BS *root)
    {
        if (root == NULL)
        {
            return;
        }
        else
        {
            stack<BS *> s;
            s.push(root);
            stack<int> post;
            while (!s.empty())
            {
                BS *temp = s.top();
                s.pop();
                post.push(temp->data);
                if (temp->left)
                {
                    s.push(temp->left);
                }
                if (temp->right)
                {
                    s.push(temp->right);
                }
            }
            while (!post.empty())
            {
                cout << post.top() << " ";
                post.pop();
            }
        }
    }
    void swap_re(BS *root)
    {
        if (root != NULL)
        {
            if (root->left || root->right)
            {
                BS *temp = root->left;
                root->left = root->right;
                root->right = temp;
            }
            swap_re(root->left);
            swap_re(root->right);
        }
    }

    void swap_ir(BS *root)
    {
        int level = 1;
        queue<BS *> q;
        q.push(root);
        while (!q.empty())
        {
            int n = q.size();
            for (int i = 0; i < n; i++)
            {
                BS *temp = q.front();
                q.pop();
                if ((level + 1) % height_re(root) == 0)
                {
                    BS *temp2 = temp->left;
                    temp->left = temp->right;
                    temp->right = temp2;
                }
                if (temp->right != NULL)
                {
                    q.push(temp->right);
                }
                if (temp->left != NULL)
                {
                    q.push(temp->left);
                }
            }
            level++;
        }
    }

    int height_re(BS *root)
    {
        if (root == NULL)
        {
            return 0;
        }
        else
        {
            int ldepth = height_re(root->left);
            int rdepth = height_re(root->right);
            if (ldepth > rdepth)
            {
                return ldepth + 1;
            }
            else
            {
                return rdepth + 1;
            }
        }
    }

    int height_ir(BS *root)
    {

        int nodes = 0; // Maximum no. of nodes in height.
        int count = 0;

        queue<BS *> q;

        BS *current;

        if (root == NULL)
        {

            return 0;
        }

        q.push(root);

        while (!q.empty())
        {

            nodes++;

            count = q.size();

            while (count--)
            {

                current = q.front();

                if (current->left != NULL)
                {

                    q.push(current->left);
                }

                if (current->right != NULL)
                {

                    q.push(current->right);
                }

                q.pop();
            }
        }

        return nodes;
    }

    int leaves_re(BS *root)
    {

        if (root == NULL)
        {

            return 0;
        }

        if (root->left == NULL && root->right == NULL)
        {

            return 1;
        }

        else
        {

            return leaves_re(root->left) + leaves_re(root->right);
        }
    }

    int leaves_ir(BS *root)
    {

        if (root == NULL)
        {

            return 0;
        }

        else
        {

            queue<BS *> q;

            int count = 0;
            q.push(root);

            while (!q.empty())
            {

                BS *temp = q.front();
                q.pop();

                if (temp->left != NULL)
                {

                    q.push(temp->left);
                }

                if (temp->right != NULL)
                {

                    q.push(temp->right);
                }

                if (temp->left == NULL && temp->right == NULL)
                {

                    count++;
                }
            }

            return count;
        }
    }

    BS *clone_re(BS *root)
    {

        if (root == NULL)
        {

            return NULL;
        }

        else
        {

            BS *nn = new BS(root->data);

            nn->left = clone_re(root->left);
            nn->right = clone_re(root->right);

            return nn;
        }
    }

    BS *clone_ir(BS *root)
    {

        stack<BS *> s;

        BS *nn = new BS(root->data);

        s.push(nn);

        while (!s.empty())
        {

            s.pop();

            if (root->left)
            {

                nn = root->left;
                root = root->left;
                s.push(nn);
            }

            if (root->right)
            {

                nn = root->right;
                root = root->right;
                s.push(nn);
            }
        }

        return nn;
    }

    void erase_re(BS *root)
    {

        if (root == NULL)
        {

            return;
        }

        else
        {

            erase_re(root->left);
            erase_re(root->right);

            cout << "\n\nNode " << root->data << " deleated.";

            free(root);
        }
    }

    void erase_ir(BS *root)
    {

        if (root == NULL)
        {

            return;
        }

        else
        {

            queue<BS *> q;
            q.push(root);

            while (!q.empty())
            {

                BS *temp = q.front();
                q.pop();

                if (temp->left)
                {

                    q.push(temp->left);
                    temp = temp->left;
                }

                if (temp->right)
                {

                    q.push(temp->right);
                    temp = temp->left;
                }

                free(temp);
            }

            root = NULL;
        }
    }

    int max_val(BS *root)
    {

        if (root == NULL)
        {

            return -1;
        }

        else
        {

            int node = root->data;

            int lnode = max_val(root->left);
            int rnode = max_val(root->right);

            if (lnode > node)
            {

                node = lnode;
            }

            if (rnode > node)
            {

                node = rnode;
            }

            return node;
        }
    }

    int min_val(BS *root)
    {

        if (root == NULL)
        {

            return -1;
        }

        else
        {

            int node = root->data;

            int lnode = max_val(root->left);
            int rnode = max_val(root->right);

            if (lnode < node)
            {

                node = lnode;
            }

            if (rnode < node)
            {

                node = rnode;
            }

            return node;
        }
    }
};

int main()
{

    BS *root = NULL;

    int n, ele, choice;

    cout << "\n\nEnter total no. of elements to create Binary Tree: ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {

        cout << "\nEnter the element: ";
        cin >> ele;

        root = root->insert(root, ele);
    }

    cout << "\n\nBinary Tree is(inorder traversal): ";
    root->inorder_re(root);

    while (true)
    {

        cout << "\n\nEnter 1 to perform inorder, preorder and post order traversal\nEnter 2 to change a tree so that the roles of the left and right pointers are swapped at every node\nEnter 3 to find the height of tree\nEnter 4 to copy this tree to another\nEnter 5 to count number of leaves and internal nodes\nEnter 6 to erase all nodes in a binary tree\nEnter 7 to find Minimum and maximum data value in BT";
        cin >> choice;

        if (choice == 1)
        {

            cout << "\n\n\nInorder traversal by recursive method is: ";
            root->inorder_re(root);

            cout << "\n\nInorder traversal by iterative method is: ";
            root->inorder_it(root);

            cout << "\n\nPreorder traversal by recursive method is: ";
            root->preorder_re(root);

            cout << "\n\nPreorder traversal by iterative method is: ";
            root->preorder_it(root);

            cout << "\n\nPostorder traversal by recursive method is: ";
            root->postorder_re(root);

            cout << "\n\nPostorder traversal by iterative method is: ";
            root->postorder_it(root);
        }

        else if (choice == 2)
        {

            cout << "\n\nBinary tree after swapping left and right nodes by recursive method: ";
            root->swap_re(root);
            root->inorder_re(root);

            cout << "\n\n\nBinary tree after swapping left and right nodes by iterative method: ";
            root->swap_ir(root);
            root->inorder_re(root);
        }

        else if (choice == 3)
        {

            cout << "\n\nHeight of Binary tree by recursive approch is: ";
            cout << root->height_re(root) - 1;

            cout << "\n\n\nHeight of Binary tree by iterative approch is: ";
            cout << root->height_ir(root) - 1;
        }

        else if (choice == 4)
        {

            cout << "\n\nCopy of given binary tree to another binary tree by recursive method is: ";
            root->clone_re(root);
            root->inorder_re(root);

            cout << "\n\n\nCopy of given binary tree to another binary tree by iterative method is: ";
            root->clone_ir(root);
            root->inorder_re(root);
        }

        else if (choice == 5)
        {

            cout << "\n\nTotal no. of leaves in Binary tree by recursive method are: ";
            cout << root->leaves_re(root);

            cout << "\n\nTotal no. of internal nodes in Binary tree by recursive method are: ";
            cout << n - root->leaves_re(root);

            cout << "\n\n\nTotal no. of leaves in Binary tree by iterative method are: ";
            cout << root->leaves_ir(root);

            cout << "\n\nTotal no. of internal nodes in Binary tree by iterative method are: ";
            cout << n - root->leaves_ir(root);
        }

        else if (choice == 6)
        {

            cout << "\n\nErasing all nodes in a binary tree: ";
            root->erase_re(root);
        }

        else if (choice == 7)
        {

            cout << "\n\nMaximum data in BT is: ";
            cout << root->max_val(root);

            cout << "\n\nMinimum data in BT is: ";
            cout << root->min_val(root);
        }

        else
        {

            cout << "\n\n\nInvalid choice";
        }

        // cout << "\n\n\nDO YOU WANT TO CONTINUE?(1/0)" << endl;
        // cin >> t;

        // if (t == 1)
        // {

        //     continue;
        // }

        // else
        // {

        //     cout << "\nThank you!!!" << endl;
        //     break;
        // }
    }

    return 0;
}
