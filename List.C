// implementation of doubly linked list
// Refer "Data Structures and algorithm analysis in C++" by Weiss, 3.5, page 91~
// 2023-07-05

// Error check version

// Major error hosts
// 1. Uninitiallized List           
    // --> the List's pointer is nullptr
    // --> not allowed in all cases. (the erase/insert/++/* should not be applied)

// 2. Uninitiallized (const_)iterator
    // --> the current's pointer is nullptr
    // --> not allowed in all cases. (the erase/insert/++/* should not be applied)

// 3. Iterator at endmarker (at times)
    // --> the current's next pointer is nullptr
    // --> erase/++/* should not be applied, the only insertion is allowed (which is pop_back())
    // --> should be checked at the List's member function insert/erase
    // --> should be checked at the iterator's operator ++/* 

// 4. Iterator at head
    // --> the current is in head. somthing is wrong from the beginning.
    // --> not allowed in all cases. (the erase/insert/++/* should not be applied)
    // --> c.f.) operator ++ might be made to be valid in some cases, but not valid here

// 5. Iterator for different List 
    // --> the iterator is from other Container
    // --> not allowed in erase/insert 
    // --> the iterator now have the List from which it was constructed as a member variable.
    // --> c.f.) ++/* are not List's member function. they're iterator's operators

// assertions and exceptions
// For major error hosts 1,2,4, they are intrinsically invalid.
    // --> they are together called as assertIsValid and check for erase/insert/++/*.
    // --> throw IteratorOutOfBoundsException 
// For major error host 3, the endmarker check would be performed for erase/++/* in addition to the assertIsValid test
    // --> throw IteratorOutOfBoundsException ("iterator is at endmarker, erase/++/* is not possible")
// For major error host 5, the iterator's List check would be performed when eras/insert is performed.
    // --> throw IteratorMisMatchException

// Haven't studied exception handling in c++...
// So the exceptions will be just warning phrases for now.

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
                const_iterator() : theList{nullptr},current{nullptr} {} // constructor (if not propely initialized, this iterator refers nullptr)

                const Object & operator* () const
                {
                    return retrieve();
                }

                const_iterator & operator++() //prefix operator
                {
                    assertIsValid();
                    if(current->next==nullptr)
                    {
                        std::cout << "Cannot retrieve from the endmarker."<< std::endl;
                        exit(1);
                    }
                    current = current->next;
                    return *this;
                }

                const_iterator operator++(int) //postfix operator / return const_iterator itself (slower)
                {
                    assertIsValid();
                    if(current->next==nullptr)
                    {
                        std::cout << "Cannot retrieve from the endmarker."<< std::endl;
                        exit(1);
                    }
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
                const List<Object> *theList; // the List from which this const_iteraotr was constructed
                Node *current;

                Object & retrieve() const
                {
                    assertIsValid();
                    if(current->next==nullptr)
                    {
                        std::cout << "Cannot retrieve from the endmarker."<< std::endl;
                        exit(1);
                    }
                    return current->data;
                }
                const_iterator(const List<Object> & lst, Node *p) : theList{&lst}, current{p} {}

                void assertIsValid() const
                {
                    if(theList == nullptr || current == nullptr || current == theList -> head)
                    {
                        std::cout << "Iterator or List not Valid" << std::endl;
                        exit(1);
                        // throw IteratorOutofBoundsException{};
                    }
                }
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
                    assertIsValid();
                    if(this->current->next==nullptr)
                    {
                        std::cout << "Cannot retrieve from the endmarker."<< std::endl;
                        exit(1);
                    }
                    this->current = this->current->next;
                    return *this;
                }

                iterator operator++(int) //no & here
                {
                    assertIsValid();
                    if(this->current->next==nullptr)
                    {
                        std::cout << "Cannot retrieve from the endmarker."<< std::endl;
                        exit(1);
                    }
                    iterator old = *this;
                    ++(*this);
                    return old;
                }

            protected:
                // iterator(const List<Object> & lst, Node *p) : const_iterator{&lst,p} {}//constructor 
                iterator(const List<Object> & lst, Node *p) //constructor 
                {
                    this->theList = &lst;
                    this->current = p;
                }

                void assertIsValid() const // inherited from const_iterator, but i should makr it const? why?
                {
                    if(this->theList == nullptr ||this->current == nullptr||this->current == this->theList->head)
                    {
                        std::cout << "Iterator or List not Valid" << std::endl;
                        exit(1);
                        // throw IteratorOutofBoundsException{};
                    }
                }

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
            // return iterator{*this,head->next};

            iterator itr{*this, head->next};
            return itr;
        }
        iterator end()
        {
            // return iterator{tail};

            return iterator{*this,tail};
        }
        const_iterator begin() const
        {
            // return const_iterator{head->next};

            const_iterator itr{*this, head->next};
            return itr;
        }
        const_iterator end() const
        {
            // return const_iterator{tail};

            return const_iterator{*this, tail};
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
            itr.assertIsValid();
            if(itr.theList != this)
            {
                std::cout << "the iterator is not from the List from which it was constructed" << std::endl;
                exit(1);
            }
            
                
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
            itr.assertIsValid();
            if(itr.theList != this)
            {
                std::cout << "the iterator is not from the List from which it was constructed" << std::endl;
                exit(1);
            }
            Node *p = itr.current;
            theSize++;
            // return {p->prev=p->prev->next=new Node{std::move(x), p->prev, p}}; //constructor

            return iterator{*this,p->prev=p->prev->next=new Node{std::move(x), p->prev, p}}; //constructor
        }

        iterator erase(iterator itr) //erase single node
        {
            itr.assertIsValid();
            if(itr.current->next==nullptr)
            {
                std::cout << "Cannot retrieve from the endmarker."<< std::endl;
                exit(1);
            }
            if(itr.theList != this)
            {
                std::cout << "the iterator is not from the List from which it was constructed" << std::endl;
                exit(1);
            }
            Node *p = itr.current;
            // iterator retVal{p->next}; // now the p->next refers the current node
            iterator retVal{*this,p->next}; // now the p->next refers the current node
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
    l1.push_back(3);
    print(l1,std::cout);

    return 0;
}