// Queue is implemented by linked list
// head and tail don't contain the data.

// 2023-07-11

// public member function
// void enqueue(const Object & x)
// Object & dequeue() const
// int size() const 
// int capacity() const 
// bool empty() const 
// void print() const

// Do i need to implement the big-five? no
// Only constructor and the destructor will do.

#ifndef QUEUE_BY_LIST_H
#define QUEUE_BY_LIST_H

class QueueEmpty{};

template <typename Object>
class Queue
{
    public:                                           
        explicit Queue(); // constructor // defualt argument only on interface // explicit only on header.
        ~Queue(); // destructor

        void enqueue(const Object & x);
        void enqueue(Object && x);
        const Object dequeue();
        int size() const;
        bool isempty() const;
        void print() const;

    private:
        struct Node
        {
                Object data;
                Node *next;

                Node(const Object & d = Object{}, Node * n = nullptr)
                : data{d}, next{n} {}

                Node(Object && d = Object{}, Node * n = nullptr)
                : data{std::move(d)}, next{n} {}
        };

        int theSize;
        Node * head;
        Node * tail;
};

#endif