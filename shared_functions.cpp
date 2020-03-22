#include <iostream>
#include <string>

extern "C" 
void print_hello(const std::string& name) {
    std::cout << "hello " << name << "\n";
}



