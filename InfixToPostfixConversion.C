// Perform infix to postfix conversion.
// Use Stack_by_list i've implemented.
// Refer "Data Structures and algorithm analysis in C++" by Weiss, 3.6, page 108
// 2023-07-06

#include <iostream>
#include "Stack_by_list.h"
#include "Stack_by_list.C"

std::string Infix2Postfix(const std::string & infix)
{
    Stack<char> stack;
    std::string outfix;
    char t;

    for(int i = 0; i<infix.size();++i)
    {
        t = infix.at(i);
        std::cout << "stack: "<<std::endl;
        stack.print();
        std::cout<< "outfix: " << outfix <<std::endl<<std::endl;

        if(isdigit(t) || (t >= 'a' && t<='z') || (t >= 'a' && t<='Z')) 
        {
            outfix.push_back(t);
        }
        else
        {
            if(stack.empty())
            {
                stack.push(t);
            }
            else
            {
                switch(t)
                {
                    case '+':
                        if(stack.top()=='(')
                            stack.push(t);
                        else 
                        {
                            while(!stack.empty() && (stack.top()=='*'||stack.top()=='+'))
                            {
                                outfix.push_back(stack.top());
                                stack.pop();
                            }
                            stack.push(t);
                        }
                        break;
                    case '*':
                        if(stack.top()=='(' || stack.top()=='+')
                            stack.push(t);
                        else // *
                        {
                            outfix.push_back(stack.top());
                            stack.pop();
                            stack.push(t);
                        }
                        break;
                    case '(':
                        stack.push(t); // assume the expression is correct
                        break;
                    case ')':
                        while(stack.top()!='(')
                        {
                            outfix.push_back(stack.top());
                            stack.pop();
                        }
                        stack.pop(); // pop '('
                        break;
                }
            }
        }
    }
    while(!stack.empty())
    {
        outfix.push_back(stack.top());
        stack.pop();
    }

    return outfix;
}

int main()
{
    std::string infix = "1+2*3+(4*5+6)*7";
    std::string outfix;
    outfix = Infix2Postfix(infix);
    std::cout<<"Infix: " <<infix<<std::endl;
    std::cout<<"Outfix: " <<outfix<<std::endl;
    return 0;
}