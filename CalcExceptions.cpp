//
// Created by avira on 04/08/2020.
//

#include "CalcExceptions.h"

const char *CalcExceptions::what() const noexcept {
    return "Unknown Calc Error. \n";
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
