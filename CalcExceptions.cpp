//
// Created by avira on 04/08/2020.
//

#include "CalcExceptions.h"

const char *CalcExceptions::what() const noexcept {
    return "Error: Unknown Calc Error. \n";
}
const char *NoAssignmentOp::what() const noexcept {
    return "Error: No Assignment operator given. \n";
}

const char *InvalidGraphName::what() const noexcept {
    return "Error: Invalid graph name. \n";
}

const char *CommandNotInFormat::what() const noexcept {
    return "Error: Unformatted command. \n" ;
}

const char *GraphNotFound::what() const noexcept {
    return  "Error: Graph not found. \n";
}

const char *InvalidFileName::what() const noexcept {
    return "Error: Invalid file name. \n";
}

const char *BinaryFileError::what() const noexcept {
    return "Error: couldn't open binary file \n";
}
