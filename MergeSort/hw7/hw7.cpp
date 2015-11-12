//  Assignment 7
//  hw7.cpp
//  HW7 - Merge Sort
//
//  Dhishan Amaranath
//  N16909360
//


#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

template <class Item,class ItemSize>
void Merge(Item data[], ItemSize leftaryS, ItemSize rightaryS);
template <class Item,class ItemSize>
void MergeSort(Item data[], ItemSize arySize);

char flag;
int complexityCnt;

int main(int argc, const char * argv[]) {
    
    complexityCnt = 0;
    vector<int> temp;
    cout << "Please Enter list of Integers" << endl;
    string input;
    getline(cin, input);
    istringstream iss(input);
    string num;
    string command;
    getline(iss,command,' ');
    flag = command.at(0);
    flag = toupper(flag);
    while (getline(iss,num,' ')) {
        temp.push_back(stoi(num));
    }
    int* array = new int[temp.size()];
    for (int y=0;y<temp.size();y++ ) {
        array[y]  =temp[y];
    }
    MergeSort(array,temp.size());
    for (int y=0;y<temp.size();y++ ) {
        cout << to_string(array[y]) << " ";
    }
    cout << endl << "Complexity variant :" << complexityCnt << endl;
    cout <<"Array Lenght: " << temp.size() << endl;
    delete [] array;
    return 0;
}

template <class Item,class ItemSize>
void MergeSort(Item data[], ItemSize arySize){
    if (arySize<=1) {
        return;
    }
    int leftaryS = 1;
    int rightaryS = arySize - leftaryS;
    MergeSort(data,leftaryS);
    MergeSort((data+leftaryS),rightaryS);
    
    Merge(data,leftaryS,rightaryS);
}

template <class Item,class ItemSize>
void Merge(Item data[], ItemSize leftaryS, ItemSize rightaryS){

    int leftIndex = 0;
    int rightIndex = 0;
    int copied = 0;
    
    Item* dataSorted = new Item[leftaryS + rightaryS];
    
    while (leftIndex < leftaryS && rightIndex < rightaryS) {
        if (flag == 'D') {
            if (data[leftIndex] > (data+leftaryS)[rightIndex]) {
                dataSorted[copied++] = data[leftIndex++];
            }else dataSorted[copied++] = (data+leftaryS)[rightIndex++];
        } else {
            if (data[leftIndex] < (data+leftaryS)[rightIndex]) {
                dataSorted[copied++] = data[leftIndex++];
            }else dataSorted[copied++] = (data+leftaryS)[rightIndex++];
        }
    }
    
    while (leftIndex < leftaryS) {
        dataSorted[copied++] = data[leftIndex++];
    }
    
    while (rightIndex < rightaryS) {
        dataSorted[copied++] = (data+leftaryS)[rightIndex++];
    }
    
    for (int i=0; i<leftaryS + rightaryS; i++) {
        data[i] = dataSorted[i];
        complexityCnt++;
    }
    delete [] dataSorted;
    
}
