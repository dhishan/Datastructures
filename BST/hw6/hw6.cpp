//  Assignment 6
//  hw6.cpp
//  HW6 - Binary Search Tree
//
//  Dhishan Amaranath
//  N16909360

#include <iostream>
#include <cassert>
#include <sstream>
#include "math.h"
#include <algorithm>

using namespace std;

template <class Item>      // Item may be any of the C++ built-in types
struct BinaryTreeNode
{
    Item data;
    BinaryTreeNode<Item>* left;
    BinaryTreeNode<Item>* right;
};

template <class Item>
class BinaryTree{
public:
    BinaryTree();
    BinaryTree(const BinaryTree<Item>&operand);
    ~BinaryTree();
    BinaryTreeNode<Item>* create_node(const Item& entry);
    bool is_leaf(const BinaryTreeNode<Item>& node);
    void tree_clear(BinaryTreeNode<Item>*& root_ptr);
    BinaryTreeNode<Item>* tree_copy(BinaryTreeNode<Item>* root_node);
    void insert (BinaryTreeNode<Item>*& root_ptr, const Item& entry);
    void search(BinaryTreeNode<Item>*  root_ptr,const Item& target,bool& found,BinaryTreeNode<Item>*& loc_ptr,int& nodeCnt);
    

public:
    BinaryTreeNode<Item>* root;

};

//////////////////////////// Linked List///////////////////////////////////////////////
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
    void searchRecursively(Node<Item>* root_node,int& cnt,bool&found,Item target);
    Node<Item> * searchNode(const Item &) const;
    void operator=(const linkedList & operand);
    void operator+=(const linkedList & operand);
    
    friend int main(int argc, const char * argv[]);
private:
    Node<Item>* head;
    Node<Item>* tail;
    void remove(Node<Item> * previousNode);
};
//////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, const char * argv[]) {
    BinaryTree<int> tree;
    linkedList<int> list;
    
    cout << "Please Enter list of Integers" << endl;
    string input;
    getline(cin, input);
    istringstream iss(input);
    string num;
    while (getline(iss,num,' ')) {
        tree.insert(tree.root, stoi(num));
        list.insert(stoi(num));
    }
    cout << "Please Enter an Integer to Search" << endl;
    string search_num;
    getline(cin, search_num);
    int num2Search = stoi(search_num);
     
    int cnt = 0;
    int cnt1 = 0;
    bool found = false;
    bool found1 = false;
    
    BinaryTreeNode<int>* found_node;
    tree.search(tree.root, num2Search, found, found_node, cnt);
    list.searchRecursively(list.head, cnt1, found1, num2Search);
    
    if (found) {
        cout << num2Search <<" Found, " << "BST visited " << cnt << "Nodes, Linked-List visited " << cnt1 << " nodes" << endl;
        
    }
    else cout << num2Search <<" Not Found" << endl;
    
    
    return 0;
}

template <class Item>
BinaryTree<Item>::BinaryTree(){
    root = NULL;
}

template<class Item>
BinaryTree<Item>::BinaryTree(const BinaryTree<Item>&operand){
    root = tree_copy(operand.root);
}

template <class Item>
BinaryTree<Item>::~BinaryTree(){
    tree_clear(root);
}

template <class Item>
bool BinaryTree<Item>::is_leaf(const BinaryTreeNode<Item>& node){
    return (node.left == NULL && node.right == NULL);
}


template<class Item>
void BinaryTree<Item>::tree_clear(BinaryTreeNode<Item>*& root_node){
    if (root == NULL) {
        return;
    }
    if (root_node->left != NULL) {
        tree_clear(root_node->left);
    }
    if (root_node->right != NULL) {
        tree_clear(root_node->right);
    }
    delete root_node;
    root_node = NULL;
    return;
}

template<class Item>
BinaryTreeNode<Item>* BinaryTree<Item>::tree_copy(BinaryTreeNode<Item>* root1){
    BinaryTreeNode<Item>* node = createNode(root1->data);
    if (root1->left != NULL) {
        node->left = tree_copy(root1->left);
    }
    if (root1->right != NULL) {
        node->right = tree_copy(root1->right);
    }
    return node;
}

template <class Item>
BinaryTreeNode<Item>* BinaryTree<Item>::create_node(const Item& entry){
    BinaryTreeNode<Item>* node = new BinaryTreeNode<Item>();
    node->data = entry;
    node->left = NULL;
    node->right = NULL;
    return node;
}

template<class Item>
void BinaryTree<Item>::insert(BinaryTreeNode<Item>*& root_ptr, const Item& entry){
    if (root_ptr == NULL) {
        root_ptr = create_node(entry);
    }
    else if (root_ptr->data >= entry) {
        insert(root_ptr->left, entry);
    }
    else insert(root_ptr->right, entry);
}

template<class Item>
void BinaryTree<Item>::search(BinaryTreeNode<Item>*  root_ptr,const Item& target,bool& found,BinaryTreeNode<Item>*& loc_ptr,int& nodeCnt){
    if(root_ptr == NULL){
        loc_ptr = NULL;
        found = false;
        nodeCnt += 1;
    }
    else if (root_ptr->data == target) {
        found = true;
        loc_ptr = root_ptr;
        nodeCnt += 1;
        return;
    }else if(target < root_ptr->data){
        nodeCnt +=1;
        search(root_ptr->left, target, found, loc_ptr, nodeCnt);
    }else{
        nodeCnt +=1;
        search(root_ptr->right, target, found, loc_ptr, nodeCnt);
    }
        
}

//////////////////////////////////////Linked List Definitions////////////////////////////////////
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

template<class Item>
void linkedList<Item>::searchRecursively(Node<Item>* root_node,int& cnt,bool&found,Item target){
    if (root_node == NULL) {
        found = false;
    }
    else if(root_node->data == target){
        found = true;
        cnt += 1;
    }
    else {
        cnt += 1;
        searchRecursively(root_node->link, cnt, found, target);
    }
}




