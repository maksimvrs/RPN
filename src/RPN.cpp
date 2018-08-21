#include <iostream>
#include <regex>
#include <stack>
#include <cmath>

#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(std::string expr) : m_expr(std::move(expr)) {}

RPN::~RPN() {}

std::string RPN::toRPN(std::string expr)
{
    std::string value;
    std::stack<char> stack;
    expr.erase(std::remove(expr.begin(), expr.end(), ' '), expr.end());
    std::regex regexSin("sin");
    std::regex regexCos("cos");
    expr = std::regex_replace(expr, regexSin, "s");
    expr = std::regex_replace(expr, regexCos, "c");
    for(char &c : expr) {
        if(std::isdigit(c) || c == 'x' || c == 'y' || c == '!') {
            value += c;
            if (!std::isdigit((&c)[1]))
                value += ' ';
        } else if(stack.empty() || c == '(' || c == 's' || c == 'c') {
            stack.push(c);
        } else if(c == '^') {
            while(stack.top() == 's' || stack.top() == 'c' || stack.top() == '^') {
                value += stack.top();
                value += ' ';
                stack.pop();
                if (stack.empty()) break;
            }
            stack.push(c);
        } else if(c == '*' || c == '/') {
            while(stack.top() == '*' || stack.top() == '/' || stack.top() == '^' ||
                  stack.top() == 's' || stack.top() == 'c') {
                value += stack.top();
                value += ' ';
                stack.pop();
                if (stack.empty()) break;
            }
            stack.push(c);
        } else if(c == '+' || c == '-') {
            while(stack.top() == '+' || stack.top() == '-'||
                  stack.top() == '*' || stack.top() == '/' ||
                  stack.top() == '^' || stack.top() == 's' || stack.top() == 'c') {
                value += stack.top();
                value += ' ';
                stack.pop();
                if (stack.empty()) break;
            }
            stack.push(c);
        } else if (c == ')') {
            while(stack.top() != '(' && !stack.empty()) {
                value += stack.top();
                value += ' ';
                stack.pop();
            }
            if (!stack.empty())
                stack.pop();
        }
    }
    while(!stack.empty()) {
        value += stack.top();
        value += ' ';
        stack.pop();
    }
    value.pop_back();
    return value;
}

void RPN::setExpr(std::string expr)
{
    m_expr = std::move(expr);
    m_RPNExpr = "";
}
std::string RPN::getRPNExpr()
{
    if (m_RPNExpr == "")
        convert();
    return m_RPNExpr;
}

std::string RPN::convert()
{
    return m_RPNExpr = toRPN(m_expr);
}
