#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <string>
#include <time.h>
#define MAX 100

using namespace std;

// ======= Cai dat double link list
struct NodeUrl {
	string data;
    bool check = false;
	NodeUrl* prev, * next = NULL;
};
struct HistoryList
{
    NodeUrl* head =NULL; 
    NodeUrl* tail = NULL; 
};
NodeUrl* GetNewNode(string x) {
    NodeUrl *newNode = new NodeUrl();
    newNode->data = x;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}
void InsertAtTail(HistoryList* l ,string x) {
    NodeUrl* newNode = GetNewNode(x);
    if (l->head == NULL) {
        l->head = newNode;
        l->tail = newNode;
        return;
    }
    l->tail->next = newNode;
    newNode->prev = l->tail;
    l->tail = newNode;
}
void DeleteAtHead(HistoryList* l) {
    if (l->head == NULL) {
        return;
    }
    l->head = l->head->next;
    l->head->prev = NULL;
}
void DeleteAtTail(HistoryList* l) {
    if (l->head == NULL) {
        return;
    }
    l->tail = l->tail->prev;
    l->tail->next = NULL;
}
void PrintUrl(HistoryList l) {
    NodeUrl* temp = l.tail;
    while (temp->check == true) {
        temp = temp->prev;
    }
    while (temp != NULL) {
        cout << temp->data <<" ";
        temp = temp->prev;
    }
    
}
string previousUrl(HistoryList &l) {
    NodeUrl* newNode = new NodeUrl;
    newNode = l.tail;
    while (newNode->check == true) {
        newNode = newNode->prev;
    }
    newNode->check = true;
    newNode = newNode->prev;

    string data = newNode->data;
    
    return data;
}
string forwardUrl(HistoryList& l) {
    NodeUrl* newNode = new NodeUrl;
    newNode = l.tail;
    while (newNode->check == true) {
        newNode = newNode->prev;
    }
    newNode = newNode->next;
    newNode->check = false;
    string data = newNode->data;

    return data;
}
// ======= Cai dat linked list
struct Node {
    string x;
    Node* next;
};
struct List {
    Node* head =NULL;
    Node* tail =NULL;
};
Node* createNode(string val) {
    Node* node = new Node;
    node->x = val;
    node->next = NULL;
    return node;
}
void addLastNode(List& l, Node* p) {
    if (l.head == NULL) {
        l.head = p;
        l.tail = p;
    }
    else {
        l.tail->next = p;
        l.tail = p;
    }
}
void xoaNode(List& l, Node* node) {
    if (l.head == NULL && l.tail == NULL) {
        return;
    }
    else if (l.head == l.tail) {
        l.head = NULL;
        l.tail = NULL;
    }
    else if (node->x == l.head->x) {
        Node* p = l.head;
        l.head = l.head->next;
        delete p;
    }
    else if (node->x == l.tail->x) {
        Node* p = l.tail;
        l.tail = l.tail->next;
        delete p;
    }
    else {
        Node* previous = l.head;
        Node* p = l.head;
        while (p != NULL) {

            if (p->next->x == node->x) {
                Node* temp = p->next;
                p->next = p->next->next;
                delete temp;
                continue;
            }

            p = p->next;
            if (p->next == NULL) {
                break;
            }
        }
    }
}
void PrintLinkedList(List l) {
    for (Node* i = l.head; i != NULL; i = i->next) {
        cout << i->x << " ";
    }
}

// ======= Cai dat mang luu lich su 
string BigHistory[MAX];
List BookMark ;
void addBookMark(List &bm,string s) {
    Node* p = createNode(s);
    addLastNode(bm, p);
}
void deleteBookMark(List& bm, string s) {
    Node* p = createNode(s);
    xoaNode(bm, p);
}



void gotoxy(int x, int y) {
    static HANDLE  h = NULL;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x,y };
    SetConsoleCursorPosition(h, c);
}

