// Implement all the functions of a dictionary (ADT) using open
// hashing technique: separate chaining using linked list Data: Set of
// (key, value) pairs, Keys are mapped to values, Keys must be
// comparable, and Keys must be unique. Standard Operations: Insert
//(key, value), Find(key), Delete(key)

#include <iostream>
// #include <stdlib.h>
using namespace std;

class Node
{
    string key;
    string value;
    Node *next;

public:
    Node()
    {
        key = " ";
        value = " ";
        next = NULL;
    }
    Node(string s1, string s2)
    {
        key = s1;
        value = s2;
        next = NULL;
    }
    friend class Dictionary;
};
class Dictionary
{
    Node *HashTable[26];//array of pointer

public:
    void CreateHT()
    {
        for (int i = 0; i < 26; i++)
        {
            HashTable[i] = NULL;
        }
    }
     int HashFunc(string s)
    {
        return (int(s[0]) % 97);//external typecasting
    }
    void Insert()
    {
        string s1, s2;
        cout << "Enter the key" << endl;
        cin >> s1;
        cout << "Enter the value" << endl;
        cin >> s2;
        Node *nn = new Node(s1, s2);
        int Loc = HashFunc(s1);
        if (HashTable[Loc] == NULL)
        {
            HashTable[Loc] = nn;
        }
        else
        {
            Node *temp = HashTable[Loc];
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = nn;
        }
        cout << "Key Inserted" << endl;
        char choice;
        cout << "Do you want to insert another word (y/n)" << endl;
        cin >> choice;
        if (choice == 'y')
        {
            Insert();
        }
        else
        {
            return;
        }
    }

    void Display()
    {
        cout << "Index"<< "\t"<< "Word"<< "\t"<< "Meaning" << endl;
        for (int i = 0; i < 26; i++)
        {
            cout << i + 1 << "\t";
            if (HashTable[i] == NULL)
            {
                cout << "--" << endl;
            }
            else
            {
                Node *temp = HashTable[i];
                while (temp != NULL)
                {
                    cout << "->" << temp->key << ":"
                         << "\t" << temp->value;
                    temp = temp->next;
                }
            }
            cout << endl;
        }
    }
    void deletion()
    {
        string s;
        cout << "Enter the key to be deleted" << endl;
        cin >> s;

        int Loc = HashFunc(s);
        if (HashTable[Loc] == NULL)
        {
            cout << "Key not present" << endl;
        }

        Node *temp = HashTable[Loc];
        Node *prev = NULL;
        if (temp->key == s)
        {
            temp = temp->next;
            delete (HashTable[Loc]);
            cout << "Key deleted" << endl;
            HashTable[Loc] = temp;
            temp = NULL;
        }
        else
        {
            while (temp->key != s && temp != NULL)
            {
                prev = temp;
                temp = temp->next;
            }
            if (temp->key == s)
            {
                prev->next = temp->next;
                delete (temp);
                cout << "key deleted" << endl;
            }
            else
            {
                cout << "Key not found" << endl;
            }
        }
    }
    void searching()
    {
        string s;
        cout << "Enter the string to be searched" << endl;
        cin >> s;

        int Loc = HashFunc(s);
        Node *temp = HashTable[Loc];
        if (HashTable[Loc] == NULL)
        {
            cout << "Key not present" << endl;
        }
        else if (temp->key == s)
        {
            cout << "KEY FOUND" << endl;
            cout << temp->key << ":" << temp->value << endl;
        }
        else
        {
            while (temp != NULL && temp->key != s)
            {

                temp = temp->next;
            }
            if (temp == NULL)
            {
                cout << "KEY NOT FOUND" << endl;
            }
            else
            {
                cout << "KEY FOUND" << endl;
                cout << temp->key << ":" << temp->value << endl;
            }
        }
    }
};
int main()
{
    Dictionary D;
    D.CreateHT();
    while (true)
    {
        cout << "----------MENU----------" << endl;
        cout << "1.Insert key" << endl;
        cout << "2.Display " << endl;
        cout << "3.Delete key" << endl;
        cout << "4.Search key" << endl;

        int choice;
        cout << "ENTER YOUR CHOICE " << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
            D.Insert();
            break;
        case 2:
            D.Display();
            break;
        case 3:
            D.deletion();
            break;
        case 4:
            D.searching();
            break;
        }
    }
}

