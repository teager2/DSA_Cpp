#include "C:\Users\theag\Desktop\cpp\HelloWorld\Queue_by_vector.h"

template<typename Object>
Queue<Object>::Queue() : theSize{0},theCapacity{SPARE_CAPACITY},front{0},back{0}  // constructor
{
    queue.resize(theCapacity);
} 

template<typename Object>
Queue<Object>::Queue(const Queue & rhs) : theSize{rhs.theSize},theCapacity{rhs.theCapacity},front{rhs.front},back{rhs.back}        // copy constructor
{                                       // initialization list only for implementationa
    printf("copy constructor\n");
    std::vector<Object> queue(theCapacity);
    for(int k = 0; k < theCapacity; ++k)
        queue[k] = rhs.queue[k];
}

template<typename Object>
Queue<Object> & Queue<Object>::operator= (const Queue & rhs)  //copy assignment
{
    printf("copy assignment\n");
    Queue copy = rhs;
    std::swap(*this, copy);
    return *this;
}

template<typename Object>
Queue<Object>::Queue(Queue && rhs) : theSize{rhs.theSize},theCapacity{rhs.theCapacity},front{rhs.front},back{rhs.back},queue{rhs.queue}     // move constructor
{ 
    printf("move constructor\n");
    rhs.theSize = 0;
    rhs.theCapacity = 0;
    rhs.front = 0;
    rhs.back = 0;
    rhs.queue.clear();
}

template<typename Object>
Queue<Object> & Queue<Object>::operator= (Queue && rhs)  //move assignment
{
    printf("move assignment\n");
    std::swap(theSize,rhs.theSize);
    std::swap(theCapacity,rhs.theCapacity);
    std::swap(front,rhs.front);
    std::swap(back,rhs.back);
    std::swap(queue,rhs.queue);
    return *this;
}

template<typename Object>
bool Queue<Object>::isempty() const
{
    return theSize == 0;
}

template<typename Object>
void Queue<Object>::print() const
{
    std::cout << "size : " << theSize << std::endl;
    std::cout << "front("<<front<<") [ ";
    for (int k = front; k != back; k = (k+1)%theCapacity)
        std::cout << queue[k] << " ";
    std::cout << "] back(" << back <<")" << std::endl;
}

template<typename Object>
void Queue<Object>::reserve(int newCapacity)
{
    std::vector<Object> temp(newCapacity);
    for(int i = 0; i<theCapacity; ++i)
        temp[i] = std::move(queue[i]);
    theCapacity = newCapacity;
    std::swap(temp,queue);
}

template<typename Object>
void Queue<Object>::enqueue(const Object & x)
{
    std::cout << "lvalue ver. of enqueue" << "\n";
    if(theSize==(theCapacity-1))
    {
        reserve(theCapacity*2);
    }
    queue.at(back) = x;
    back = (back+1)%theCapacity;
    ++theSize;
}

template<typename Object>
void Queue<Object>::enqueue(Object && x)
{
    std::cout << "rvalue ver. of enqueue" << "\n";
    if(theSize==(theCapacity-1))
    {
        reserve(theCapacity*2);
    }
    queue.at(back) = x;
    back = (back+1)%theCapacity;
    ++theSize;
}

template<typename Object>
Object & Queue<Object>::dequeue() 
{
    try
    {
        if(isempty())
            throw QueueEmpty();
        const int temp = front;
        front = (front+1)%theCapacity;
        --theSize;
        if(theSize == 0) 
            front = back = 0;
        return queue[temp];
    }
    catch(QueueEmpty e)
    {
        std::cout << "dequeue error : Queue is empty\n";
        exit(2);
    }
}

template<typename Object>
int Queue<Object>::size() const
{
    return theSize;
}

template<typename Object>
int Queue<Object>::capacity() const
{
    return theCapacity;
}