int selection(int start, int end, int y)
{
    int select = 1;
    int y0 = -1;
    gotoxy(0, select + y - 1);
    cout << char(16);

    while (1)
    {
        char key = _getch();

        if (key == 13)
        {
            gotoxy(0, y0);
            cout << char(32);
            break;
        }
        if (key == 80 || key == 77)
            select++;

        if (key == 72 || key == 75)
            select--;

        if (select > end)
            select = start;
        else if (select < start)
            select = end;

        gotoxy(0, y0);
        cout << char(32);
        gotoxy(0, select + y - 1);
        cout << char(16);


        y0 = select + y - 1;
    }
    return select;
}

void pageNhap(HistoryList l)
{
    string u;
    system("CLS");
    cout << "Nhap URL: ";
    cin >> u;
    InsertAtTail(&l, u);
}

void pageBookMark(List& bm)
{
    system("CLS");
    PrintLinkedList(bm);
    _getch();
}

void pageHistory(HistoryList& l)
{
    system("CLS");
    PrintUrl(l);
    _getch();
}

int main() {
    
    string str[4] = { "leetcode.com","facebook.com","youtube.com", "zalo.com"};
   
    HistoryList l;
    for (int i = 0; i < 4; i++) {
        InsertAtTail(&l, str[i]);
        addBookMark(BookMark, str[i]);
        BigHistory[i] = str[i];
    }
    /*PrintUrl(l);
    cout << endl;
    cout << endl;
    cout << previousUrl(l) << endl;
    cout << previousUrl(l)<<endl;
    PrintUrl(l);
    cout << endl;
    cout << forwardUrl(l) << endl;
    PrintUrl(l);*/


    int imenu = 1;
    while (true)
    {
        int x = 2, y = 0;
        system("CLS");
        gotoxy(x, y++);
        PrintUrl(l);
        gotoxy(x, y++);
        cout << "------MENU------- \n\n";
        gotoxy(x, y++);
        cout << "1. NhapURL";
        gotoxy(x, y++);
        cout << "2. Forward";
        gotoxy(x, y++);
        cout << "3. Previous";
        gotoxy(x, y++);
        cout << "4. BookMark";
        gotoxy(x, y++);
        cout << "5. History";
        gotoxy(x, y++);
        cout << "6. Exit";

        imenu = selection(1, 6, 2);

        switch (imenu)
        {
        case 1:
            pageNhap(l);
            break;
        case 2:
            cout << endl;
            forwardUrl(l);
            break;
        case 3:
            cout << endl;
            previousUrl(l);
            break;
        case 4:
            pageBookMark(BookMark);
            _getch();
            break;
        case 5:
            pageHistory(l);
            break;
        case 6:
            exit(0);
            break;
        }
         
    }
    

    /*PrintLinkedList(BookMark);
    deleteBookMark(BookMark, "zalo.com");
    cout << endl;
    PrintLinkedList(BookMark);*/

}



//  ======= Cai dat stack
//struct Node {
//	string data;
//	Node* next;
//};
//typedef struct Node* stack;
//Node* createNodeStack(string data) {
//    Node* p = new Node();
//    if (p == NULL) {
//        return NULL;
//    }
//    p->data = data;
//    p->next = NULL;
//
//    return p;
//}
//bool isEmpty(stack& s) {
//    return (s == NULL);
//}
//void push(stack& s, string data) {
//    Node* ptr = createNodeStack(data);
//    if (isEmpty(s)) {
//        s = ptr;
//    }
//    else {
//        ptr->next = s;
//        s = ptr;
//    }
//}
//string pop(stack& s) {
//    if (!isEmpty(s)) {
//        string data = s->data;
//        Node* x = s;
//        s = s->next;
//        delete(x);
//        return data;
//    }
//    else {
//        return 0;
//    }
//}
//string top(stack s) {
//    if (!isEmpty(s)) {
//        return s->data;
//    }
//    else {
//        return 0;
//    }
//}
//
//void PrintStack(stack& s) {
//    while (!isEmpty(s)) {
//        cout << pop(s);
//        cout << endl;
//    }
//}