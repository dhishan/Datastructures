//
//  main.cpp
//  list
//
//  Created by Dhishan  A on 7/6/15.
//  Copyright (c) 2015 Dhishan  A. All rights reserved.
//

#include <iostream>
#include "linkedList.cpp"

using namespace std;

template<class Item>
void printreverse(Node<Item>* pointer);

int main(int argc, const char * argv[]) {
    linkedList<int> list;
    list.insert(1);
    list.insert(4);
    list.insert(5);
    printreverse(list.head);
    std::cout << "Hello, World!\n";
    return 0;
}

template<class Item>
void printreverse(Node<Item>* pointer){
    if (pointer == NULL) {
        return;
    }
    int data = pointer->data;
    printreverse(pointer->link);
    cout << data << endl;
}