//
// Created by avira on 04/08/2020.
//

#ifndef MTM_FINALPROJECT_CALCEXCEPTIONS_H
#define MTM_FINALPROJECT_CALCEXCEPTIONS_H
#include "Exceptions.h"

class CalcExceptions : public Exceptions {
public:
    const char *what() const noexcept override;
};

class InvalidGraphName : public CalcExceptions {
public:
    const char *what() const noexcept override;
};

class CommandNotInFormat : public CalcExceptions {
public:
    const char *what() const noexcept override;
};

class NoAssignmentOp : public CalcExceptions {
public:
    const char *what() const noexcept override;
};

class GraphNotFound : public CalcExceptions {
public:
    const char *what() const noexcept override;
};

#endif //MTM_FINALPROJECT_CALCEXCEPTIONS_H

