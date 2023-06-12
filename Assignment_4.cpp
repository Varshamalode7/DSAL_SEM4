/* Online C++ compiler to run C++ program online
 Title:-Consider telephone book database of N clients. Make use of a hash
 table implementation to quickly look up client’s telephone number.
 Make use of two collision handling techniques and compare them using
 number of comparisons required to find a set of telephone numbers
 (Note: Use linear probing with replacement and without replacement)*/

#include <iostream>
#include <string.h>
#include <iomanip>
using namespace std;

class Hashtable
{
    char Cname[20];
    long int telephone;

public:
    void create_Ht();
    void show_Ht();
    int Hash(char nm[]);
    void insert_HT1();
    void insert_HT2(char name[],int tele);
    void search_HT1();
    void search_HT2();
} HT1[10], HT2[10];  //array of obj

void Hashtable::create_Ht()
{
    int tablesize = 10;
    for (int i = 0; i < tablesize; i++)
    {
        strcpy(HT1[i].Cname, "-----");
        HT1[i].telephone = 0;
        strcpy(HT2[i].Cname, "-----");
        HT2[i].telephone = 0;
    }
}

void Hashtable::show_Ht()
{
    int tablesize = 10;
    cout << "Hash table 1"<< "\t\t\t\t"<< "Hash table 2" << endl;
    cout << "Index Cname Telephone"<< "\t\t\t\t"<< "Index \t Cname \t Telephone \t"<< "\t\t\t\t" << endl;
    for (int i = 0; i < tablesize; i++)
    {
        cout << i << "\t" << HT1[i].Cname << "\t" << HT1[i].telephone << setw(34) << i << "\t" << HT2[i].Cname << "\t" << HT2[i].telephone << endl;
    }
}

int Hashtable::Hash(char nm[])
{
    int tablesize = 10;
    int ascii = 0;
    for (int i = 0; nm[i] != '\0'; i++)
    {
        ascii = ascii + nm[i];
    }
    return (ascii % tablesize);
}

void Hashtable::insert_HT1()
{
    int cnt, index, tele, tablesize = 10;
    char name[20];
    cout << "How many ele you want to insert" << endl;
    cin >> cnt;
    for (int i = 0; i < cnt; i++)
    {
        cout << "Enter the client name" << endl;
        cin >> name;
        cout << "Enter the telephone number" << endl;
        cin >> tele;
        index = Hash(name);
        if (HT1[index].telephone == 0)
        {
            strcpy(HT1[index].Cname, name);
            HT1[index].telephone = tele;
        }
        else
        {
            do
            {
              index = ((index + 1) % tablesize);
            } while (HT1[index].telephone != 0);
            strcpy(HT1[index].Cname, name);
            HT1[index].telephone = tele;
        }
        insert_HT2(name,tele);
    }
}

void Hashtable::insert_HT2(char name[],int tele)
{
    int cnt, index, tablesize = 10;
    int Actual_index, Current_index, New_index;
        index = Hash(name);
        if (HT2[index].telephone == 0)
        {
            strcpy(HT2[index].Cname, name);
            HT2[index].telephone = tele;
        }
        else
        {
            Current_index = index;
            Actual_index = Hash(HT2[index].Cname);
            do
            {
                index = ((index + 1) % tablesize);
            } while (HT2[index].telephone != 0);
            New_index = index;
            if (Current_index == Actual_index)
            {
                strcpy(HT2[New_index].Cname, name);
                HT2[New_index].telephone = tele;
            }
            else
            {
                strcpy(HT2[New_index].Cname, HT2[Current_index].Cname);
                HT2[New_index].telephone = HT2[Current_index].telephone;
                strcpy(HT2[Current_index].Cname, name);
                HT2[Current_index].telephone = tele;
            }
        }
}

void Hashtable::search_HT1(){
    int cnt,index,comp,cmp,tablesize=10;
    char name[20];
    comp=0;
    cout<<"How many element you want to seach "<<endl;
    cin>>cnt;

    for(int i=0;i<cnt;i++){
        cmp=0;
        cout<<"Enter the client name you want to search"<<endl;
        cin>>name;
        index=Hash(name);
        if(strcmp(HT1[index].Cname,name)==0){
            cmp++;
            cout<<"Then  the telephone number of search name is"<<HT1[index].telephone<<endl;
        }
        else{
            cmp++;
            do{
                index=((index+1)%tablesize);
                cmp++;
            }while(strcmp(HT1[index].Cname,name)!=0);
            cout<<"Then  the telephone number of search name is"<<HT1[index].telephone<<endl;

            cout<<"Needed comparison for a single element"<<cmp<<endl;
            comp=comp+cmp;
        }
    }
    cout<<"Total needed comparison are"<<comp<<endl;
}

