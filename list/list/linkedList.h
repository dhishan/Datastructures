//
//  linkedList.h
//  list
//
//  Created by Dhishan  A on 7/6/15.
//  Copyright (c) 2015 Dhishan  A. All rights reserved.
//

#ifndef __list__linkedList__
#define __list__linkedList__

#include <stdio.h>
#include <iostream>
#include <string>
#include <cassert>
#include <sstream>
#include "math.h"

template<class Item>
struct Node{
    Item data;
    Node<Item>* link;
};

template<class Item> class linkedList{
public:
    linkedList();
    linkedList(const linkedList<Item> &source);
    ~linkedList();
    void insert_head(const Item &);
    void insert(const Item &);
    void insertAt(const Item &,int);
    void erase(int index);
    void clear();
    int count() const;
    Item elementAt(int index) const;
    Node<Item> * searchNode(const Item &) const;
    void operator=(const linkedList & operand);
    void operator+=(const linkedList & operand);
    friend void printreverse(Node<Item> * pointer);
    friend int main(int argc, const char * argv[]);
private:
    Node<Item>* head;
    Node<Item>* tail;
    void remove(Node<Item> * previousNode);
};

#endif /* defined(__list__linkedList__) */
