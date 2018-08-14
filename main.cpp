#include <iostream>

#include "src/RPN.hpp"

int main() {
    std::cout << "Enter an expression:" << std::endl;
    std::string input;
    std::getline(std::cin, input);
    std::cout << RPN::toRPN(input) << std::endl;
    return 0;
}