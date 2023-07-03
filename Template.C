#include "iostream"
#include "vector"

// function template
// return the maximun item in array a.
// Assumes a.size > 0.
// Comparable objects must provide operator< and operator= 

template <typename Comparable>
const Comparable & findMax( const std::vector<Comparable> & a)
{
    int maxIndex = 0;

    for(int i = 1; i < a.size(); ++i)
        if (a[maxIndex] < a[i])
            maxIndex = i;
    return a[maxIndex];
}

// class template
template <typename Object>
class MemoryCell
{
    public:
        explicit MemoryCell (const Object & initialValue = Object{})
            :storedValue{initialValue} {}
        const Object & read()
        {
            return storedValue;
        }
        void write (const Object & x)
        {
            storedValue = x;
        }

    private:
        Object storedValue;
};

// Square class
class Square
{
    public:
        explicit Square(double s = 0.0) : side{s} {}

        double getSide() const
        {
            return side;
        }

        void print(std::ostream & out = std::cout) const
        {
            out << "(square " << getSide() << ")";
        }

        bool operator< (const Square & rhs) const //so that the operator< in findMax can be evaluateed
        {
            return getSide() < rhs.getSide();
        }


    private:
        double side;
};

// define the output of class Square. here we print the side of Square.

std::ostream & operator<< ( std::ostream & out, const Square & rhs )
{
    rhs.print( out );
    return out;
}

int main()
{
    // // findMax test for pretty much primitive types
    // std::vector<int>        v1(37);
    // std::vector<double>     v2(40);
    // std::vector<std::string>  v3{"string","alligator"};

    // for (int i = 0 ; i<v1.size(); ++i)
    //     v1[i] = i * i;
    // for (int i = 0 ; i<v2.size(); ++i)
    //     v2[i] = i - i/10;

    // std::cout << findMax(v1) << std::endl;
    // std::cout << findMax(v2) << std::endl;
    // for (auto x : v3)
    //     std::cout << x << " ";
    // std::cout << std::endl;

    // // Memory Cell template test
    // MemoryCell<int> m1;
    // MemoryCell<std::string> m2{"hello"};

    // m1.write(37);
    // m2.write(m2.read()+" world");
    // std::cout << m1.read() << std::endl << m2.read() << std::endl;

    // findMax test for square class

    Square s1{2.0};
    std::cout << s1.getSide() << std::endl;

    std::vector<Square> v = {Square{3.0},Square{2.0},Square{2.5}};

    std::cout << findMax(v) << std::endl; 

    return 0;
}