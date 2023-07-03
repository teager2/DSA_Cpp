#include <iostream>
#include "IntCell.h"
#include "IntCell.C"

int main()
{
    IntCell m,n{3};
    m.write(5);
    std::cout << "Cell m contents: " << m.read() << std::endl;
    std::cout << "Cell n contents: " << n.read() << std::endl;

    IntCell *p = new IntCell;
    p->write(6);
    std::cout << "Cell p contents: " << p->read() << std::endl;
    delete p;
    
    return 0;
    
}