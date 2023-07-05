// implementation of doubly linked list
// Refer "Data Structures and algorithm analysis in C++" by Weiss, 3.5, page 91~
// 2023-07-05

#include <iostream>

template <typename Object>
class List
{
    private:
        struct Node
        {
            Object data;
            Node* prev;
            Node* next;

            Node(const Object &d = Object{}, Node * p = nullptr, Node * n = nullptr) //object coule also be class;
            : data{d}, prev{p}, next{n} {}

            Node(Object && d, Node * p = nullptr, Node * n = nullptr)
            : data{std::move(d)}, prev{p}, next{n}{}

        };

    public:
        class const_iterator
        {
            public:
                const_iterator() : current{nullptr} {} // constructor (if not propely initialized, this iterator refers nullptr)

                const Object & operator* () const
                {
                    return retrieve();
                }

                const_iterator & operator++() //prefix operator
                {
                    current = current->next;
                    return *this;
                }

                const_iterator operator++(int) //postfix operator / return const_iterator itself (slower)
                {
                    const_iterator old = *this;
                    ++(*this); //using the prefix;
                    return old; // return old itself is the key of postfix operator
                }

                bool operator==(const const_iterator & rhs) const
                {
                    return current == rhs.current;
                }

                bool operator!=(const const_iterator & rhs) const
                {
                    return !(*this == rhs); // using the operator==
                }

            protected:
                Node *current;
                Object & retrieve() const
                {
                    return current->data;
                }
                const_iterator(Node *p) : current{p} {}

                friend class List<Object>;
        };

        class iterator : public const_iterator //base class is const_iterator
        {
            public:
                iterator(){}

                Object & operator* () //operator of mutator version
                {
                    return const_iterator::retrieve();
                }

                const Object & operator*() const
                {
                    return const_iterator::operator*(); // repeat again so the ambiguity is avoided.
                }

                //due to changed return type (const_iterator -> iterator)
                //we provide a new pair of operator++
                iterator & operator++() //prefix
                {
                    this->current = this->current->next;
                    return *this;
                }

                iterator operator++(int) //no & here
                {
                    iterator old = *this;
                    ++(*this);
                    return old;
                }

            protected:
                iterator(Node *p) : const_iterator{p} {}//constructor 

                friend class List<Object>;
        };

    public:
        List() //constructor
        {
            init(); // creates empty List;
        }
        ~List() //destructor
        {
            clear();
            delete head;
            delete tail;
        }
        List(const List & rhs) // copy constructor
        {
            init();
            for(auto & x : rhs) //by invoking member methods
                push_back(x);
        }

        List & operator= ( const List & rhs) // copy assignment operator
        {
            List copy = rhs; // copy constructor
            std::swap(*this,copy);
            return *this;
        }
        List (List && rhs) : theSize{rhs.theSize},head{rhs.head},tail{rhs.tail} // move constructor
        {
            rhs.theSize = 0;
            rhs.head = nullptr;
            rhs.tail = nullptr;
        }

        List & operator= (List && rhs) // move assignment operator
        {
            std::swap(theSize, rhs.theSize);
            std::swap(head, rhs.head);
            std::swap(tail, rhs.tail);
            return *this;
        }

        void init() //sets empty doubly linked list
        {
            theSize = 0;
            head = new Node;
            tail = new Node;
            head->next = tail;
            tail->prev = head;
        }

        iterator begin() //construct the iterator whose member(Node*) points the first item
        {
            // return {head->next};
            return iterator{head->next};
        }
        iterator end()
        {
            return iterator{tail};
        }
        const_iterator begin() const
        {
            return const_iterator{head->next};
        }
        const_iterator end() const
        {
            return const_iterator{tail};
        }

        int size() const
        {
            return theSize;
        }
        bool empty() const
        {
            return size() == 0;
        }

        void clear()
        {
            while(!empty())
                pop_front(); // pop front is not a burden(constant time) for doubly linked list
        }

        Object & front() // methods utilizing the iterator
        {
            return *begin();
        }

        const Object & front() const // accessor version
        {
            return *begin();
        }

        Object & back() 
        {
            return *--end();
        }

        const Object & back() const // accessor version
        {
            return *--end();
        }

        void push_front(const Object & x) // done by insert
        {
            insert(begin(),x);
        }
        void push_front(Object && x) // done by insert
        {
            insert(begin(),std::move(x));
        }
        void push_back(const Object & x) // done by insert
        {
            insert(end(),x);
        }
        void push_back(Object && x) // done by insert
        {
            insert(end(),std::move(x));
        }

        void pop_front()
        {
            erase(begin());
        }
        void pop_back()
        {
            erase(--end()); // end() refers the last tail node
        }

        iterator insert( iterator itr, const Object & x)
        {
            Node *p = itr.current;
            theSize++;
            // Node * newNode = new Node{x,p->prev,p};
            // p->prev->next = newNode;
            // p->prev = newNode;
            return {p->prev=p->prev->next=new Node{x, p->prev, p}}; //consturctor 
            // return iterator{p->prev=p->prev->next=new Node{x, p->prev, p}}; //consturctor 
        }

        iterator insert( iterator itr, Object && x)
        {
            Node *p = itr.current;
            theSize++;
            return {p->prev=p->prev->next=new Node{std::move(x), p->prev, p}}; //constructor
            // return iterator{p->prev=p->prev->next=new Node{std::move(x), p->prev, p}}; //constructor
        }

        iterator erase(iterator itr) //erase single node
        {
            Node *p = itr.current;
            iterator retVal{p->next}; // now the p->next refers the current node
            p->prev->next = p->next;
            p->next->prev = p->prev;
            delete p; // reclaim the erased item;
            theSize--;

            return retVal;
        }
        iterator erase(iterator from, iterator to) //erase nodes
        {
            for(auto k = from; k!= to;)
                k=erase(k);

            return to;
        }

    private:
        int theSize;
        Node *head;
        Node *tail;

};

//Generic begin and end
template<typename Container>
auto begin(Container & c) -> decltype(c.begin())
{
    return c.begin();
}

template<typename Container>
auto end(Container & c) -> decltype(c.end())
{
    return c.end();
}

//print
template <typename Container>
void print(const Container & c, std::ostream & out = std::cout) // print any container
{
    if (c.empty())
        out << "(empty)";
    else
    {
        // auto itr = begin(c);
        // auto itr = c.begin();
        typename Container::const_iterator itr = begin(c); // typename!

        out << "size : " << c.size() << std::endl;
        // out << "size(itr ver2.) : " << itr->size() <<std::endl;

        out << "print items" << std::endl;
        out << "[ " << *itr++; // first item (it's postfix, so it outputs the firstitem, although after the operation itr refers the second item)


        while(itr != end(c))
            out << ", " << *itr++;
        out << " ]" << std::endl;
    }
}

int main()
{
    List<int> l1;
    l1.push_back(1);
    l1.push_back(2);

    print(l1,std::cout);

    l1.clear();
    l1.push_back(5);
    l1.push_back(6);

    print(l1,std::cout);
    l1.pop_front();
    print(l1,std::cout);

    return 0;
}