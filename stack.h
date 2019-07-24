//
//  stack.h
//  artunsarioglu_cs300_hw1
//
//  Created by Artun on 10.07.2019.
//  Copyright © 2019 Artun. All rights reserved.
//

#ifndef stack_h
#define stack_h

#include <vector>
using namespace std;

// this always will be integer therefore I dont necessarily need to implement template class here but I will do it for whatsoever reason
template<class T>
struct coordinate {
    int xCor; // x-axis of coordinate
    int yCor; // y-oordinate of coordinate
    
    //any initial coordinate will be 0,0
};

template <class T>
class Stack {
private:
    //T top; // in our case it is integer
    vector<coordinate<T>> stack_array;
    T topOfStack;
    // Put your internal data representation here
    
public:
    Stack(); //default constructor , contains nothing
    
    void push(coordinate<T> coor);
    void pop();
    
    coordinate<T> top();
    bool isEmpty();
    
    const static T noItem;
};

//#include "stack.cpp"

#endif /* stack_h */
