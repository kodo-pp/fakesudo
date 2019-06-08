#pragma once

#include <cstdlib>
#include <dlfcn.h>
#include <iostream>


template <typename Return, typename... Args>
using FunctionPointer = Return(*)(Args...);


template <typename Return, typename... Args>
FunctionPointer<Return, Args...> get_next_symbol(const char* name)
{
    auto sym = reinterpret_cast<FunctionPointer<Return, Args...>>(dlsym(RTLD_NEXT, name));
    if (sym == nullptr) {
        std::cerr << "libfakesudo fatal error: symbol '" << name << "' is not available" << std::endl;
        abort();
    }
    return sym;
}
