#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <time.h>
#define SIZE 7

using namespace std;

//Khai bao Doublelink list
struct NodeUrl {
	string data;
	bool check = false;
	NodeUrl* prev, * next = NULL;
};
struct DoubleLinkList
{
	NodeUrl* head = NULL;
	NodeUrl* tail = NULL;
};
NodeUrl* createNodeUrl(string x);
void insertAtTail(DoubleLinkList* l, string x);
void deleteAtTail(DoubleLinkList* l);
void printUrl(DoubleLinkList l);
string previousUrl(DoubleLinkList* l);
string forwardUrl(DoubleLinkList* l);
string currentUrl(DoubleLinkList* l);


//Khai bao Linked list
struct Node {
	int count;
	string x;
	Node* next;
};
struct LinkedList {
	Node* head = NULL;
	Node* tail = NULL;
};
Node* createNode(string val, int count);
void addLastNode(LinkedList* l, Node* p);
void xoaNode(LinkedList* l, Node* node);
void printLinkedList(LinkedList l);

//Khai bao HashTable
void initHashTable(DoubleLinkList* Tabs[]);
void addToHashTable(DoubleLinkList* Tabs[], string x);
int hashFunc(string x);
void displayAllTabs(DoubleLinkList* Tabs[]);
DoubleLinkList* SearchHashTable(DoubleLinkList* Tabs[], string x);

//Khai bao Menu
void gotoxy(int x, int y);
int  selection(int start, int end, int y);
void menuMain(DoubleLinkList* l);
void menuInputNewUrl(DoubleLinkList* l);
void menuBookMark(DoubleLinkList* l);
void menuBigHistory(DoubleLinkList* l);
void menuNewTab(); //Tabs khai bao toan cuc

//Ham di chuyen de Nhap
void InputNewUrl(DoubleLinkList* l);
void InputBookMarkToDel(LinkedList* bm);
void InputHistoryToDel(LinkedList* l);
void InputNewTab(DoubleLinkList* Tabs[]);
void InputTabToAccess(DoubleLinkList* Tabs[]);

//Ham thao tac 
void GetCurrentAndAddBookMark(DoubleLinkList* l);
void deleteBookMark(LinkedList* bm, int s);
void addBookMark(LinkedList* bm, string s);
void addBigHistory(LinkedList* bighistory, string s, int count);
void deleteHistory(LinkedList* bighistory, int count);
void accessLink(string str);
int findLastIndex(LinkedList* list);


//Khai bao cac danh sach
LinkedList BigHistory;  //vi 2 danh sach dung chung nen khai bao toan cuc
LinkedList BookMark;
DoubleLinkList* Tabs[SIZE];

int main() {

	initHashTable(Tabs);

	//Khoi tao san Tab1
	addToHashTable(Tabs, "Tab1");
	DoubleLinkList* l = SearchHashTable(Tabs, "Tab1");
	menuMain(l);


	return 0;

}

