#include <iostream>
#include <vector>
#include <cstring>

// function Objects in 2 ways

// 1. function objects passing (simplest idea)
// 2. C++ style - operator() overloading and even shortening by omitting "operator". furture Standard Liabrary function

// Generic FindMax, with a function object, Version #1
// Precondition arr.size() >0
// #1 
// template <typename Object, typename Comparator>
// const Object & findMax (const std::vector<Object> & arr, Comparator cmp)
// {
//     int maxIndex = 0;
//     for (int i =1 ; i<arr.size() ; ++i)
//         if (cmp.isLessThan (arr[maxIndex],arr[i]))
//             maxIndex = i;

//     return arr[maxIndex];
// }
// #2-1 operator ()
template <typename Object, typename Comparator>
const Object & findMax (const std::vector<Object> & arr, Comparator isLessThan)
{
    int maxIndex = 0;
    for (int i =1 ; i<arr.size() ; ++i)
        if (isLessThan (arr[maxIndex],arr[i]))
            maxIndex = i;

    return arr[maxIndex];
}
// #2-2 defualt ordering - standard library function in <functional>
#include <functional>
template <typename Object>
const Object & findMax (const std::vector<Object> & arr)
{
    return findMax(arr, std::less <Object>{} );
}

// Function object
// #1
// class CaseInsensitiveCompare
// {
//     public:
//         bool isLessThan(const std::string & lhs, const std::string & rhs ) const
//             {
//                 return strcasecmp (lhs.c_str(),rhs.c_str()) < 0;
//             }
// };

//#2 operator()
class CaseInsensitiveCompare
{
    public:
        bool operator() (const std::string & lhs, const std::string & rhs ) const
            {
                return strcasecmp (lhs.c_str(),rhs.c_str()) < 0;
            }
};

int main()
{
    std::vector<std::string> arr = {"ZEBRA", "alligator", "crocodile"};
    std::cout << findMax( arr, CaseInsensitiveCompare{}) << std::endl;
    std::cout << findMax( arr) << std::endl;
}