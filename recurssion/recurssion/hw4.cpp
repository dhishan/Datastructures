/**
 Assignment 4
 hw4.cpp
 Dhishan Amaranath
 N16909360
 **/

#include <iostream>
#include <unordered_set>

using namespace std;

unordered_set<string> parenthesis_list;

void generate_parenthesis(string set,int count,int opencnt,int closecnt);

int main(int argc, const char * argv[]) {
    int n;
    cout << "Enter the number of pairs to generate" << endl;
    cin >> n;
    generate_parenthesis("",n,0,0);
    for (auto it = parenthesis_list.begin(); it!=parenthesis_list.end(); ++it) {
        cout << *it << endl;
    }
    return 0;
}

void generate_parenthesis(string set,int count,int opencnt,int closecnt){
    if (closecnt == count) {
        parenthesis_list.insert(set);
        return;
    }
    if (opencnt < count) {
        generate_parenthesis(set+"(",count,opencnt+1,closecnt);
    }
    if (closecnt < opencnt) {
        generate_parenthesis(set+")",count,opencnt,closecnt+1);
    }
}
