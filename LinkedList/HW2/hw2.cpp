//  Assignment 2
//  hw2.cpp
//  HW2 - Linked List
//
//  Dhishan Amaranath
//  N16909360
//

#include <iostream>
#include <string>
#include <cassert>
#include <sstream>
#include "math.h"

using namespace std;

struct Node{
    typedef int Item;
    Item data;
    Node* link;
};

class linkedList{
public:
    linkedList();
    linkedList(const linkedList &source);
    ~linkedList();
    void insert_head(const Node::Item &);
    void insert(const Node::Item &);
    void insertAt(const Node::Item &,int);
    void remove(Node * previousNode);
    void clear();
    int count() const;
    Node::Item elementAt(int index) const;
    Node * searchNode(const Node::Item &) const;
    void operator=(const linkedList & operand);
    void operator+=(const linkedList & operand);
    void reverseList();
private:
    Node* head;
    Node* tail;
    Node* iterator;
};

const linkedList operator+(const linkedList & operand1,const linkedList & operand2);

void readList(linkedList &);

void printList(linkedList &);
void insertSorted(int ,linkedList &list);
float getMedian(linkedList &list);
void reverselist(linkedList &list);

int main(int argc, const char * argv[]) {
    
    char option;
    cout << "Please tell me what to do: concatenate(C), insert(I), median(M), reverse(R), end(E)?" << endl;
    cin >> option;
    cin.ignore();
    option = tolower(option);
    linkedList list1 = linkedList();
    linkedList list2 = linkedList();
    linkedList list3 = linkedList();
    while (option != 'e') {
        switch (option) {
        case 'c':
            cout << "Please input list 1" << endl;
            readList(list1);
            cout << "Please input list 2" << endl;
            readList(list2);
            cout << "Concatinated List is" << endl;
            list3 = list1 + list2;
            printList(list3);
            break;
        case 'i':
            cout << "Please input list" << endl;
            readList(list1);
            cout << "Enter Element to Insert" << endl;
            int val;
            cin.clear();
            cin >> val;
            insertSorted(val,list1);
            cout << "New List is" << endl;
            printList(list1);
            cin.ignore();
            break;
        case 'm':
            cout << "Please input list" << endl;
            readList(list2);
            cout << "Median is " << getMedian(list2) << endl;
            break;
        case 'r':
            cout << "Please input list" << endl;
            readList(list3);
            reverselist(list3);
            cout << "New List is" << endl;
            printList(list3);
            break;
        default:
                cout << "Please input proper choice" << endl;
            break;
        }
        list1.clear();
        list2.clear();
        list3.clear();
        cout << "Please tell me what to do: concatenate(C), insert(I), median(M), reverse(R), end(E)?" << endl;
        cin >> option;
        cin.ignore();
        option = tolower(option);
    }
    return 0;
}

void readList(linkedList &list){
    string input;
    getline(cin, input);
    istringstream iss(input);
    int val;
    while (iss >> val) {
        list.insert(val);
    }
}

void printList(linkedList &list){
    for (int i=0; i < list.count(); i++) {
        cout << list.elementAt(i) << " ";
    }
    cout << endl;
}

void insertSorted(int val, linkedList &list){
    for (int i=0; i < list.count(); i++) {
        if(list.elementAt(i) >= val){
            list.insertAt(val, i);
            break;
        }
    }
}

float getMedian(linkedList &list){
    assert(list.count() != 0);
    float median;
    if(list.count() % 2 == 0){
        median = list.elementAt(list.count()/2 - 1) + list.elementAt(list.count()/2);
        median /=2.0;
    }
    else {
        median = list.elementAt(ceil(list.count()/2));
    }
    return median;
}

void reverselist(linkedList &list){
    list.reverseList();
}

linkedList::linkedList(){
    head = NULL;
    tail = NULL;
}

linkedList::linkedList(const linkedList &source){
    for (int i = 0; i< source.count(); i++) {
        insert(source.elementAt(i));
    }
}

linkedList::~linkedList(){
    clear();
}


void linkedList::insert_head(const Node::Item &newItem){
    Node * newNode = new Node;
    newNode->data = newItem;
    newNode->link = head;
    head = newNode;
    if (tail == NULL) {
        tail = head;
        iterator = head;
    }
    
}

void linkedList::insert(const Node::Item &newItem){
    Node * newNode = new Node;
    newNode->data = newItem;
    newNode->link = NULL;
    if (tail)
        tail->link = newNode;
    tail = newNode;
    if(head == NULL){
        head = newNode;
        iterator = head;
    }
}

void linkedList::insertAt(const Node::Item & newItem,int location){
    assert(location>=0 && location<=count());
    if(location == 0){
        insert_head(newItem);
        return;
    }
    int i=1;
    Node * previousNode = head;
    do {
        if(i==location){
            Node * newNode = new Node;
            newNode->data = newItem;
            newNode->link = previousNode->link;
            previousNode->link = newNode;
        }
        i++;
        previousNode = previousNode->link;
    } while (previousNode);
}

void linkedList::remove(Node * node){
    assert(node != NULL);
    Node * temp = head;
    if (head == node) {
        head = node->link;
        if (iterator == head) {
            iterator = head->link;
        }
        if (tail == node) {
            tail = node->link;
        }
        delete node;
        return;
    }
    while (temp) {
        if (temp->link == node) {
            if ( node == tail) {
                tail = temp;
            }
            if (iterator == node) {
                iterator = temp;
            }
            temp->link = node->link;
            delete node;
            return;
        }
        temp = temp->link;
    }
}

Node::Item linkedList::elementAt(int index) const{
    assert(index>=0 && index<count());
    Node * current = head;
    int i= 0;
    while (current) {
        if (i == index) {
            return current->data;
        }
        i++;
        current = current->link;
    }
    return NULL;
}

Node * linkedList::searchNode(const Node::Item &item) const{
    Node * current = head;
    while (current) {
        if (item == current->data) {
            return current;
        }
        current = current->link;
    }
    return current;
}

void linkedList::clear(){
    if (head == NULL) {
        return;
    }
    Node * current = head;
    while (current->link != NULL) {
        Node * temp = current;
        current = current->link;
        delete temp;
    }
    delete current;
    head = NULL;
    tail = NULL;
    iterator = NULL;
}

int linkedList::count() const{
    int count = 0;
    for (Node * current = head; current != NULL; current = current->link) {
        count++;
    }
    return count;
}

void linkedList::operator=(const linkedList &operand){
    clear();
    for (int i = 0; i< operand.count(); i++) {
        insert(operand.elementAt(i));
    }
}

void linkedList::operator+=(const linkedList &operand){
    for (int i= 0; i< operand.count(); i++) {
        insert(operand.elementAt(i));
    }
}

const linkedList operator+(const linkedList & operand1,const linkedList & operand2)  {
    linkedList list = linkedList(operand1);
    list += operand2;
    return list;
}

void linkedList::reverseList(){
    if (count() > 1) {
        Node * nextLink = NULL;
        Node * current = head;
        Node * temp = NULL;
        do{
            temp = current->link;
            current->link = nextLink;
            nextLink = current;
            current = temp;
        }while (current != NULL);
        temp = head;
        head = tail;
        tail = temp;
    }
}
































