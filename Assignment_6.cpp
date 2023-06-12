
// There are fight paths between the cities. If there is a fight between the
// city A and city B then there is an edge between the city A to B. The
// cost of an edge represents the time required or fuel required to travel
// from city A to B. Represent this as a graph using adjacency list where
// every node of graph represented by city name. Perform following
// operations 1) calculate in degree, out degree of vertices 2) check
// whether graph is connected or not.

#include <iostream>
#include <string.h>
using namespace std;

class DLLNode
{
public:
    char data[10];
    DLLNode *down;
    DLLNode *next;
} *Head;//obj of poiter

class Stack
{
public:
    char vertex[10];
    int in_stack(char node[]);
} stk[10];

int Stack ::in_stack(char node[])
{
    int i, present = 0;
    for (i = 0; i < 10; i++)
    {
        if (strcmp(stk[i].vertex, node) == 0)
            present = 1;
    }
    return present;
}

class Queue
{
public:
    char vertex[10];
    int in_Queue(char node[]);
} que[10];

int Queue ::in_Queue(char node[])
{
    int i, present = 0;
    for (i = 0; i < 10; i++)
    {
        if (strcmp(que[i].vertex, node) == 0)
            present = 1;
    }
    return present;
}

class Graph : public DLLNode, public Stack, public Queue
{
public:
    DLLNode *create_Graph(DLLNode *head);
    void display_Graph();
    void traverse_DFS();
    void traverse_BFS();
    void check_degree();
};

DLLNode *Graph ::create_Graph(DLLNode *head)
{
    int vertices, adjacent;
    DLLNode *tmp, *move, *Newnode;
    cout << "\n\t How many vertices..? : ";
    cin >> vertices;
    for (int i = 0; i < vertices; i++)
    {
        Newnode = new DLLNode;
        cout << "\n\t Enter name of Vertex:";
        cin >> Newnode->data;
        Newnode->next = NULL;
        Newnode->down = NULL;
        if (head == NULL)
        {
            head = Newnode;
            move = tmp = head;
        }
        else
        {
            move->down = Newnode;
            move = move->down;
            tmp = move;
        }
        cout << "\n\t How many adjacent vertices.? :";
        cin >> adjacent;
        for (int j = 0; j < adjacent; j++)
        {
            Newnode = new DLLNode;
            cout << "\n\t\t Enter name of Adjacent Vertex:";
            cin >> Newnode->data;
            Newnode->next = NULL;
            Newnode->down = NULL;
            tmp->next = Newnode;
            tmp = Newnode;
        }
    }
    return head;
    cout << endl;
}

void Graph ::display_Graph()
{
    DLLNode *tmp, *move;
    cout << "\nVertex :--> Adjacent Vertices....";
    move = Head;
    while (move != NULL)
    {
        cout << "\n"
             << move->data << " : ";
        tmp = move->next;
        while (tmp != NULL)
        {
            cout << "-->" << tmp->data;
            tmp = tmp->next;
        }
        move = move->down;
    }
}

void Graph ::traverse_DFS()
{
    DLLNode *tmp;
    int done, top = -1;
    tmp = Head;
    if (!(in_stack(tmp->data)))
    {
        top++;
        strcpy(stk[top].vertex, tmp->data);
        cout << "DFS : " << stk[top].vertex;
        while (top != -1)
        {
            tmp = Head;
            while (strcmp(stk[top].vertex, tmp->data) != 0)
                tmp = tmp->down;
            tmp = tmp->next;
            done = 0;
            while (tmp != NULL && done == 0)
            {
                if (!(in_stack(tmp->data)))
                {
                    top++;
                    strcpy(stk[top].vertex, tmp->data);
                    cout << " , " << stk[top].vertex;
                    done = 1;
                }
                else
                    tmp = tmp->next;
            }
            if (tmp == NULL)
                top--;
        }
    }
    else
    {
        cout << "\n\t Can not start DFS from Vertex: " << tmp->data;
    }
}

void Graph ::traverse_BFS()
{
    DLLNode *tmp;
    int front, rear;
    front = rear = -1;
    tmp = Head;
    if (!(in_Queue(tmp->data)))
    {
        rear++;
        strcpy(que[rear].vertex, tmp->data);
        cout << "BFS:" << que[rear].vertex;
        while (front != rear)
        {
            tmp = Head;
            front++;
            while (strcmp(que[front].vertex, tmp->data) != 0)

                tmp = tmp->down;

            tmp = tmp->next;
            while (tmp != NULL)
            {
                if (!(in_Queue(tmp->data)))
                {
                    rear++;
                    strcpy(que[rear].vertex, tmp->data);
                    cout << " , " << que[rear].vertex;
                }
                else
                    tmp = tmp->next;
            }
        }
    }
    else
    {
        cout << "\n\t Can not start DFS from Vertex: " << tmp->data;
    }
}

void Graph ::check_degree()
{
    DLLNode *tmp, *move;
    int cnt, flag = 0;
    cout << "\n\n Vertex : Degree....";
    move = Head;
    while (move != NULL)
    {
        cout << "\n"
             << move->data << " : ";
        tmp = move->next;
        cnt = 0;
        while (tmp != NULL)
        {
            cnt++;
            tmp = tmp->next;
        }
        cout << " " << cnt;
        if (cnt == 0)
            flag = 1;
        move = move->down;
    }
    if (flag == 0)
        cout << "\n\n As all Vertices has Degree = 0, the Graph is Connected.";
    else
        cout << "\n\n As some Vertices has Degree = 0, the Graph is Disconnected.";
}

int main()
{
    Graph G1;
    Head = NULL;
    int choice;
    while (true)
    {
        cout << endl;
        cout << "1.Create graph" << endl;
        cout << "2.Display graph" << endl;
        cout << "3.DFS Traversal of graph" << endl;
        cout << "4.BFS Traversal of graph" << endl;
        cout << "5.Find indegree and Check graph is connected or not" << endl;

        cout << "Enter your choice" << endl;
        cin >> choice;

        if (choice == 1)
        {
            Head = G1.create_Graph(Head);
        }
        else if (choice == 2)
        {
            G1.display_Graph();
        }
        else if (choice == 3)
        {
            G1.traverse_DFS();
        }
        else if (choice == 4)
        {
            G1.traverse_BFS();
        }
        else if (choice == 5)
        {
            G1.check_degree();
        }
        else
        {
            cout << "Thank you enter valid choice" << endl;
        }
    }

    return 0;
}
