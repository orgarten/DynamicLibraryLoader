#include "DynamicFunctionWrapper.h"

#include <iostream>
#include <string>

#include <dlfcn.h>

int DynamicFunctionWrapper::load_external_symbol(const std::string &symbol){
    if(!handle)
        return -1;
    // clear errors
    dlerror();

    *(void**) (&dyn_print_hello) = dlsym(handle, symbol.c_str());
    const char* error = dlerror();
    if(error != NULL) {
        std::cerr << error << "\n";
        return -1;
    }
    return 0;
}

// public interface to use
void DynamicFunctionWrapper::print_hello(const std::string& name)
{
    std::cout << "DynamicFunctionWrapper: ";
    dyn_print_hello(name);
}
