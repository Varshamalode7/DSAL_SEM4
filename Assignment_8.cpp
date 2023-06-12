// Given sequence k = k1 <k2 < ... < kn of n sorted keys, with a search
// probability pi for each key ki . Build the Binary search tree that has
// the least search cost given the access probability for each key.

#include <iostream>
using namespace std;

template <class T>
class node
{
public:
    T data;
    node<T> *left;
    node<T> *right;
    node()
    {

        left = right = NULL;
    }
    node(T data)
    {
        this->data = data;
        left = right = NULL;
    }
    template <class B>
    friend class obst;
};

template <class T>
class obst
{
    node<T> *root_node;

public:
    obst()
    {
        root_node = NULL;
    }
    node<T> *get_root()
    {
        return this->root_node;
    }
    node<T> *create_tree(int start, int end, int **r, T *input);

    void calculate_table(double *p, double *q, int temp, T *);
    void show_table(double **weight, double **cost, int **root, int temp);

    void inorder(node<T> *curr);
    void preorder(node<T> *curr);
    void postorder(node<T> *curr);
};

template <class T>
node<T> *obst<T>::create_tree(int start, int end, int **root, T *input)
{
    if (start != end)
    {
        int k = root[start][end];
        node<T> *t = new node<T>(input[k]);

        t->left = create_tree(start, k - 1, root, input);
        t->right = create_tree(k, end, root, input);
        return t;
    }
    else
    {
        return NULL;
    }
}

template <class T>
void obst<T>::calculate_table(double *p, double *q, int temp, T *input)
{
    // cout<<"START"<<endl;
    double **weight = new double *[temp + 1];
    for (int i = 0; i <= temp; i++)
    {
        weight[i] = new double[temp + 1];
    }

    double **cost = new double *[temp + 1];
    for (int i = 0; i <= temp; i++)
    {
        cost[i] = new double[temp + 1];
    }

    int **root = new int *[temp + 1];
    for (int i = 0; i <= temp; i++)
    {
        root[i] = new int[temp + 1];
    }

    //    cout<<"MID"<<endl;
    for (int i = 0; i < temp; i++)
    {
        // For equal i=j that is i-j=0;
        // for null tree
        weight[i][i] = q[i];
        cost[i][i] = 0.0;
        root[i][i] = 0;

        // For i-j=1;
        // for tree with one node
        weight[i][i + 1] = q[i] + q[i + 1] + p[i + 1];
        cost[i][i + 1] = weight[i][i + 1];
        root[i][i + 1] = i + 1;
    }

    // For last entry
    weight[temp][temp] = q[temp];
    cost[temp][temp] = 0.0;
    root[temp][temp] = 0;

    // For i-j=2/3/4/5...
    // for Tree having more than one node

    for (int i = 2; i <= temp; i++)
    {
        for (int j = 0; j <= temp - i; j++)
        {

            weight[j][j + i] = p[j + i] + q[j + i] + weight[j][j + i - 1];

            double min = 999.9;
            int k = 0;
            double sum = 0.0;
            for (int m = j + 1; m <= j + i; m++)
            {
                sum = cost[j][m - 1] + cost[m][j + i];
                if (sum < min)
                {
                    min = sum;
                    k = m;
                }
            }

            cost[j][j + i] = weight[j][j + i] +min;
            root[j][j + i] = k;
        }
    }

    // cout<<"END"<<endl;

    // To display table

    cout << "\n\n"
         << endl;

    cout << "Table For OBST creation => \n\n"
         << endl;
    show_table(weight, cost, root, temp);

    this->root_node=create_tree(0, temp, root, input);
}

template <class T>
void obst<T>::show_table(double **weight, double **cost, int **root, int temp)
{
    for (int i = 0; i <= temp; i++)
    {
        for (int j = i; j <= temp; j++)
        {
            cout << "w[ " << i << "," << j << " ] : " << weight[i][j];
            cout << "\t";
        }
        cout << endl;
        for (int j = i; j <= temp; j++)
        {

            cout << "c[ " << i << "," << j << " ] : " << cost[i][j];
            cout << "\t";
        }
        cout << endl;
        for (int j = i; j <= temp; j++)
        {

            // cout<<"c[ "<<i<<","<<j<<" ] : "<<cost[i][j]<<endl;
            cout << "r[ " << i << "," << j << " ] : " << root[i][j];

            cout << "\t";
        }

        cout << "\n\n";
    }
}

template <class T>
void obst<T>::inorder(node<T> *curr)
{
    if (curr != NULL)
    {
        inorder(curr->left);
        cout << curr->data << "  ";
        inorder(curr->right);
    }
}

template <class T>
void obst<T>::preorder(node<T> *curr)
{
    if (curr != NULL)
    {

        cout << curr->data << "  ";
        preorder(curr->left);
        preorder(curr->right);
    }
}

template <class T>
void obst<T>::postorder(node<T> *curr)
{
    if (curr != NULL)
    {
        postorder(curr->left);
        postorder(curr->right);
        cout << curr->data << "  ";
    }
}

int main()
{
    obst<string> st;
    int choice, temp;

    while (true)
    {
        cout<<" 1. To Create Table"<<endl;
        cout<<" 2.To show Inorder traversal"<<endl;
        cout<<" 3.To show Preorder Traversal"<<endl;
        cout<<" 4.To show Postorder traversal"<< endl;

        cout << "Enter Your choice : "<<endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            cout << "\nEnter Number of identifiers : ";
            cin >> temp;

            string *input = new string[temp + 1];
            double *p = new double[temp];
            double *q = new double[temp + 1];

            cout << "\nEnter Identifiers... ";
            for (int i =1; i <=temp; i++)
            {
                cout << "\nEnter identifier " << i  << " : ";
                cin >> input[i];
            }
            cout << "\nEnter Probabilities of successful search... ";
            for (int i = 1; i <= temp; i++)
            {
                cout << "\nEnter successful probability " << i << " : ";
                cin >> p[i];
            }
            cout << "\nEnter Probabilities of Unsuccessful search... ";
            for (int i = 0; i <= temp; i++)
            {
                cout << "\nEnter Unsuccessful probability " << i << " : ";
                cin >> q[i];
            }

            st.calculate_table(p, q, temp, input);
            break;
        }

        case 2:
        {
            cout << "\nInorder traversal : ";

            st.inorder(st.get_root());
            break;
        }

        case 3:
        {
            cout << "\nPreorder traversal : ";

            st.preorder(st.get_root());
            break;
        }
        case 4:
        {
            cout << "\nPostorder traversal : ";

            st.postorder(st.get_root());
            break;
        }
        default:
        {
            cout << "\nEnd Of program!!" << endl;
            exit(0);
            break;
        }
        }
    }
}
