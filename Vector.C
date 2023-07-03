// vector class template "Vector" will be implemented
// Refer "Data Structures and algorithm analysis in C++" by Weiss, 3.4, page 87~

#include <iostream>
#include <algorithm>

template<typename Object>
class Vector
{
    public:
        //constructor
        explicit Vector(int initSize = 0) : theSize{initSize}, theCapacity{initSize + SPARE_CAPACITY}
        {
            objects = new Object[theCapacity];
        }

        //copy constructor
        Vector(const Vector & rhs) : theSize{rhs.theSize},theCapacity{rhs.theCapacity}
        {
            printf("copy constructor\n");
            objects = new Object[theCapacity];
            for(int i =0;i<theSize;++i)
                objects[i] = rhs.objects[i];
        }

        //copy assignment operator
        Vector & operator= (const Vector & rhs)
        {
            printf("copy assignment\n");
            Vector copy = rhs; // use of copy constructor
            std::swap(*this, copy); // swap is done by moving implemented in move constructor and move assignment 
            return *this; //Specifically, move constructor and 2 move assignment is called. 
        } // What std::swap does is, conceptually,
            //1. Vector temp(std::move(*this)) (move constructor)
            //2. *this = std::move(copy) (move assignment)
            //3. copy = std::move(temp) (move assignment)

        //destructor
        ~Vector()
        {
            delete [] objects;
        }

        //move constructor
        Vector(Vector && rhs) : theSize{rhs.theSize}, theCapacity{rhs.theCapacity}, objects{rhs.objects}
        {
            printf("move constructor\n");
            rhs.theSize = 0;
            rhs.theCapacity = 0;
            rhs.objects = nullptr;
        }

        //move assignment operator
        Vector & operator= (Vector && rhs) 
        {
            printf("move assignment\n");
            std::swap( theSize, rhs.theSize);
            std::swap( theCapacity, rhs.theCapacity);
            std::swap( objects, rhs.objects);
            return *this;
        }

        //How come i can't find the initialization of rhs object in this move operator? 
        //I can't quite understand this part since it isn't the same form from what i've seen on the internet

        void resize(int newSize)
        {
            if(newSize > theCapacity) 
                reserve(newSize * 2); //
            theSize = newSize;
        }

        void reserve(int newCapacity)
        {
            if(newCapacity < theSize)
                return;

            Object * newArray = new Object[newCapacity];
            for(int k = 0; k < theSize; ++k) //move all the value in Object vector
                newArray[k] = std::move(objects[k]); //values in objects are no longer in use
                                            //thus more efficient std::move is used
            theCapacity = newCapacity;
            std::swap(objects,newArray); // swap the address of vector. 
            // now objects points the series of memory(vector) with newCapacity
            delete []  newArray;
        }

        Object & operator[] (int index) // mutator ver.
        {
            if (index < 0 || index > theSize - 1)
            {
                std::cout << "invalid vector index is given" << std::endl;
                exit(1);
            }
            return objects[index];
        }

        const Object & operator[] (int index) const // accessor ver.
        {
            if (index < 0 || index > theSize - 1)
            {
                std::cout << "invalid vector index is given" << std::endl;
                exit(1);
            }
            return objects[index];
        }

        bool emtpy() const // accesor
        {
            return size() == 0;
        }

        int size() const // accesor
        {
            return theSize;
        }

        int capacity() const // accesor
        {
            return theCapacity;
        }

        void push_back (const Object & x)
        {
            if(theSize == theCapacity)
                reserve(2*theCapacity + 1);
            objects[theSize++] = x; 
        }

        void push_back (Object && x)
        {
            if(theSize == theCapacity)
                reserve(2*theCapacity + 1);
            objects[theSize++] = std::move(x); 
        }

        void pop_back() //delete the last item of vector
        {
            if (theSize == 0)
                std::cout << "the size of the vector is 0!" << std::endl;
            else 
                --theSize;
        }

        const Object & back () const // accessor and the return type is const
        {
            return objects[theSize -1];
        }

        typedef Object * iterator; // implement the itr with pointer. 
        typedef const Object * const_iterator; 

        iterator begin()
        {
            return objects;
        }

        const_iterator begin() const
        {
            return objects;
        }

        iterator end()
        {
            return &objects[size()]; // note that end refers the next address of last item
        }

        const_iterator end() const
        {
            return &objects[size()];
        }


        static const int SPARE_CAPACITY = 16;

    private:
        int theSize;
        int theCapacity;
        Object * objects;
};

int main()
{
    Vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);

    Vector<int> v2;
    v2.push_back(3);
    v2.push_back(4);
    v2.push_back(5);

    // Vector<int> v3 = v1; // copy constructor; 
    Vector<int> v4;  // constructor
    v4 = v2; //copy assignment, copy constructor, move constructor, move assignment, move assignement ??????

    // Vector<int> v5 = std::move(v1); //move constructor
    // Vector<int> v6; // constructor
    // v6 = std::move(v2); //move assignment

    
    // std::cout << "size of vec: " << v1.size() <<std::endl;
    // std::cout << "emtpy-ness of vec: " << v1.emtpy() <<std::endl;
    // std::cout << "capacity of vec: " << v1.capacity() <<std::endl;

    for(auto k = v4.begin() ; k < v4.end(); ++k)
        std::cout << *k <<std::endl;
    

    // return 0;

}
