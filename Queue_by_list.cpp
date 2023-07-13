#include "C:\Users\theag\Desktop\cpp\HelloWorld\Queue_by_list.h"


template<typename Object>
Queue<Object>::Queue()// constructor
{
    std::cout << "constructor " << "\n";
    theSize = 0;
    head = new Node{Object{},nullptr};
    tail = new Node{Object{},nullptr};
    head->next = tail;
    tail->next = nullptr;
    std::cout << "constructor end " << "\n";
} 

template<typename Object>
Queue<Object>::~Queue()// destructor
{
    std::cout << "destructor " << "\n";
    while (!isempty())
    {
        dequeue();
    }
    delete head;
    delete tail;
} 

template<typename Object>
bool Queue<Object>::isempty() const
{
    return theSize == 0;
}

template<typename Object>
void Queue<Object>::print() const
{
    std::cout<<"the size is " << theSize << std::endl;
    Node * current_Node = head->next;
    std::cout << "front"<<" [ ";
    while(current_Node != tail)
    {
        std::cout << current_Node->data << " ";
        current_Node = current_Node->next;
    }
    std::cout << "] back" << std::endl;
}


template<typename Object>
void Queue<Object>::enqueue(const Object & x)
{
    // head          tail
    // (0) -> ( ) -> (0)  -> nullptr
    tail->data = x;
    // head          tail
    // (0) -> ( ) -> (x) -> nullptr 
    tail->next = new Node{Object{},nullptr}; 
    // head         tail    tail->next
    // (0) -> ( ) -> (x)   ->   (0)  ->  nullptr
    tail = tail->next;
    // head                     tail
    // (0) -> ( ) -> (x)   ->   (0) -> nullptr
    ++theSize;
}

template<typename Object>
void Queue<Object>::enqueue(Object && x)
{
    // head          tail
    // (0) -> ( ) -> (0)  -> nullptr
    tail->data = std::move(x);
    // head          tail
    // (0) -> ( ) -> (x) -> nullptr 
    tail->next = new Node{Object{},nullptr}; 
    // head         tail    tail->next
    // (0) -> ( ) -> (x)   ->   (0)  ->  nullptr
    tail = tail->next;
    // head                     tail
    // (0) -> ( ) -> (x)   ->   (0) -> nullptr
    ++theSize;
}


template<typename Object>
const Object Queue<Object>::dequeue() 
{
    try
    {
        if(isempty())
            throw QueueEmpty();
        

        // head          tail
        // (0) -> (x) -> (0)  -> nullptr
        Node * first = head->next;
        // head  first   tail
        // (0) -> (x) -> (0)  -> nullptr
        Object retVal = first->data; //head and tail's data are the ends of the queue.
        head->next = first->next;
        // head  first   tail
        // (0)    (x)    (0)  -> nullptr
        //  ↑-------------↑
        delete first;
        // head    tail
        // (0)  -> (0)  -> nullptr
        --theSize;
        return retVal;
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
