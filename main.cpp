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

// header for dlopen(), dlerror(), ...
#include <dlfcn.h>


int main(int argc, char* argv[]) {

    // this needs to be a void pointer..apparently not possible to use smart pointers
    void* handle;

    // function pointer
    void (*print_hello)(const std::string& );

    // create handle
    handle = dlopen(argv[1], RTLD_LAZY);

    // check for errors
    if(!handle) {
        std::cerr << "Error while loading shared library: " << dlerror() << "\n";
        return -1;
    }

    // clear any errors
    dlerror();

    // loading the actual function
    *(void**) (&print_hello) = dlsym(handle, "print_hello");

    // check for errors
    const char* error{dlerror()};
    if(error != NULL ) {
        std::cerr << "error during loading of the symbol: " << error << "\n";
        return -1;
    }

    // use function pointer
    print_hello("Orell");
    dlclose(handle);
    return 0;
}
