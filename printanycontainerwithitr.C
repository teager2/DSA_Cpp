#include <iostream>
#include <vector>
#include <list>

template<typename Container>
auto begin(Container & c) -> decltype(c.begin())
{
    return c.begin();
}

template<typename Container>
auto begin(const Container & c) -> decltype(c.begin())
{
    return c.begin();
}

template<typename Container>
auto end(Container & c) -> decltype(c.end())
{
    return c.end();
}

template<typename Container>
auto end(const Container & c) -> decltype(c.end())
{
    return c.end();
}

template <typename Container>
void print(const Container & c, std::ostream & out = std::cout)
{
    if (c.empty())
        out << "(empty)";
    else
    {
        // auto itr = begin(c);
        auto itr = c.begin();
        // Container::const_iterator itr = begin(c);

        out << "size : " << c.size() << std::endl;
        // out << "size(itr ver1.) : " << (*itr).size() << std::endl;
        // out << "size(itr ver2.) : " << itr->size() <<std::endl;

        out << "print items" << std::endl;
        out << "[ " << *itr++; // first item

        while(itr != end(c))
            out << ", " << *itr++;
        out << " ]" << std::endl;
    }
}


int main()
{
    std::vector<int> v {6,5,1,4,2};
    std::list<int> l {6,5,1,4,2};

    print(v,std::cout);

    return 0;
}