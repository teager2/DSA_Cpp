// Perform postfix expression when the expressions are given as a string.
// Use Stack_by_list i've implemented.
// Refer "Data Structures and algorithm analysis in C++" by Weiss, 3.6, page 105
// 2023-07-06

#include <iostream>
#include "Stack_by_list.h"
#include "Stack_by_list.C"

void PostfixExpression(const std::string & string)
{
    Stack<double> stack;
    char t;
    double a,b;

    for(int i = 0; i < string.length();++i)
    {
        t = string.at(i);
        if(isdigit(t))
        {
            stack.push((double)t-48.0); // ASCII of '0' is 48
        }
        else{
            a = stack.top(); stack.pop();
            b = stack.top(); stack.pop();
            switch(t)
            {
                case '+':
                    stack.push(a+b);
                    break;
                case '-':
                    stack.push(a-b);
                    break;
                case '*':
                    stack.push(a*b);
                    break;
                case '/':
                    stack.push(a/b);
                    break;
            }
        }
    }

    const double result = stack.top();
    std::cout << "Result of postfix expression is " << result << std::endl;
}

int main()
{
    std::string expression = "6523+8*+3+*"; //answer is 288
    PostfixExpression(expression);

    return 0;
}
