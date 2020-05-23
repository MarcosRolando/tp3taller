#include "common_OSException.h"
#include <cerrno>
#include <cstdio>
#include <cstdarg>
#include <cstring>

OSException::OSException(const char *fmt, ...) noexcept {
    _errno = errno;
    memset(errorMsg, 0, BUF_LEN);
    va_list args;
    va_start(args, fmt);
    int s = vsnprintf(errorMsg, BUF_LEN, fmt, args);
    va_end(args);
    if (_errno != 0) {
        strncpy(errorMsg + s, strerror(_errno), BUF_LEN - s);
    }
    errorMsg[BUF_LEN - 1] = 0;
}

const char *OSException::what() const noexcept {
    return errorMsg;
}
