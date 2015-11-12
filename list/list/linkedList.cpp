//
//  linkedList.cpp
//  list
//
//  Created by Dhishan  A on 7/6/15.
//  Copyright (c) 2015 Dhishan  A. All rights reserved.
//

#include "linkedList.h"
template<class Item>
linkedList<Item>::linkedList(){
    head = NULL;
    tail = NULL;
}

template<class Item>
linkedList<Item>::linkedList(const linkedList &source){
    for (int i = 0; i< source.count(); i++) {
        insert(source.elementAt(i));
    }
}

template<class Item>
linkedList<Item>::~linkedList(){
    clear();
}

template<class Item>
void linkedList<Item>::insert_head(const Item &newItem){
    Node<Item> * newNode = new Node<Item>;
    newNode->data = newItem;
    newNode->link = head;
    head = newNode;
    if (tail == NULL) {
        tail = head;
    }
    
}

template<class Item>
void linkedList<Item>::insert(const Item &newItem){
    Node<Item> * newNode = new Node<Item>;
    newNode->data = newItem;
    newNode->link = NULL;
    if (tail)
        tail->link = newNode;
    tail = newNode;
    if(head == NULL){
        head = newNode;
    }
}

template<class Item>
void linkedList<Item>::insertAt(const Item & newItem,int location){
    assert(location>=0 && location<=count());
    if(location == 0){
        insert_head(newItem);
        return;
    }
    int i=1;
    Node<Item> * previousNode = head;
    do {
        if(i==location){
            Node<Item> * newNode = new Node<Item>;
            newNode->data = newItem;
            newNode->link = previousNode->link;
            previousNode->link = newNode;
        }
        i++;
        previousNode = previousNode->link;
    } while (previousNode);
}

template<class Item>
void linkedList<Item>::remove(Node<Item> * previousNode){
    assert(previousNode != NULL);
    if(previousNode->link == tail)
        tail = previousNode;
    Node<Item> * temp = previousNode->link->link;
    delete previousNode->link;
    previousNode->link = temp;
}

template<class Item>
void linkedList<Item>::erase(int index){
    assert(index>=0 && index<count());
    Node<Item> * current = head;
    if(index == 0){
        if(tail == head)
            tail = NULL;
        head = head->link;
        delete current;
        return;
    }//remove head
    int i= 0;
    while (current) {
        if (i == index-1) {
            remove(current);
        }
        i++;
        current = current->link;
    }
}

template<class Item>
Item linkedList<Item>::elementAt(int index) const{
    assert(index>=0 && index<count());
    Node<Item> * current = head;
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

template<class Item>
Node<Item> * linkedList<Item>::searchNode(const Item &item) const{
    Node<Item> * current = head;
    while (current) {
        if (item == current->data) {
            return current;
        }
        current = current->link;
    }
    return current;
}

template<class Item>
void linkedList<Item>::clear(){
    if (head == NULL) {
        return;
    }
    Node<Item> * current = head;
    while (current->link != NULL) {
        Node<Item> * temp = current;
        current = current->link;
        delete temp;
    }
    delete current;
    head = NULL;
    tail = NULL;
}

template<class Item>
int linkedList<Item>::count() const{
    int count = 0;
    for (Node<Item> * current = head; current != NULL; current = current->link) {
        count++;
    }
    return count;
}

template<class Item>
void linkedList<Item>::operator=(const linkedList &operand){
    clear();
    for (int i = 0; i< operand.count(); i++) {
        insert(operand.elementAt(i));
    }
}

template<class Item>
void linkedList<Item>::operator+=(const linkedList &operand){
    for (int i= 0; i< operand.count(); i++) {
        insert(operand.elementAt(i));
    }
}

template<class Item>
const linkedList<Item> operator+(const linkedList<Item> & operand1,const linkedList<Item> & operand2)  {
    linkedList<Item> list = linkedList<Item>(operand1);
    list += operand2;
    return list;
}
