//
// Created by avira on 04/08/2020.
//

#include "Exceptions.h"

const char *OpenFileError::what() const noexcept {
    return "Error: FATAL - Unable to open file.";
}

const char *RunError::what() const noexcept {
    return "Error: FATAL - Illegal use of calculator";
}
