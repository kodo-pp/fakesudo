#include <config.hpp>

#include <unistd.h>


extern "C"
{

#ifdef LIBFAKESUDO_FAKE_CHOWN

int chown(const char* path, uid_t owner, gid_t group)
{
    if (access(path, F_OK) != 0) {
        // File does not exist
        return -1;
    }
    return 0;
}

int lchown(const char* path, uid_t owner, gid_t group)
{
    if (access(path, F_OK) != 0) {
        // File does not exist
        return -1;
    }
    return 0;
}

int fchown(int fd, uid_t owner, gid_t group)
{
    return 0;
}

int fchownat(int dirfd, const char* path, uid_t owner, gid_t group, int flags)
{
    if (faccessat(dirfd, path, F_OK, flags) != 0) {
        // File does not exist
        return -1;
    }
    return 0;
}

#endif // LIBFAKESUDO_FAKE_CHOWN

} // extern "C"
