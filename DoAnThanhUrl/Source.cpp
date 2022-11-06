#include<iostream>
#include<stdio.h>
#include<windows.h>
#include<string>
#include<time.h>
#define MAX 100

using namespace std;

//  ======= Cai dat stack
struct Node {
	string data;
	Node* next;
};
typedef struct Node* stack;
Node* createNodeStack(string data) {
    Node* p = new Node();
    if (p == NULL) {
        return NULL;
    }
    p->data = data;
    p->next = NULL;

    return p;
}
bool isEmpty(stack s) {
    return (s == NULL);
}
void push(stack& s, string data) {
    Node* ptr = createNodeStack(data);
    if (isEmpty(s)) {
        s = ptr;
    }
    else {
        ptr->next = s;
        s = ptr;
    }
}
string pop(stack& s) {
    if (!isEmpty(s)) {
        string data = s->data;
        Node* x = s;
        s = s->next;
        delete(x);
        return data;
    }
    else {
        return;
    }
}
string top(stack s) {
    if (!isEmpty(s)) {
        return s->data;
    }
    else {
        return;
    }
}

// ======= Cai dat double link list
struct NodeUrl {
	string data;
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
    NodeUrl* newNode = new NodeUrl();
    if (l->head == NULL) {
        l->head = newNode;
        l->tail = newNode;
        return;
    }
    l->tail->next = newNode;
    newNode->prev = l->tail;
    l->tail = newNode;
}
// Lam them insert vao giua 
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

// ======= Cai dat mang luu lich su 
string History[MAX];

int main() {
    

    return 0;
}