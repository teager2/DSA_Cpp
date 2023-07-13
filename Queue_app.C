#include <iostream>
#define QUEUE_BY_LIST

#ifdef QUEUE_BY_VECTOR
#include "Queue_by_vector.h"
#include "Queue_by_vector.C"
#endif

#ifdef QUEUE_BY_LIST
#include "Queue_by_list.h"
#include "Queue_by_list.cpp"
#endif

int main()
{
    Queue<int> q1;
    q1.enqueue(1);
    q1.enqueue(2);
    q1.enqueue(3);
    q1.enqueue(4);
    q1.print();
    q1.dequeue();
    q1.dequeue();
    q1.print();

    return 0;
}