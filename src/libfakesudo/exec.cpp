#include <libfakesudo/get_next_symbol.hpp>

#include <cstdlib>
#include <iostream>
#include <string_view>
#include <unistd.h>
#include <vector>


extern "C"
{

int execle(const char* path, const char* arg0, ...)
{
    std::cerr << "libfakesudo error: execle is not implemented" << std::endl;
    abort();
}

int execve(const char* path, char* const* argv, char* const* envp)
{
    auto old = get_next_symbol<int, const char*, char* const*, char* const*>("execve");
    auto ld_preload = getenv("LD_PRELOAD");
    if (ld_preload == nullptr) {
        std::cerr << "libfakesudo fatal error: getenv(\"LD_PRELOAD\") returned nullptr" << std::endl;
    }
    const char* libfakesudo_uid = getenv("LIBFAKESUDO_UID");
    if (libfakesudo_uid == nullptr) {
        libfakesudo_uid = "0";
    }
    std::vector<const char*> env;
    for (auto sptr = envp; *sptr != nullptr; ++sptr) {
        std::string_view str = *sptr;
        if (str.find("LD_PRELOAD=") == 0 || str.find("LIBFAKESUDO_UID=") == 0) {
            continue;
        }
        env.push_back(*sptr);
    }
    std::string preload = std::string("LD_PRELOAD=") + ld_preload;
    std::string uid = std::string("LIBFAKESUDO_UID=") + libfakesudo_uid;
    env.push_back(preload.c_str());
    env.push_back(uid.c_str());

    return old(path, argv, const_cast<char* const*>(env.data()));
}

int fexecve(int fd, char* const* argv, char* const* envp)
{
    std::cerr << "libfakesudo error: fexecve is not implemented" << std::endl;
    abort();
}


} // extern "C"
