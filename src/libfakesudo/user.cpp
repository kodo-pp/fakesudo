#include <libfakesudo/parameters.hpp>

#include <cstdlib>
#include <unistd.h>


extern "C"
{

uid_t getuid()
{
    if (faked_uid.has_value()) {
        return *faked_uid;
    }
    char* str = getenv("LIBFAKESUDO_UID");
    if (str == nullptr) {
        faked_uid = 0;
        return 0;
    }
    auto uid = static_cast<uid_t>(atol(str));
    faked_uid = uid;
    return uid;
}

uid_t geteuid()
{
    if (faked_uid.has_value()) {
        return *faked_uid;
    }
    char* str = getenv("LIBFAKESUDO_UID");
    if (str == nullptr) {
        faked_uid = 0;
        return 0;
    }
    auto uid = static_cast<uid_t>(atol(str));
    faked_uid = uid;
    return uid;
}

} // extern "C"
