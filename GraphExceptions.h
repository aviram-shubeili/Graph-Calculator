//
// Created by avira on 04/08/2020.
//

#ifndef MTM_FINALPROJECT_GRAPHEXCEPTIONS_H
#define MTM_FINALPROJECT_GRAPHEXCEPTIONS_H
#include "Exceptions.h"

class GraphExceptions : public Exceptions {

};

class InvalidGraphData : public GraphExceptions {

};

class IllegalEdgeData : public GraphExceptions {

};

class IllegalVertexName : public GraphExceptions {

};

class VertexNotExist : public GraphExceptions {

};


#endif //MTM_FINALPROJECT_GRAPHEXCEPTIONS_H
