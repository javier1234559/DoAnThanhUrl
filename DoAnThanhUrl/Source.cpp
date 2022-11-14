#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <string>
#include <time.h>
#define MAX_SIZE 100

using namespace std;

//Khai bao Doublelink list
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
NodeUrl* GetNewNode(string x);
void InsertAtTail(HistoryList* l, string x);
void DeleteAtHead(HistoryList* l);
void DeleteAtTail(HistoryList* l);
void PrintUrl(HistoryList l);
string previousUrl(HistoryList& l);
string forwardUrl(HistoryList& l);
string currentUrl(HistoryList& l);
// Khai bao Linked list
struct Node {
    int count;
    string x;
    Node* next;
};
struct List {
    Node* head =NULL;
    Node* tail =NULL;
};
Node* createNode(string val,int count);
void addLastNode(List* l, Node* p);
void xoaNode(List& l, Node* node);
void PrintLinkedList(List l);

//Khai bao Menu
void gotoxy(int x, int y);
int selection(int start, int end, int y);
void pageBookMark(List* bm);
void pageHistory(List* l);
void menuMain();
void menupageNhap();
void menuBookMark();
void menuBigHistory();
void pageNhap(HistoryList* l);
void addBookMark(HistoryList* l);
// Khai bao cac danh sach
List BigHistory;
List BookMark;
HistoryList l;
void addBookMark(List* bm, string s);
void deleteBookMark(List* bm, int s);
void addBigHistory(List* bighistory, string s, int count);
void deleteHistory(List* bighistory, int count);
int findMaxIndex(List* list);
int main() {
    
    string str[4] = { "google.com","facebook.com","youtube.com", "zalo.com"};
   
    for (int i = 0; i < 4; i++) {
        InsertAtTail(&l, str[i]);
        addBookMark(&BookMark, str[i]);
        addBigHistory(&BigHistory, str[i],i);
    }
    menuMain();
    
   
    //chua fix bug xoa Bookmark va History nhung ko cap nhat lai count
    //them bookmark moi va them id cho no
}

//Cai dat Doublelink list
NodeUrl* GetNewNode(string x) {
    NodeUrl* newNode = new NodeUrl();
    newNode->data = x;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}
