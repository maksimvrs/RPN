# Reverse Polish notation
## Getting started
### Installing
```
git clone https://github.com/maksimvrs/RPN.git
```
### Example
```
#include <iostream>

#include "src/RPN.hpp"

int main() {
    std::cout << "Enter an expression:" << std::endl;
    std::string input;
    std::getline(std::cin, input);
    std::cout << RPN::toRPN(input) << std::endl;
    return 0;
}
```
### Building
```
cmake ./
make 
./RPN
```
### A more complex example.
```
#include <iostream>

#include "src/RPN.hpp"

int main() {
    std::cout << "Enter an expression:" << std::endl;
    std::string input;
    std::getline(std::cin, input);
    RPN rpn(input);
    rpn.convert();
    std::cout << "Expression in Reverse Polish Notation:" << std::endl;
    std::cout << rpn.getRPNExpr() << std::endl;

    std::cout << "Enter x and y value: " << std::endl;
    float x, y;
    std::cin >> x >> y;
    std::cout << "The value of the expression:" << std::endl;
    std::cout <<  rpn.calculate(x, y) << std::endl;

    std::cout << "The value of the expression of the computed return function:" << std::endl;
    auto func = rpn.getFunction();
    std::cout << func(x, y) << std::endl;

    return 0;
}
```
*Output example:*
```
Enter an expression:
x * y
Expression in Reverse Polish Notation:
x y *
Enter x and y value: 
2 2
The value of the expression:
4
The value of the expression of the computed return function:
4
```
