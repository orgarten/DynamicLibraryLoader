/**
 * author: Orell Garten
 * date: 21/MAR/2020
 * licence: MIT
 *
 * This is the main file showing how to load dynamic libraries
 *
 **/

#include <iostream>
#include <string>
#include <memory>

// include Wrapper
#include "DynamicFunctionWrapper.h"
int main(int argc, char* argv[]) {

    // using the wrapper class
    auto wrapper = DynamicFunctionWrapper(argv[1]);
    wrapper.load_external_symbol("print_hello");

    // use function wrapper
    wrapper.print_hello("Orell");
   
    return 0;
}
