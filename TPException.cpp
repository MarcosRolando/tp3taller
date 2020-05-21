//
// Created by marcos on 20/5/20.
//

#include "TPException.h"

const char *TPException::what() const noexcept {
    return errorMessage.c_str();
}
