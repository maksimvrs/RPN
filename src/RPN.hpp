#ifndef RPN_RPN_HPP
#define RPN_RPN_HPP

#include <iostream>
#include <regex>
#include <stack>
#include <cmath>

class RPN {
public:
    RPN();
    RPN(std::string);
    ~RPN();

    void setExpr(std::string);
    static std::string toRPN(std::string);
    std::string convert();
    std::string getRPNExpr();
    float calculate(float, float);
    float (*getFunction())(float, float);

private:
    std::string m_expr;
    std::string m_RPNExpr;
};


#endif //RPN_RPN_HPP
