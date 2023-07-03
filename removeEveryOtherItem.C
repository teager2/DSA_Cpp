#include <iostream>
#include <vector>
#include <list>

template<typename Container>
void removeEveryOtherItem(Container & lst) // call by reference
{
    // Container::iterator = lst.begin();
    auto itr = lst.begin();

    while(itr!=lst.end())
    {
        itr = lst.erase(itr); //return value 
        if(itr != lst.end())
            ++itr;
    }
}

int main()
{
    std::vector<int> v {6,5,1,4,2};
    std::list<int> l {6,5,1,4,2};

    removeEveryOtherItem (v);
    removeEveryOtherItem (l);

    for(std::vector<int>::iterator itr = v.begin(); itr!=v.end();++itr)
        std::cout << *itr << std::endl;
        
    for(std::vector<int>::iterator itr = v.begin(); itr!=v.end();++itr)
        std::cout << *itr << std::endl;

    return 0;

}