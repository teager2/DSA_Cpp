#include <iostream>

// class IntCell
// {
//     public:
//         explicit IntCell(int initialValue = 0) // = 0 by only interface / explicit to avoid behind-the-scenes type conversion
//         {
//             storedValue = new int{initialValue};
//         }

//         int read() const
//         {
//             return *storedValue;
//         }

//         void write(int x)
//         {
//             *storedValue = x;
//         }

//     private:
//         int *storedValue;
// };

class IntCell
{
    public:
        explicit IntCell (int initialValue =0) //constructor
            {
                storedValue = new int{initialValue};
                std::cout << "constructor " << std::endl;
            }
        ~IntCell()
        {
            delete storedValue;
            std::cout << "destructor " << std::endl;
        }

        IntCell (const IntCell & rhs) //copy constructor
        {
            storedValue = new int{*rhs.storedValue};
            std::cout << "copy constructor " << std::endl;
        }

        IntCell (IntCell && rhs) : storedValue {rhs.storedValue} //move constructor
        {
            rhs.storedValue = nullptr;
            std::cout << "move constructor " << std::endl;
        }

        IntCell & operator= (const IntCell & rhs) // copy assignment 
        // return type of operator is a reference to the invoking object
        {
            if (this != &rhs)
                *storedValue = *rhs.storedValue;
            std::cout << "copy assignment " << std::endl;
            return *this;
        }

        IntCell & operator= (IntCell && rhs) // move assignment
        {
            std::swap(storedValue, rhs.storedValue);
            std::cout << "move assignment " << std::endl;
            return *this;
        }

        int read() const
        {
            return *storedValue;
        }
        void write(int x)
        {
            *storedValue = x;
        }

    private:
        int *storedValue;
};

int main()
{
    std::cout << "class a "<<std::endl;
    IntCell a{2};
    std::cout << std::endl<<std::endl;
    std::cout << "class b copy"<<std::endl;
    IntCell b = a;
    std::cout << std::endl<<std::endl;
    std::cout << "class c "<<std::endl;
    IntCell c;
    std::cout << std::endl<<std::endl;

    std::cout << "class c copy assignment "<<std::endl;
    c = b;
    std::cout << std::endl<<std::endl;
    a.write(4);
    std::cout << a.read() << std::endl << b.read() << std::endl << c.read() << std::endl;

    return 0;
}