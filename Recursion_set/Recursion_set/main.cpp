//
//  main.cpp
//  Recursion_set
//
//  Created by Dhishan  A on 7/7/15.
//  Copyright (c) 2015 Dhishan  A. All rights reserved.
//

#include <iostream>
#include <unordered_set>

using namespace std;

unordered_set<string> parenthesis_list;

void generate_set(unordered_set<string> set);

int main(int argc, const char * argv[]) {
    
    unordered_set<string> set;
    set.insert("a");
    set.insert("b");
    set.insert("c");
    generate_set(set);
    for (auto it = parenthesis_list.begin(); it!=parenthesis_list.end(); ++it) {
        cout << *it << endl;
    }
    return 0;
}

void generate_set(unordered_set<string> set){
    if (set.empty()) {
        parenthesis_list.insert("{}");
        return;
    }
    string data = "{";
    for (auto it = set.begin(); it!=set.end(); ++it) {
        data += *it + ",";
        unordered_set<string> temp = set;
        temp.erase(*it);
        generate_set(temp);
    }
    data += "}";
    parenthesis_list.insert(data);
}

