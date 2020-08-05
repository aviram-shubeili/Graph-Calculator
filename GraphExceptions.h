//
// Created by avira on 04/08/2020.
//

#ifndef MTM_FINALPROJECT_GRAPHEXCEPTIONS_H
#define MTM_FINALPROJECT_GRAPHEXCEPTIONS_H

#include "Exceptions.h"

class GraphExceptions : public Exceptions {
public:
    const char *what() const noexcept override {
        return "Error: Unknown Graph Error. \n";
    }
};

class InvalidGraphData : public GraphExceptions {
public:
    const char *what() const noexcept override {
        return "Error: Invalid graph data. \n" ;
    }
};

class IllegalVertexName : public GraphExceptions {
public:
    const char *what() const noexcept override {
        return "Error: Illegal vertex name. \n";
    }
};

class VertexNotExist : public GraphExceptions {
public:
    const char *what() const noexcept override {
        return "Error: Vertex doesnt exist in graph. \n";
    }
};

class EdgeAlreadyExists : public GraphExceptions {
public:
    const char *what() const noexcept override {
        return "Error: Edge already exists in graph. \n";
    }
};

class VertexAlreadyExists : public GraphExceptions {
public:
    const char *what() const noexcept override {
        return "Error: Vertex already exists in graph. \n";
    }
};

class SelfLoop : public GraphExceptions {
public:
    const char *what() const noexcept override {
        return "Error: Self loop edge. \n";
    }
};



#endif //MTM_FINALPROJECT_GRAPHEXCEPTIONS_H
