#include "common_TPException.h"

const char *TPException::what() const noexcept {
    return errorMessage.c_str();
}
