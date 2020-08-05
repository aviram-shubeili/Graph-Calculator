//
// Created by avira on 04/08/2020.
//

#ifndef MTM_FINALPROJECT_EXCEPTIONS_H
#define MTM_FINALPROJECT_EXCEPTIONS_H
#include <exception>

class Exceptions : public std::exception{

};

class RunError : public Exceptions {
public:
    const char *what() const noexcept override;
};

class OpenFileError : public Exceptions {
public:
    const char *what() const noexcept override;
};


#endif //MTM_FINALPROJECT_EXCEPTIONS_H