void Hashtable::search_HT2(){
    int cnt,index,comp,cmp,tablesize=10;
    char name[20];
    comp=0;
    cout<<"How many element you want to seach "<<endl;
    cin>>cnt;

    for(int i=0;i<cnt;i++){
        cmp=0;
        cout<<"Enter the client name you want to search"<<endl;
        cin>>name;
        index=Hash(name);
        if(strcmp(HT2[index].Cname,name)==0){
            cmp++;
            cout<<"Then  the telephone number of search name is"<<HT2[index].telephone<<endl;
        }
        else{
            cmp++;
            do{
                index=((index+1)%tablesize);
                cmp++;
            }while(strcmp(HT2[index].Cname,name)!=0);
            cout<<"Then  the telephone number of search name is"<<HT2[index].telephone<<endl;

            cout<<"Needed comparison for a single element"<<cmp<<endl;
            comp=comp+cmp;
        }
    }
    cout<<"Total needed comparison are"<<comp<<endl;
}
int main()
{
    Hashtable obj;
    int choice;

    while (true)
    {
        cout << "1.Create hash function" << endl;
        cout << "2.show/display hashtable " << endl;
        cout << "3.Insert in ht 1 and in Ht 2" << endl;
        cout << "4.Search name in ht 1" << endl;
        cout << "5.search name in ht 2" << endl;

        cout << "Enter the choice" << endl;
        cin >> choice;

        if (choice == 1)
        {
            obj.create_Ht();
        }
        else if (choice == 2)
        {
            obj.show_Ht();
        }
        else if (choice == 3)
        {
            obj.insert_HT1();
        }
        else if (choice == 4)
        {
            obj.search_HT1();
        }
        else if (choice == 5)
        {
            obj.search_HT2();
        }
        else
        {
            cout << "Enter the valid choice" << endl;
        }
    }

    return 0;
}

// #include <iostream>
// #include <string.h>
// #include<iomanip>
// using namespace std;
// //.......................Class Definition
// class HashTable
// {
//     char Cname[20];
//      long int telephone;

// public:
//     void create_HT();
//     void show_HT();
//     int Hash(char nm[]);
//     void insert_HT1();
//     void insert_HT2(char name[],int tele);
//     void search_HT1();
//     void search_HT2();
// } HT1[10], HT2[10];//aaray of obj 
// //..................................Member Function Definition
// void HashTable ::create_HT()
// {
//     int Tablesize = 10;
//     for (int i = 0; i < Tablesize; i++)
//     {
//         strcpy(HT1[i].Cname, "----");
//         HT1[i].telephone = 0;
//         strcpy(HT2[i].Cname, "----");
//         HT2[i].telephone = 0;
//     }
// }

// void HashTable ::show_HT()
// {
//     int i, Tablesize = 10;
//     cout << "\n\n ----Hash Table-01--- \t\t\t\t---Hash Table-02---"<<endl;
//     cout << "\n\n Index Cname-Telephone\t\t\t\t Index Cname-Telephone"<<endl;
//     for (i = 0; i < Tablesize; i++)
//     {
//         cout  << i << "\t" << HT1[i].Cname << "\t" << HT1[i].telephone<< setw(32)<< i << "\t" << HT2[i].Cname << "\t" << HT2[i].telephone<<endl;;
       
//     }
// }
// int HashTable ::Hash(char nm[])
// {
//     int askii = 0;
//     int Tablesize = 10;

//     for (int i = 0; nm[i] != '\0'; i++)
//     {
//         askii = askii + nm[i];//internl typecasting
//     }
//     return (askii % Tablesize);
// }

