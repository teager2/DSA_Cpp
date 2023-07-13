// Queue is implemented by std::vector
// circular-array
// 2023-07-11

// public member function
// void enqueue(const Object & x)
// Object & dequeue() const
// int size() const 
// int capacity() const 
// bool empty() const 
// void print() const

// public member variable
// static const int SPARE_CAPACITY

// private member function
// void reserve(int newcapacity)

// private member variable
// std::vector<Object> queue
// int back - position number of the next position of the back element
// int front - position number of the front element
// int currentSize
// int currentCapacity

// Do i need to implement the big-five? no
// Only constructor and the destructor will do.
// but All 5 are implemented here.
// Constructor/Copy constructor/Copy assignment operator/move constructor/move assigement operator

#ifndef QUEUE_BY_VECTOR_H
#define QUEUE_BY_VECTOR_H

#include <vector>

class QueueEmpty{};

template <typename Object>
class Queue
{
    public:                                           
        explicit Queue(); // constructor // defualt argument only on interface // explicit only on header.
        // ~Queue(); // no need, std::vector will do automatically
        Queue(const Queue & rhs);         // copy constructor
        Queue & operator= (const Queue & rhs);  //copy assignment
        Queue(Queue && rhs);
        Queue & operator = (Queue && rhs);

        void enqueue(const Object & x);
        void enqueue(Object && x);
        Object & dequeue();
        int size() const;
        int capacity() const; 
        bool isempty() const;
        void print() const;

        static const int SPARE_CAPACITY = 10;

    private:
        void reserve(int newCapacity);

        std::vector<Object> queue;
        int theSize;
        int theCapacity;
        int front; //position number of front of queue
        int back; // position number of the next item of the end of queue
};

#endif