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

class DynamicFunctionWrapper {
public:
    DynamicFunctionWrapper(const std::string &module_name) : mod(module_name), handle(dlopen(mod.c_str(), RTLD_LAZY)) { };
    ~DynamicFunctionWrapper() { dlclose(handle); };
    
    int load_external_symbol(const std::string &symbol){
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
    };
    void print_hello(const std::string& name)
    {
        std::cout << "DynamicFunctionWrapper: ";
        dyn_print_hello(name);
    };
private:
    const std::string &mod;
    void* handle;
    void (*dyn_print_hello)(const std::string&);
};

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

    auto wrapper = DynamicFunctionWrapper(argv[1]);
    wrapper.load_external_symbol("print_hello");


    // use function pointer
    print_hello("Orell");
    wrapper.print_hello("Orell");
    dlclose(handle);
    return 0;
}
