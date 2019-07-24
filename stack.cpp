//
//  stack.cpp
//  artunsarioglu_cs300_hw1
//
//  Created by Artun on 10.07.2019.
//  Copyright © 2019 Artun. All rights reserved.
//

#include <iostream>
#include "stack.h"

using namespace std;

/*
Constructor of Stack
*/
template<class T>
Stack<T>::Stack()
{
    topOfStack = -1;
}


/*
 Test whether the stack is logically empty
 if stack is empty :
return true
 return false
 */
template<class T>
bool Stack<T>::isEmpty()
{
    return topOfStack == -1;
}


/*
 Returns the most recently inserted item in the stack.
 If stack is empty :
    throw -> exception
 */
template<class T>
coordinate<T> Stack<T>::top()
{
    if(isEmpty())
        throw underflow_error("Stack is empty!");
    return stack_array[topOfStack];
}


/*
 Insert 'coor' into the stack
 */
template<class T>
void Stack<T>::push(coordinate<T> coor)
{
    stack_array.push_back(coor);
    ++topOfStack;
}


/*
 Removes the most recently inserted item
 Exception if the stack is empty
 */
template<class T>
void Stack<T>::pop()
{
    if(isEmpty())
        throw underflow_error("Stack is empty!");
    stack_array.pop_back();
    topOfStack--;
}