//Cai dat Doublelink list
NodeUrl* createNodeUrl(string x) {
	NodeUrl* newNode = new NodeUrl();
	newNode->data = x;
	newNode->prev = NULL;
	newNode->next = NULL;
	return newNode;
}
void insertAtTail(DoubleLinkList* l, string x) {
	NodeUrl* newNode = createNodeUrl(x);
	if (l->head == NULL) {
		l->head = newNode;
		l->tail = newNode;
		return;
	}
	l->tail->next = newNode;
	newNode->prev = l->tail;
	l->tail = newNode;
}
void deleteAtTail(DoubleLinkList* l) {
	if (l->head == NULL) {
		return;
	}
	l->tail = l->tail->prev;
	l->tail->next = NULL;
}
void printUrl(DoubleLinkList l) {
	NodeUrl* temp = l.tail;
	while (temp->check == true) {
		temp = temp->prev;
	}
	gotoxy(0, 0);
	cout << "Url: ";
	while (temp != NULL) {
		cout << temp->data << " ";
		temp = temp->prev;
		break;
	}

	cout << endl;
}
string previousUrl(DoubleLinkList* l) {
	NodeUrl* newNode = new NodeUrl;
	newNode = l->tail;
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
string forwardUrl(DoubleLinkList* l) {
	NodeUrl* newNode = new NodeUrl;
	newNode = l->tail;

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
string newAndResetUrl(DoubleLinkList* l, string u) {
	NodeUrl* newAndResetUrl = createNodeUrl(u);
	NodeUrl* newNode = new NodeUrl();
	newNode = l->tail;
	while (newNode->check == true) {
		newNode = newNode->prev;
		deleteAtTail(l);
	}
	cout << newNode->data << endl;
	newNode->next = newAndResetUrl;
	newAndResetUrl->prev = newNode;
	l->tail = newAndResetUrl;
	return u;
}
string currentUrl(DoubleLinkList* l) {
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
Node* createNode(string val, int count) {
	Node* node = new Node;
	node->x = val;
	node->count = count;
	node->next = NULL;
	return node;
}
void addLastNode(LinkedList* l, Node* p) {
	if (l->head == NULL) {
		l->head = p;
		l->tail = p;
	}
	else {
		l->tail->next = p;
		l->tail = p;
	}
}
void xoaNode(LinkedList* list, int count) {
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
void printLinkedList(LinkedList l) {
	for (Node* i = l.head; i != NULL; i = i->next) {
		cout << i->count << "." << i->x << " ";

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
void menuMain(DoubleLinkList* l) {
	int imenu = 1;
	while (true) {
		int x = 2, y = 0;
		system("CLS");
		gotoxy(x, y++);
		printUrl(*l);
		gotoxy(x, y++);
		cout << "------MENU------- \n\n";
		gotoxy(x, y++);
		cout << "1. NHAP URL";
		gotoxy(x, y++);
		cout << "2. BOOKMARK";
		gotoxy(x, y++);
		cout << "3. HISTORY";
		gotoxy(x, y++);
		cout << "4. MENU NEW TAB";
		gotoxy(x, y++);
		cout << "5. EXIT";
		imenu = selection(1, 5, 2);
		switch (imenu)
		{
		case 1:
			menuInputNewUrl(l);
			InputNewUrl(l);
			break;
		case 2:
			menuBookMark(l);
			break;
		case 3:
			menuBigHistory(l);
			break;
		case 4:
			menuNewTab();
			break;
		case 5:
			cout << "\nKet thuc chuong trinh ! ";
			exit(0);
			break;
		}
	}
}
void menuInputNewUrl(DoubleLinkList* l) {
	int imenu = 1;
	while (true)
	{
		int x = 2, y = 0;
		system("CLS");
		gotoxy(x, y++);
		printUrl(*l);
		gotoxy(x, y++);
		cout << "------MENU------- \n\n";
		gotoxy(x, y++);
		cout << "1. NHAP URL";
		gotoxy(x, y++);
		cout << "2. FORWARD";
		gotoxy(x, y++);
		cout << "3. PREVIOUS";
		gotoxy(x, y++);
		cout << "4. THEM BOOKMARK";
		gotoxy(x, y++);
		cout << "5. BACK TO MENU";
		gotoxy(x, y++);
		cout << "6. TRUY CAP";
		imenu = selection(1, 6, 2);
		switch (imenu)
		{
		case 1:
			InputNewUrl(l);
			break;
		case 2:
			forwardUrl(l);
			break;
		case 3:
			previousUrl(l);
			break;
		case 4:
			GetCurrentAndAddBookMark(l);
			break;
		case 5:
			menuMain(l);
			break;
		case 6:
			string link = currentUrl(l);
			accessLink(link);
			break;

		}

	}

}
void menuBookMark(DoubleLinkList* l) {
	int imenu = 1;
	while (true)
	{
		int x = 2, y = 0;
		system("CLS");
		gotoxy(0, 0);
		cout << "BookMark: ";
		printLinkedList(BookMark);
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
			InputBookMarkToDel(&BookMark);
			break;
		case 2:
			menuMain(l);
			break;
		}
	}
}
void menuBigHistory(DoubleLinkList* l) {
	int imenu = 1;
	while (true)
	{
		int x = 2, y = 0;
		system("CLS");
		gotoxy(0, 0);
		cout << "BigHistory: ";
		printLinkedList(BigHistory);
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
			InputHistoryToDel(&BigHistory);
			break;
		case 2:
			menuMain(l);
			break;
		}
	}
}
void menuNewTab() { //Tabs da khai bao toan cuc
	int imenu = 1;
	while (true)
	{
		int x = 2, y = 0;
		system("CLS");
		gotoxy(0, 0);
		cout << "Danh sach cac Tab: ";
		displayAllTabs(Tabs);
		gotoxy(x, y++);
		gotoxy(x, y++);
		cout << "------MENU------- \n\n";
		gotoxy(x, y++);
		cout << "1.Nhap key New Tab";
		gotoxy(x, y++);
		cout << "2.Truy Cap Tab";
		imenu = selection(1, 2, 2);

		switch (imenu)
		{
		case 1:
			InputNewTab(Tabs);
			break;
		case 2:
			InputTabToAccess(Tabs);
			break;
		}
	}
}

//Ham di chuyen de Nhap
void InputNewUrl(DoubleLinkList* l)
{
	gotoxy(0, 9);
	string u;
	cout << "Nhap URL: ";
	cin >> u;
	int count = findLastIndex(&BigHistory) + 1;
	addBigHistory(&BigHistory, u, count);
	if (l->tail->check == true) {
		newAndResetUrl(l, u);
		return;
	}
	insertAtTail(l, u);
}
void InputBookMarkToDel(LinkedList* bm)
{
	gotoxy(0, 4);
	int u;
	cout << "Nhap so thu tu URL muon xoa: ";
	cin >> u;
	deleteBookMark(bm, u);
}
void InputHistoryToDel(LinkedList* l)
{
	gotoxy(0, 4);
	int u;
	cout << "Nhap so thu tu URL muon xoa: ";
	cin >> u;
	deleteHistory(l, u);
}
void InputNewTab(DoubleLinkList* Tabs[]) {
	gotoxy(0, 4);
	string key;
	cout << "Nhap ten Tab khong duoc trung : ";
	cin >> key;
	addToHashTable(Tabs, key);

	//Di chuyen den Tab vua nhap 
	DoubleLinkList* l = SearchHashTable(Tabs, key);
	menuMain(l);
}
void InputTabToAccess(DoubleLinkList* Tabs[]) {
	gotoxy(0, 4);
	string key;
	cout << "Nhap Ten Tab De Truy Cap : ";
	cin >> key;
	DoubleLinkList* l = SearchHashTable(Tabs, key);
	if (l != NULL && l->head != NULL)
		menuMain(l);
	else {
		cout << "\nTen Tab Khong Ton Tai !";
		_getch(); //pause 
	}
}

//Ham thao tac
void GetCurrentAndAddBookMark(DoubleLinkList* l) {
	string current = currentUrl(l);
	addBookMark(&BookMark, current);
	gotoxy(0, 8);
	cout << "Them bookmark thanh cong !";
	_getch();
}
void addBookMark(LinkedList* bm, string s) {
	int count = findLastIndex(bm) + 1;
	Node* p = createNode(s, count);
	addLastNode(bm, p);
}
void deleteBookMark(LinkedList* bm, int count) {
	xoaNode(bm, count);
}
void addBigHistory(LinkedList* bighistory, string s, int count) {
	Node* p = createNode(s, count);
	addLastNode(bighistory, p);
}
void deleteHistory(LinkedList* bighistory, int count) {
	xoaNode(bighistory, count);
}
void accessLink(string str) {
	str = "https://" + str;  //them giao thuc 
	system(std::string("start " + str).c_str());
	system("pause>>null");
}
int findLastIndex(LinkedList* list) { //ham tim gia tri chi muc lon nhat de them id cho danh sach lk
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


//Khai bao Hashtable
void initHashTable(DoubleLinkList* Tabs[])
{
	for (int i = 0; i < SIZE; i++) {
		DoubleLinkList* temp = new DoubleLinkList();
		temp->head = NULL;
		temp->tail = NULL;
		Tabs[i] = temp;
	}
}
int hashFunc(string x) {
	int sum = 0;
	for (int i = 0; i < x.length(); i++)
		sum = sum + int(x[i]);

	return  sum % SIZE;
}
void addToHashTable(DoubleLinkList* Tabs[], string x) {
	int h = hashFunc(x);
	DoubleLinkList* Tab = Tabs[h];
	insertAtTail(Tab, x);

}
void displayAllTabs(DoubleLinkList* Tabs[]) {
	for (int i = 0; i < SIZE; i++) {
		if (Tabs[i]->head != NULL) {
			NodeUrl* p = Tabs[i]->head;
			cout << p->data << " ";
		}
	}
}
DoubleLinkList* SearchHashTable(DoubleLinkList* Tabs[], string x) {
	int h = hashFunc(x);
	DoubleLinkList* Tab = Tabs[h];

	while (Tab->head != NULL && Tab->head->data != x) {
		Tab->head = Tab->head->next;
	}

	return Tab;
}
