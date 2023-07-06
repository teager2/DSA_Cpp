// Stack is implemented by std::list
// 2023-07-06

// public member function
// pop()
// push()
// top()
// print()
// empty()

// Do i need to implement the big-five?
// Constructor/Copy constructor/Copy assignment operator

#ifndef STACK_BY_LIST_H
#define STACK_BY_LIST_H

#include <list>
#include <algorithm>

template <typename Object>
class Stack
{
    public:                                           
        explicit Stack(int initSize=0); // constructor // defualt argument only on interface // explicit only on header.
        Stack(const Stack & rhs);         // copy constructor
        Stack & operator= (const Stack & rhs);  //copy assignment

        const Object & top() const;
        void pop();
        int size();
        bool empty();
        void push(const Object & x);
        void push(Object && x);
        void print();

    private:
        std::list<Object> stack;
        int theSize;
};

#endif