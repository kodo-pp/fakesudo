#include <libfakesudo/get_next_symbol.hpp>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string_view>


extern "C"
{

char* getenv(const char* c_name)
{
    auto old = get_next_symbol<char*, const char*>("getenv");
    return old(c_name);
}

char* secure_getenv(const char* c_name)
{
    auto old = get_next_symbol<char*, const char*>("secure_getenv");
    return old(c_name);
}

int putenv(char* c_str)
{
    auto old = get_next_symbol<int, char*>("putenv");
    std::string_view str = c_str;
    auto equals_index = str.find('=');
    if (equals_index == str.npos) {
        // Delete env (GNU extension)
        const auto& name = str;
        if (name == "LD_PRELOAD" || name == "LIBFAKESUDO_UID") {
            return 0;
        }
        return old(c_str);
    } else {
        // Add env
        auto name = str.substr(0, equals_index);
        if (name == "LD_PRELOAD") {
            std::cerr << "libfakesudo error: nested setting LD_PRELOAD is not implemented" << std::endl;
            abort();
        }
        if (name == "LIBFAKESUDO_UID") {
            return 0;
        }
        return old(c_str);
    }
}

int setenv(const char* c_name, const char* value, int replace)
{
    auto old = get_next_symbol<int, const char*, const char*, int>("setenv");
    std::string_view name = c_name;
    if (name == "LD_PRELOAD" && replace != 0) {
        std::cerr << "libfakesudo error: nested setting LD_PRELOAD is not implemented" << std::endl;
        abort();
    }
    if (name == "LIBFAKESUDO_UID") {
        return 0;
    }
    return old(c_name, value, replace);
}

int clearenv()
{
    std::cerr << "libfakesudo error: clearenv() is not implemented" << std::endl;
    abort();
}

int unsetenv(const char* c_name)
{
    auto old = get_next_symbol<int, const char*>("unsetenv");
    std::string_view name = c_name;

    if (name == "LD_PRELOAD" || name == "LIBFAKESUDO_UID") {
        return 0;
    }
    return old(c_name);
}

} // extern "C"
