#include "IntCell.h"

IntCell::IntCell(int initialValue) : storedValue{initialValue}
{

}

int IntCell::read() const // by default, mutator. but const makes it a accesor
{
    return storedValue;
}

void IntCell::write(int x)
{
    storedValue = x;
}