// void HashTable ::insert_HT1()
// {
//     int i, cnt, tele, index, Tablesize = 10;
//     char name[20];
//     cout << "\n How many records u wanna insert..?: ";
//     cin >> cnt;
//     for (i = 0; i < cnt; i++)
//     {
//         cout << "\n\t Enter Client Name:";
//         cin >> name;
//         cout << "\n\t Enter Telephone No:";
//         cin >> tele;
//         index = Hash(name);
//         if (HT1[index].telephone == 0)
//         {
//             strcpy(HT1[index].Cname, name);
//             HT1[index].telephone = tele;
//         }
//         else
//         {
//             do
//             {
//                 index = ((index + 1) % Tablesize);
//             } while (HT1[index].telephone != 0);
//             strcpy(HT1[index].Cname, name);
//             HT1[index].telephone = tele;
//         }
//         insert_HT2(name,tele);
//     }
// }
// void HashTable ::insert_HT2(char name[],int tele)
// {
//     int i, cnt, index, Tablesize = 10;
//     //char name[20];
//     int Act_Index, Cur_Index, New_Index;
//     index = Hash(name);
//     if (HT2[index].telephone == 0)
//     {
//         strcpy(HT2[index].Cname, name);
//         HT2[index].telephone = tele;
//     }
//     else
//     {
//         Cur_Index = index;
//         Act_Index = Hash(HT2[index].Cname);
//         do
//         {
//             index = ((index + 1) % Tablesize);
//         } while (HT2[index].telephone != 0);
//         New_Index = index;
//         if (Act_Index == Cur_Index)
//         {
//             strcpy(HT2[New_Index].Cname, name);
//             HT2[New_Index].telephone = tele;
//         }
//         else
//         {
//             strcpy(HT2[New_Index].Cname, HT2[Cur_Index].Cname);
//             HT2[New_Index].telephone = HT2[Cur_Index].telephone;
//             strcpy(HT2[Cur_Index].Cname, name);
//             HT2[Cur_Index].telephone = tele;
//         }
//     }
    
// }
// void HashTable ::search_HT1()
// {
//     int i, cnt, comp, cmp, index, Tablesize = 10;
//     char name[20];
//     comp = 0;
//     cout << "\n How many records u wanna search..?:";
//     cin >> cnt;
//     for (i = 0; i < cnt; i++)
//     {
//         cmp = 0;
//         cout << "\n\t Enter Client Name: ";
//         cin >> name;
//         index = Hash(name);
        
//         if (strcmp(HT1[index].Cname, name) == 0)
//         {
//             cmp++;
//             cout << "\n Client's Telephone No:" << HT1[index].telephone;
//         }
//         else

//         {
//             cmp++;
//             do
//             {
//                 index = ((index + 1) % Tablesize);
//                 cmp++;
//             } while (strcmp(HT1[index].Cname, name) != 0);
//             cout << "\n Client'sTelephone No:" << HT1[index].telephone;
//         }
        
//         cout << "\n Needed Comparisons:" << cmp;
//         comp = comp + cmp;
//     }
//     cout << "\n Total Needed Comparisons: " << comp;
// }
// void HashTable ::search_HT2()
// {
//     int i, cnt, comp, cmp, index, Tablesize = 10;
//     char name[20];
//     comp = 0;
//     cout << "\n How many records u wanna search..?: ";
//     cin >> cnt;
//     for (i = 0; i < cnt; i++)
//     {
//         cmp = 0;
//         cout << "\n\t Enter Client Name:";
//         cin >> name;
//         index = Hash(name);
//         if (strcmp(HT2[index].Cname, name) == 0)
//         {
//             cmp++;
//             cout << "\n Client's Telephone No: " << HT2[index].telephone;
//         }
//         else
//         {
//             cmp++;
//             do
//             {
//                 index = ((index + 1) % Tablesize);
//                 cmp++;
//             } while (strcmp(HT2[index].Cname, name) != 0);
//             cout << "\n Client's Telephone No:" << HT2[index].telephone;
//         }
//         cout << "\n Needed Comparisons:" << cmp;
//         comp = comp + cmp;
//     }
//     cout << "\n Total Needed Comparisons: " << comp;
// }

// int main()

// {
//     cout << "\n -----****DSA Lab PR-04 Hash Table****-----";
//     HashTable HT;
//     cout << "\n A] Creating Hash Table.........";
//     HT.create_HT();
//     cout << "\n B] Display Hash Table.........";
//     HT.show_HT();
//     cout << "\n C] Insert (Cname-telephone) in Hash Table-01.........";
//     HT.insert_HT1();
//     cout << "\n D] Insert (Cname-telephone) in Hash Table-02.........";
//     //HT.insert_HT2();
//     cout << "\n E] Display Hash Table.........";
//     HT.show_HT();
//     cout << "\n F] Search in Hash Table-01.........";
//     HT.search_HT1();
//     cout << "\n G] Search in Hash Table-02.........";
//     HT.search_HT2();
//     return 0;
// }

