#include <iostream>
#include "Binary_Search_Tree.h"
#include "Binary_Search_Tree.cpp"

int main()
{
    BinarySearchTree<int> B1;
    B1.insert(6);
    B1.insert(8);
    B1.insert(2);
    B1.insert(1);
    B1.insert(4);
    B1.insert(3);
    B1.insert(5);
    B1.printTree(std::cout);
    std::cout << "Max : " << B1.findMax() << std::endl;
    std::cout << "Min : " << B1.findMin() << std::endl;
    std::cout << "Height : " << B1.height() << std::endl;

    int x = 7;
    std::cout << "Contain x : " << (B1.contains(x) ? "yes" : "no") << std::endl;

    return 0;
}