void InsertAtTail(HistoryList* l, string x) {
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
    gotoxy(0, 0);
    cout << "Url: ";
    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->prev;
    }
    
    cout << endl;
}
string previousUrl(HistoryList& l) {
    NodeUrl* newNode = new NodeUrl;
    newNode = l.tail;
    while (newNode->check == true) {
        newNode = newNode->prev;
    }
    if (newNode->prev == NULL) {
        return "";
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
    if (newNode->next == NULL) {
        return "";
    }
    newNode = newNode->next;
    newNode->check = false;
    string data = newNode->data;

    return data;
}
string newAndResetUrl(HistoryList* l, string u) {
    NodeUrl* newAndResetUrl = GetNewNode(u);
    NodeUrl* newNode = new NodeUrl();
    newNode = l->tail;
    while (newNode->check == true) {
        newNode = newNode->prev;
        DeleteAtTail(l);
    }
    cout << newNode->data << endl;
    newNode->next = newAndResetUrl;
    newAndResetUrl->prev = newNode;
    l->tail = newAndResetUrl;
    return u;
}
string currentUrl(HistoryList* l) {
    NodeUrl* newNode = new NodeUrl;
    newNode = l->tail;
    while (newNode->check == true) {
        newNode = newNode->prev;
    }
    if (newNode->prev == NULL) {
        return "";
    }
    string data = newNode->data;
    return data;
}
// Cai dat Linked list

Node* createNode(string val,int count) {
    Node* node = new Node;
    node->x = val;
    node->count = count;
    node->next = NULL;
    return node;
}
void addLastNode(List* l, Node*p) {
    if (l->head == NULL) {
        l->head = p;
        l->tail = p;
    }
    else {
        l->tail->next = p;
        l->tail = p;
    }
}
void xoaNode(List* list, int count) {
    Node* pdel = list->head; 
    if (pdel == NULL) {
        return;
    }
    else {
        Node* pre = NULL;
        while (pdel != NULL) {
            if (pdel->count == count) {
                break;
            }
            pre = pdel;
            pdel = pdel->next;
        }
        if (pdel == NULL) {
            return;
        }
        else {
            if (pdel == list->head) {
                list->head = list->head->next;
                pdel->next = NULL;
                delete pdel;
                pdel = NULL;
            }
            else if (pdel->next == NULL) {
                list->tail = pre;
                pre->next = NULL;
                delete pdel;
                pdel = NULL;
            }
            else {
                pre->next = pdel->next;
                pdel->next = NULL;
                delete pdel;
                pdel = NULL;
            }
        }
    }
}
void PrintLinkedList(List l) {
    for (Node* i = l.head; i != NULL; i = i->next) {
        cout << i->count<<"." << i->x << " ";
       
    }
}

//Cai dat Menu
void gotoxy(int x, int y) {
    static HANDLE  h = NULL;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x,y };
    SetConsoleCursorPosition(h, c);
}
int  selection(int start, int end, int y)
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
void pageBookMark(List* bm)
{
    gotoxy(0, 4);
    int u;
    cout << "Nhap so thu tu URL muon xoa: ";
    cin >> u;
    deleteBookMark(bm, u);
}
void pageHistory(List* l)
{
    gotoxy(0, 4);
    int u;
    cout << "Nhap so thu tu URL muon xoa: ";
    cin >> u;
    deleteHistory(l, u);
}
void menuMain() {
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
        cout << "2. BookMark";
        gotoxy(x, y++);
        cout << "3. History";
        gotoxy(x, y++);
        cout << "4. Exit";

        imenu = selection(1, 4, 2);

        switch (imenu)
        {
        case 1:
            menupageNhap();
            pageNhap(&l);
            break;
        case 2:
            menuBookMark();
            break;
        case 3:
            menuBigHistory();
            break;
        case 4:
            cout << "\nKet thuc chuong trinh ! ";
            exit(0);
            break;
        }
    }
}
void menupageNhap() {
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
        cout << "1. Nhap URL";
        gotoxy(x, y++);
        cout << "2. Forward";
        gotoxy(x, y++);
        cout << "3. Previous";
        gotoxy(x, y++);
        cout << "4. Them BookMark";
        gotoxy(x, y++);
        cout << "5. Back to home menu";
        imenu = selection(1, 5, 2);
        switch (imenu)
        {
        case 1:
            pageNhap(&l);
            break;
        case 2:
            forwardUrl(l);
            break;
        case 3:
            previousUrl(l);
            break;
        case 4:
            addBookMark(&l);
            break;
        case 5:
            menuMain();
            break;
        }
    }

}
void menuBookMark() {
    int imenu = 1;
    while (true)
    {
        int x = 2, y = 0;
        system("CLS");
        gotoxy(0, 0);
        cout << "BookMark: ";
        PrintLinkedList(BookMark);
        gotoxy(x, y++);
        gotoxy(x, y++);
        cout << "------MENU------- \n\n";
        gotoxy(x, y++);
        cout << "1. Xoa bookmark";
        gotoxy(x, y++);
        cout << "2. Back to home menu";
        imenu = selection(1, 2, 2);

        switch (imenu)
        {
        case 1:
            pageBookMark(&BookMark);
            break;
        case 2:
            menuMain();
            break;
        }
    }
}
void menuBigHistory() {
    int imenu = 1;
    while (true)
    {
        int x = 2, y = 0;
        system("CLS");
        gotoxy(0, 0);
        cout << "BigHistory: ";
        PrintLinkedList(BigHistory);
        gotoxy(x, y++);
        gotoxy(x, y++);
        cout << "------MENU------- \n\n";
        gotoxy(x, y++);
        cout << "1. Xoa history";
        gotoxy(x, y++);
        cout << "2. Back to home menu";
        imenu = selection(1, 2, 2);

        switch (imenu)
        {
        case 1:
            pageHistory(&BigHistory);
            break;
        case 2:
            menuMain();
            break;
        }
    }
}
void pageNhap(HistoryList*l)
{
    gotoxy(0, 7);
    string u;
    cout << "Nhap URL: ";
    cin >> u;
    int count = findMaxIndex(&BigHistory) + 1;
    addBigHistory(&BigHistory, u, count);
    if (l->tail->check == true) {
        newAndResetUrl(l,u);
        return;
    }
    InsertAtTail(l, u);
}
void addBookMark(HistoryList* l) {
    string current = currentUrl(l);
    addBookMark(&BookMark, current);
    gotoxy(0, 8);
    cout << "Them bookmark thanh cong !";
    _getch();
}
// Cai dat cac danh sach
void addBookMark(List* bm, string s) {
    int count = findMaxIndex(bm) + 1;
    Node* p = createNode(s,count);
    addLastNode(bm, p);
}
void deleteBookMark(List* bm,int count) {
    xoaNode(bm, count);
}
void addBigHistory(List* bighistory, string s, int count) {
    Node* p = createNode(s, count);
    addLastNode(bighistory, p);
}
void deleteHistory(List* bighistory, int count) {
    xoaNode(bighistory, count);
}
int findMaxIndex(List* list) {
    Node* temp = list->head;
    int max;
    if (temp == NULL) {
        max = 0;
        return max;
    }
    max = list->head->count;
    for (Node* i = list->head; i != NULL; i = i->next) {
        if (max < i->count)
            max = i->count;
    }

    return max;
}