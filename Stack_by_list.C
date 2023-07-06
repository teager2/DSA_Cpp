#include "C:\Users\theag\Desktop\cpp\HelloWorld\Stack_by_list.h"

template<typename Object>
Stack<Object>::Stack(int initSize )  // explicit only on header. not here
{
    theSize = initSize;
    std::list<Object> stack;
} 

template<typename Object>
Stack<Object>::Stack(const Stack & rhs) : theSize{rhs.theSize}        // copy constructor
{                                       // initialization list only for implementationa
    printf("copy constructor\n");
    std::list<Object> stack;
    stack.assign(rhs.stack.begin(), rhs.stack.end());
}

template<typename Object>
Stack<Object> & Stack<Object>::operator= (const Stack & rhs)  //copy assignment
{
    Stack copy = rhs;
    std::swap(*this, copy);
    return *this;
}

template<typename Object>
const Object & Stack<Object>::top() const
{
    return stack.front();
}

template<typename Object>
void Stack<Object>::pop()
{
    if (!empty())
    {
        stack.pop_front();
        --theSize;
    }
    else
    {
        std::cout << "The size of stack is 0" << std::endl;
        exit(1);
    }
}

template<typename Object>
int Stack<Object>::size()
{
    return theSize;
}

template<typename Object>
bool Stack<Object>::empty()
{
    return theSize == 0;
}

template<typename Object>
void Stack<Object>::push(const Object & x)
{
    stack.push_front(x);
    ++theSize;
}
template<typename Object>
void Stack<Object>::push(Object && x)
{
    stack.push_front(std::move(x));
    ++theSize;
}

template<typename Object>
void Stack<Object>::print()
{
    auto itr = stack.begin();
    std::cout << "size : " << theSize << std::endl;
    std::cout << "print item" << std::endl;
    std::cout << "[ " << *itr++;

    while (itr != stack.end())
        std::cout << ", " << *itr++;
    std::cout << " ]" << std::endl;
}