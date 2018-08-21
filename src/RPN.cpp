#include <iostream>
#include <regex>
#include <stack>
#include <cmath>
#include <sstream> 

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

float RPN::calculate(float x, float y)
{
    std::stringstream input(m_RPNExpr);
    std::string token;
    std::stack<double> stack;
    while (input >> token) {
        if (token == "+") {
			double a = stack.top();
			stack.pop();
			double b = stack.top();
			stack.pop();
			stack.push(a + b);
		}
		else if (token == "-") {
			double a = stack.top();
			stack.pop();
			double b = stack.top();
			stack.pop();
			stack.push(b - a);
		}
		else if (token == "*") {
			double a = stack.top();
			stack.pop();
			double b = stack.top();
			stack.pop();
			stack.push(a * b);
		}
		else if (token == "/") {
			double a = stack.top();
			stack.pop();
			double b = stack.top();
			stack.pop();
			stack.push(b / a);
		}
        else if (token == "^") {
            double a = stack.top();
			stack.pop();
			double b = stack.top();
			stack.pop();
			stack.push(pow(b, a));
        }
        else if (token == "s") {
            double a = stack.top();
			stack.pop();
            stack.push(sin(a));
        }
        else if (token == "c") {
            double a = stack.top();
			stack.pop();
            stack.push(cos(a));
        }
        else if (token == "x") {
            stack.push(x);
        }
        else if (token == "y") {
            stack.push(y);
        }
		else {
			float num = std::stoi(token);
	        stack.push(num);
		}
    }
    if(stack.size() != 1)
        throw 1;
    return stack.top();
}

float (*RPN::getFunction())(float, float)
{
    const std::string expr = m_RPNExpr;
    auto func = [this](float x, float y) -> float {
        std::stringstream input(m_RPNExpr);
        std::string token;
        std::stack<double> stack;
        while (input >> token) {
            if (token == "+") {
                double a = stack.top();
                stack.pop();
                double b = stack.top();
                stack.pop();
                stack.push(a + b);
            }
            else if (token == "-") {
                double a = stack.top();
                stack.pop();
                double b = stack.top();
                stack.pop();
                stack.push(b - a);
            }
            else if (token == "*") {
                double a = stack.top();
                stack.pop();
                double b = stack.top();
                stack.pop();
                stack.push(a * b);
            }
            else if (token == "/") {
                double a = stack.top();
                stack.pop();
                double b = stack.top();
                stack.pop();
                stack.push(b / a);
            }
            else if (token == "^") {
                double a = stack.top();
                stack.pop();
                double b = stack.top();
                stack.pop();
                stack.push(pow(b, a));
            }
            else if (token == "s") {
                double a = stack.top();
                stack.pop();
                stack.push(sin(a));
            }
            else if (token == "c") {
                double a = stack.top();
                stack.pop();
                stack.push(cos(a));
            }
            else if (token == "x") {
                stack.push(x);
            }
            else if (token == "y") {
                stack.push(y);
            }
            else {
                float num = std::stoi(token);
                stack.push(num);
            }
        }
        if (stack.size() != 1)
            throw 1;
        return stack.top();
    };
    static std::function<float(float, float)> staticFunc = func;
    return [](float x, float y) { return staticFunc(x, y); };
}
