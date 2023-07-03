#include <iostream>

class IntCell
{
    public:
    IntCell()
    {
        storedValue = 0;
    }
    IntCell( int initialValue )
    {
        storedValue = initialValue;
    }
    int read()
    {
        return storedValue;
    }

    void write(int x)
    {
        storedValue = x;
    }
    
    private:
        int storedValue;
};
int main()
{
    std::cout << "Hello World" << std::endl;
    int x,p;
    x = 10;
    IntCell V1(1);
    IntCell V2;
    V2.write(x);
    p = V2.read();
    std::cout << "V1 : " << V1.read() << std::endl; 
    std::cout << "V2 : " << V2.read() << std::endl; 
    return 0;
}