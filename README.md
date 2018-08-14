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
```
### Building
```
cmake ./
make 
./RPN
Enter an expression:
( 6 - 3) ^2 - 11
63-2^11
```
