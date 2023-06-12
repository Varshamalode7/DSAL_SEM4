// Create an inordered threaded binary search tree. Perform inorder,
// preorder traversals without recursion and deletion of a node. Analyze
// time and space complexity of the algorithm.

#include <iostream>
using namespace std;

class Node
{
	int data;
	Node *left, *right;
	bool lthread, rthread;

public:
	Node(int d)
	{
		data = d;
		left = right = NULL;
		lthread = rthread = true;
	}
	friend class ThreadedBinaryTree;
};

class ThreadedBinaryTree
{
public:
	Node *root = NULL;
	void insert(int item)
	{
		Node *newnode = new Node(item);
		if (root == NULL)
		{
			root = newnode;
			return;
		}
		Node *temp = root;
		Node *parent = NULL;
		while (temp != NULL)
		{
			if (item == temp->data)
			{
				cout << "Element already exists" << endl;
				return;
			}
			parent = temp;
			if (item < temp->data)
			{
				if (temp->lthread == false)
					temp = temp->left;
				else
					break;
			}
			else
			{
				if (temp->rthread == false)
					temp = temp->right;
				else
					break;
			}
		}
		if (item < temp->data)
		{
			newnode->left = parent->left;
			newnode->right = parent;
			parent->lthread = false;
			parent->left = newnode;
		}
		else
		{
			newnode->left = parent;
			newnode->right = parent->right;
			parent->rthread = false;
			parent->right = newnode;
		}
	}

	Node *inordersuccessor(Node *node)
	{
		if (node->rthread == true)
			return node->right;
		node = node->right;
		while (node->lthread == false)
			node = node->left;
		return node;
	}

	Node *inpred(Node *ptr)
	{
		if (ptr->lthread == true)
			return ptr->left;
		ptr = ptr->left;
		while (ptr->rthread == false)
			ptr = ptr->right;
		return ptr;
	}

	void inorder(Node *node)
	{
		if (node == NULL)
		{
			cout << "Tree is empty" << endl;
			return;
		}
		Node *ptr = node;
		while (ptr->lthread == false)
			ptr = ptr->left;
		while (ptr != NULL)
		{
			cout << ptr->data << " -> ";
			ptr = inordersuccessor(ptr);
		}
	}

	void preorder(Node *node)
	{
		if (node == NULL)
		{
			cout << "Tree is empty" << endl;
			return;
		}
		Node *ptr = node;
		while (ptr != NULL)
		{
			cout << ptr->data << " -> ";
			if (ptr->lthread == false)
				ptr = ptr->left;
			else if (ptr->rthread == false)
				ptr = ptr->right;
			else
			{
				while (ptr != NULL && ptr->rthread == true)
					ptr = ptr->right;
				if (ptr != NULL)
					ptr = ptr->right;
			}
		}
	}

	Node *caseA(Node *root, Node *par, Node *ptr)
	{
		if (par == NULL)
			root = NULL;
		else if (ptr == par->left)
		{
			par->lthread = true;
			par->left = ptr->left;
		}
		else
		{
			par->rthread = true;
			par->right = ptr->right;
		}
		delete ptr;
		return root;
	}

	Node *caseB(Node *root, Node *par, Node *ptr)
	{
		Node *child;
		if (ptr->lthread == false)
			child = ptr->left;
		else
			child = ptr->right;
		if (par == NULL)
			root = child;
		else if (ptr == par->left)
			par->left = child;
		else
			par->right = child;
		Node *s = inordersuccessor(ptr);
		Node *p = inpred(ptr);
		if (ptr->lthread == false)
			p->right = s;
		else
		{
			if (ptr->rthread == false)
				s->left = p;
		}
		delete ptr;
		return root;
	}

	Node *caseC(Node *root, Node *par, Node *ptr)
	{
		Node *parsucc = ptr;
		Node *succ = ptr->right;
		while (succ->lthread == false)
		{
			parsucc = succ;
			succ = succ->left;
		}
		ptr->data = succ->data;
		if (succ->lthread == true && succ->rthread == true)
			root = caseA(root, parsucc, succ);
		else
			root = caseB(root, parsucc, succ);
		return root;
	}

	Node *deletion(Node *root, int item)
	{
		Node *par = NULL;
		Node *ptr = root;
		int found = 0;
		while (ptr != NULL)
		{
			if (item == ptr->data)
			{
				found = 1;
				break;
			}
			par = ptr;
			if (item < ptr->data)
			{
				if (ptr->lthread == false)
					ptr = ptr->left;
				else
					break;
			}
			else
			{
				if (ptr->rthread == false)
					ptr = ptr->right;
				else
					break;
			}
		}
		if (found == 0)
		{
			cout << "Element not present" << endl;
			return NULL;
		}
		else if (ptr->lthread == false && ptr->rthread == false)
			root = caseC(root, par, ptr);
		else if (ptr->lthread == false)
			root = caseB(root, par, ptr);
		else if (ptr->rthread == false)
			root = caseB(root, par, ptr);
		else
			root = caseA(root, par, ptr);
		return root;
	}
};

int main()
{
	ThreadedBinaryTree obj;
	while (true)
	{
		cout << "1. Creating the Threaded Binary Tree." << endl;
		cout << "2. Displaying the Threaded Binary Tree." << endl;
		cout << "3. Deleting an element." << endl;
		cout << "4.Inserting nodes in bst" << endl;
		cout << "5. Exit." << endl;
		int choice;
		cout << "Enter your choice:" << endl;
		cin >> choice;
		if (choice == 1)
		{
			cout << "Enter the number of elements" << endl;
			int n;
			cin >> n;
			cout << "Enter the elements:" << endl;
			int ele;
			for (int i = 1; i <= n; i++)
			{
				cin >> ele;
				obj.insert(ele);
			}
		}
		else if (choice == 2)
		{
			cout << "Inorder Traversal:";
			obj.inorder(obj.root);
			cout << endl;
			cout << "Preorder Traversal:";
			obj.preorder(obj.root);
			cout << endl;
		}
		else if (choice == 3)
		{
			cout << "Enter an element to be deleted" << endl;
			int ele;
			cin >> ele;
			cout << "Inorder Traversal before deletion:";
			obj.inorder(obj.root);
			cout << endl;
			obj.root = obj.deletion(obj.root, ele);
			cout << "Inorder Traversal after deletion:";
			obj.inorder(obj.root);
			cout << endl;
		}
		else if (choice == 4)
		{
			// cout << "Enter the number of elements" << endl;
			// int n;
			// cin >> n;
			// cout << "Enter the elements:" << endl;
			// int ele;
			// for (int i = 1; i <= n; i++)
			// {
			// 	cin >> ele;
			// 	obj.insert(ele);
			// }
			int ele;
			cout << "Enter the ele you want to insert" << endl;
			cin >> ele;
			obj.insert(ele);
		}
		else if (choice == 5)
		{
			cout << "Program exited successfully." << endl;
			break;
		}
		else
		{
			cout << "Invalid choice. Please enter a valid number from 1 to 4." << endl;
		}
	}
	return 0;
}
