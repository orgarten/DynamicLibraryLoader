/**
 * author: Orell Garten
 * date: 22/MAR/2020
 * license: MIT
 *
 * This file provides a class which wraps a known function from a shared object
 * */

#ifndef DYNAMIC_FUNCTION_WRAPPER
#define DYNAMIC_FUNCTION_WRAPPER

#include <string>
#include <dlfcn.h>

class DynamicFunctionWrapper {
public:
    DynamicFunctionWrapper(const std::string &module_name) : mod(module_name), handle(dlopen(mod.c_str(), RTLD_LAZY)) { };
    ~DynamicFunctionWrapper() { dlclose(handle); };
    
    int load_external_symbol(const std::string &symbol);
    void print_hello(const std::string &name);
private:
    const std::string &mod;
    void* handle;
    void (*dyn_print_hello)(const std::string&);
};
#endif
