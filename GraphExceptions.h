//
// Created by avira on 04/08/2020.
//

#ifndef MTM_FINALPROJECT_GRAPHEXCEPTIONS_H
#define MTM_FINALPROJECT_GRAPHEXCEPTIONS_H
#include "Exceptions.h"

class GraphExceptions : public Exceptions {
public:
    const char *what() const noexcept override;
};

class InvalidGraphData : public GraphExceptions {
public:
    const char *what() const noexcept override;
};

class IllegalEdgeData : public GraphExceptions {
public:
    const char *what() const noexcept override;
};

class IllegalVertexName : public GraphExceptions {
public:
    const char *what() const noexcept override;
};

class VertexNotExist : public GraphExceptions {
public:
    const char *what() const noexcept override;
};


class EdgeAlreadyExists : public GraphExceptions {
public:
    const char *what() const noexcept override;
};

class VertexAlreadyExists : public GraphExceptions {
public:
    const char *what() const noexcept override;
};

class SelfLoop : public GraphExceptions {
public:
    const char *what() const noexcept override;
};


#endif //MTM_FINALPROJECT_GRAPHEXCEPTIONS_H
