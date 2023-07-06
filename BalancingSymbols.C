// Check if the Symbols in word are balanced.
// Use Stack_by_list i've implemented.
// Refer "Data Structures and algorithm analysis in C++" by Weiss, 3.6, page 104
// 2023-07-06

#include <iostream>
#include "Stack_by_list.h"
#include "Stack_by_list.C"

void BalancingSymbols(const std::string & string)
{
    Stack<char> test;
    for (int i = 0; i < string.size(); ++i)
    {
        char t = string.at(i);

        if(t == '(' || t == '{' || t == '[')
            test.push(t);
        
        if (!test.empty() && ( t == ')' || t == '}' || t == ']'))
        {
            const char top = test.top();
            if(top == '(' && t == ')')
                test.pop();
            if(top == '{' && t == '}')
                test.pop();
            if(top == '[' && t == ']')
                test.pop();
        }
    }

    if (test.empty())
        std::cout << "Given sentence '" << string << "' is balanced." << std::endl;
    else 
        std::cout << "Given sentence '" << string << "' is Not balanced." << std::endl;
}

int main()
{
    std::string a="(i love you)";
    std::string b="([i love you])";
    std::string c="(i love you]";

    BalancingSymbols(a);
    BalancingSymbols(b);
    BalancingSymbols(c);
    return 0;
}